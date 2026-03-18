#include "HailoInference.h"
#include <iostream>

HailoInference::HailoInference(const std::string& hef_path)
{
    std::cout << "Hailo placeholder: " << hef_path << "\n";
}

HailoInference::~HailoInference() = default;

std::vector<HailoInference::Detection> HailoInference::run(const std::vector<uint8_t>&)
{
    // Здесь должен быть реальный вызов HailoRT
    return {{0, 0.92f, 120, 80, 420, 380}};
}