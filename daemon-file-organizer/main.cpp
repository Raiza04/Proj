#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include "include/nlohmann/json.hpp" // downloaded header by CMake
#include <nlohmann/json.hpp>         // if the header already exists
#include <fcntl.h>

using json = nlohmann::json;
namespace fs = std::filesystem;

#define HOUR 4

void daemonize()
{
    pid_t pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    if (setsid() < 0)
    {
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    // --- LOGGING ---

    int fd_null = open("/dev/null", O_RDWR);
    if (fd_null != -1)
    {
        dup2(fd_null, STDIN_FILENO);
        close(fd_null);
    }
    int fd_log = open("organizer_daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd_log != -1)
    {
        dup2(fd_log, STDOUT_FILENO);
        dup2(fd_log, STDERR_FILENO);
        close(fd_log);
    }
}

int main(void)
{
    std::vector<fs::path> dirs;
    std::unordered_map<std::string, std::string> extToFolder;

    std::ifstream myPaths("paths.txt");
    if (!myPaths.is_open())
    {
        std::cerr << "Error: File 'paths.txt' could not be opened.\n";
        return 1;
    }

    std::string line;
    while (std::getline(myPaths, line))
    {
        if (!fs::exists(line) || !fs::is_directory(line))
        {
            std::cerr << "Warning: " << line << " does not exist or is not a folder.\n";
            continue;
        }
        dirs.push_back(line);
    }

    if (dirs.empty())
    {
        std::cerr << "Error: No valid paths provided in paths.txt.\n";
        return 1;
    }

    try
    {
        json j = json::parse(std::ifstream("extensions.json"));
        for (auto &[folder, extList] : j.items())
        {
            for (auto &ext : extList)
            {
                extToFolder[ext] = folder;
            }
        }
    }
    catch (...)
    {
        std::cerr << "Error: Missing or bad extensions.json\n";
        return 1;
    }

    daemonize();

    while (true)
    {
        for (size_t i = 0; i < dirs.size(); i++)
        {
            for (const auto &entry : fs::directory_iterator(dirs[i]))
            {
                if (entry.is_regular_file())
                {
                    std::string ext = entry.path().extension().string();
                    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c)
                                   { return std::tolower(c); });

                    auto it = extToFolder.find(ext);
                    std::string folder = (it == extToFolder.end()) ? "Misc" : it->second;

                    fs::path src = entry.path();
                    fs::path dest = dirs[i] / folder / src.filename();

                    fs::create_directories(dest.parent_path());
                    fs::rename(src, dest);
                }
            }
        }
        sleep(HOUR * 3600); // every 4 hours
    }

    return 0;
}