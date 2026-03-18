#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

Logger& Logger::instance() {
    static Logger inst;
    return inst;
}

Logger::Logger() {
    setFile("pchelovod.log");
}

Logger::~Logger() {
    if (file_.is_open()) file_.close();
}

void Logger::setFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (file_.is_open()) file_.close();
    file_.open(filename, std::ios::app);
}

void Logger::log(const std::string& msg, const std::string& level) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S")
       << " [" << level << "] " << msg << "\n";

    std::lock_guard<std::mutex> lock(mtx_);
    std::cout << ss.str();
    if (file_.is_open()) {
        file_ << ss.str();
        file_.flush();
    }
}