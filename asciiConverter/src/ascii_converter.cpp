#include "ascii_converter.hpp"
#include <opencv2/imgproc.hpp>
#include <cmath>

std::vector<std::string> ascii::convert(const cv::Mat& gray,
                                        int maxCols,
                                        const std::string& chars) {
    // Calculate the scaling factors
    double charAspectRatio = 0.5; // Assuming characters are half as wide as they are tall
    double aspectRatio = static_cast<double>(gray.rows) / gray.cols;

    // Calculate the new dimensions
    int newCols = maxCols;
    int newRows = static_cast<int>(aspectRatio * newCols * charAspectRatio);

    cv::Mat resized;
    cv::resize(gray, resized, cv::Size(newCols, newRows), 0, 0, cv::INTER_AREA);

    std::vector<std::string> result;
    result.reserve(resized.rows);

    for (int y = 0; y < resized.rows; ++y) {
        std::string row;
        row.reserve(resized.cols);

        for (int x = 0; x < resized.cols; ++x) {
            uchar pixel = resized.at<uchar>(y, x);
            int idx = pixel * (chars.size() - 1) / 255;
            row += chars[idx];
        }

        result.push_back(row);
    }

    return result;
}