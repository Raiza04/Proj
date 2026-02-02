#include "ascii_converter.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 3)
    {
        std::cerr << "Usage: ./asciiConverter <filename> [resolution]" << std::endl;
        return 1;
    }

    std::string imagePath = std::string("images/") + argv[1];

    int resolution = 100;

    if (argc == 3)
    {
        try
        {
            resolution = std::stoi(argv[2]);
        }
        catch (...)
        {
            std::cerr << "Warning: '" << argv[2] << "' is not a valid number" << std::endl;
            std::cerr << "Using default resolution: " << resolution << std::endl;
        }
    }

    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cerr << "Could not load image!" << std::endl;
        return -1;
    }

    std::vector<std::string> asciiArt = ascii::convert(image, resolution);

    std::ofstream out("ascii_output.txt");
    for (const auto &line : asciiArt)
    {
        out << line << "\n";
    }
    out.close();

    std::cout << "ASCII art saved to ascii_output.txt\n\n";
    std::cout << "ASCII art preview:\n";
    for (const auto &line : asciiArt)
    {
        std::cout << line << "\n";
    }

    int fontSize = 1;
    int font = cv::FONT_HERSHEY_SIMPLEX;
    int thickness = 1;
    int lineType = cv::LINE_AA;

    int rows = asciiArt.size();
    int cols = asciiArt[0].size();
    int imgHeight = rows * fontSize * 20;
    int imgWidth = cols * fontSize * 10;

    cv::Mat asciiImage = cv::Mat::zeros(imgHeight, imgWidth, CV_8UC3);

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            int textX = x * fontSize * 10;
            int textY = y * fontSize * 20 + fontSize * 15;
            cv::putText(asciiImage, std::string(1, asciiArt[y][x]), cv::Point(textX, textY), font, fontSize, cv::Scalar(255, 255, 255), thickness, lineType);
        }
    }

    cv::imwrite("ascii_output.png", asciiImage);
    std::cout << "ASCII image saved to ascii_output.png\n";

    return 0;
}