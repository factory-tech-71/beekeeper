#pragma once

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/mission/mission.h>
#include <memory>
#include <vector>
#include <string>
#include <mutex>

class HailoInference;

struct Drone {
    std::shared_ptr<mavsdk::System> system;
    std::shared_ptr<mavsdk::Action> action;
    std::shared_ptr<mavsdk::Telemetry> telemetry;
    std::shared_ptr<mavsdk::Offboard> offboard;
    std::shared_ptr<mavsdk::Mission> mission;
    std::string name;
    bool is_leader = false;
    bool in_offboard = false;
};

class SwarmManager
{
public:
    explicit SwarmManager(const std::string& connection_string = "udp://:14550");
    ~SwarmManager();

    size_t droneCount() const;
    std::string getStatusSummary() const;

    void armAll();
    void takeoffAll(float altitude_m = 5.0f);

    bool startOffboardAll();
    void stopOffboardAll();
    void setVFormation(float spacing_m = 6.0f);

    bool uploadSimpleMission(const std::string& mission_txt_path);

    // Для карты — возвращает позиции (можно расширить)
    std::vector<std::tuple<std::string, double, double, float>> getDronePositions() const;

private:
    mavsdk::Mavsdk mavsdk;
    std::vector<Drone> drones;
    size_t leader_index = 0;
    mutable std::mutex mtx;
    std::unique_ptr<HailoInference> hailo;
};