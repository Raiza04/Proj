#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include "json.hpp"
using json = nlohmann::json;

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    bool verbose = false;
    bool dryRun  = false;
    fs::path dir = ".";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-v" || arg == "--verbose")
            verbose = true;
        else if (arg == "-d" || arg == "--dry")
            dryRun = true;
        else if (arg.empty() || arg[0] != '-')
            dir = arg;
    }

    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        std::cerr << "Error: '" << dir << "' is not a valid directory\n";
        return 1;
    }

    std::unordered_map<std::string, std::string> extToFolder;

    try {
        json j = json::parse(std::ifstream("categories.json"));
        for (auto& [folder, extList] : j.items()) {
            for (auto& ext : extList){
                extToFolder[ext] = folder;
            }
        }
    } catch (...) {
        std::cerr << "Missing or bad categories.json\n";
        return 1;
    }


    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (entry.is_regular_file())
        {   
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c){ return std::tolower(c); });

            auto it = extToFolder.find(ext);
            std::string folder = (it == extToFolder.end()) ? "Misc" : it->second;
            
            fs::path src  = entry.path();
            fs::path dest = src.parent_path() / folder / src.filename();

            if (dryRun) {
                std::cout << "[dry] would move:  " << src.filename().string() << "  ->  " << dest << '\n';

            } else {
                
                fs::create_directories(dest.parent_path());
                fs::rename(src, dest);
                if (verbose){
                    std::cout << "moved: " << src.filename().string() << '\n';
                }
            }
        }
    }
}