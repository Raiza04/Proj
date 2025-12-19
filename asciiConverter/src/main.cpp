#include "ascii_converter.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    // Load an image from file

    if (argc < 2 || argc > 2) return 1;
    

    std::string imagePath = std::string("images/") + argv[1];
    
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Could not load image!" << std::endl;
        return -1;
    }

    // Convert the image to ASCII art
    std::vector<std::string> asciiArt = ascii::convert(image, 540);

    // Save the ASCII art to a file
    std::ofstream out("ascii_output.txt");
    for (const auto& line : asciiArt) {
        out << line << "\n";
    }
    out.close();

    // Print the ASCII art to the terminal
    std::cout << "ASCII art saved to ascii_output.txt\n\n";
    std::cout << "ASCII art preview:\n";
    for (const auto& line : asciiArt) {
        std::cout << line << "\n";
    }

    // Create an image to draw the ASCII art
    int fontSize = 1;
    int font = cv::FONT_HERSHEY_SIMPLEX;
    int thickness = 1;
    int lineType = cv::LINE_AA;

    int rows = asciiArt.size();
    int cols = asciiArt[0].size();
    int imgHeight = rows * fontSize * 20; // Adjust based on font size
    int imgWidth = cols * fontSize * 10;  // Adjust based on font size

    cv::Mat asciiImage = cv::Mat::zeros(imgHeight, imgWidth, CV_8UC3);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            int textX = x * fontSize * 10;
            int textY = y * fontSize * 20 + fontSize * 15;
            cv::putText(asciiImage, std::string(1, asciiArt[y][x]), cv::Point(textX, textY), font, fontSize, cv::Scalar(255, 255, 255), thickness, lineType);
        }
    }

    // Save the ASCII image to a file
    cv::imwrite("ascii_output.png", asciiImage);
    std::cout << "ASCII image saved to ascii_output.png\n";

    return 0;
}