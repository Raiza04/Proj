#pragma once
#include <opencv2/core/mat.hpp>
#include <string>
#include <vector>

namespace ascii {
    std::vector<std::string> convert(const cv::Mat& gray, int maxCols, const std::string& chars = " .:-=+*#%@");
}