#include "SwarmManager.h"
#include "HailoInference.h"
#include <iostream>
#include <fstream>
#include <sstream>

SwarmManager::SwarmManager(const std::string& connection_string)
{
    mavsdk.add_any_connection(connection_string);

    // Hailo
    try {
        hailo = std::make_unique<HailoInference>("models/yolov8s.hef");
    } catch (...) {
        std::cerr << "Hailo не запустился\n";
    }
}

SwarmManager::~SwarmManager() = default;

size_t SwarmManager::droneCount() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return drones.size();
}

std::string SwarmManager::getStatusSummary() const
{
    std::lock_guard<std::mutex> lock(mtx);
    std::ostringstream oss;
    for (const auto& d : drones) {
        oss << d.name << "  armed:" << d.action->get_is_armed().value_or(false) << "\n";
    }
    return oss.str();
}

void SwarmManager::armAll()
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& d : drones) d.action->arm_async([](auto){});
}

void SwarmManager::takeoffAll(float alt)
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& d : drones) {
        d.action->set_takeoff_altitude(alt);
        d.action->takeoff_async([](auto){});
    }
}

bool SwarmManager::startOffboardAll()
{
    std::lock_guard<std::mutex> lock(mtx);
    bool ok = true;
    for (auto& d : drones) {
        if (d.offboard->start() != mavsdk::Offboard::Result::Success) ok = false;
        else d.in_offboard = true;
    }
    return ok;
}

void SwarmManager::setVFormation(float spacing)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (leader_index >= drones.size()) return;

    auto pos_opt = drones[leader_index].telemetry->position();
    if (!pos_opt) return;

    size_t idx = 0;
    for (auto& d : drones) {
        if (d.is_leader) continue;
        float dx = (idx % 3 - 1) * spacing;
        float dy = (idx / 3) * spacing * 1.4f;
        mavsdk::Offboard::PositionNedYaw sp{};
        sp.north_m = dx;
        sp.east_m  = dy;
        sp.down_m  = -5.0f;
        sp.yaw_deg = 0;
        d.offboard->set_position_ned(sp);
        idx++;
    }
}

bool SwarmManager::uploadSimpleMission(const std::string& path)
{
    std::ifstream f(path);
    if (!f) return false;

    std::vector<mavsdk::Mission::MissionItem> items;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        double lat, lon, alt;
        if (iss >> lat >> lon >> alt) {
            mavsdk::Mission::MissionItem it{};
            it.latitude_deg = lat;
            it.longitude_deg = lon;
            it.relative_altitude_m = alt;
            it.command = mavsdk::Mission::MissionItem::Command::NavigateTo;
            items.push_back(it);
        }
    }

    std::lock_guard<std::mutex> lock(mtx);
    for (auto& d : drones) {
        d.mission->upload_mission(items);
    }
    return true;
}

std::vector<std::tuple<std::string, double, double, float>> SwarmManager::getDronePositions() const
{
    std::vector<std::tuple<std::string, double, double, float>> res;
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& d : drones) {
        auto p = d.telemetry->position();
        if (p) {
            res.emplace_back(d.name, p->latitude_deg, p->longitude_deg, p->absolute_altitude_m);
        }
    }
    return res;
}