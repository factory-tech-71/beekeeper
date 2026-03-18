#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    static Logger& instance();
    void log(const std::string& msg, const std::string& level = "INFO");
    void setFile(const std::string& filename);

private:
    Logger();
    ~Logger();

    std::ofstream file_;
    std::mutex mtx_;
};