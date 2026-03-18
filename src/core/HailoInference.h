// HailoInference.h
#pragma once
#include <hailo/hailort.hpp>
#include <memory>
#include <vector>

class HailoInference {
public:
    HailoInference(const std::string& hef_path);
    ~HailoInference();
    
    struct Detection { float x, y, w, h; float confidence; int class_id; };
    std::vector<Detection> run(const cv::Mat& frame);  // вход — кадр с камеры дрона

private:
    std::shared_ptr<hailo::VDevice> vdevice;
    std::shared_ptr<hailo::InferModel> infer_model;
    std::shared_ptr<hailo::ConfiguredInferModel> configured_model;
};