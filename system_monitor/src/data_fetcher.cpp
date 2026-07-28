#include "data_fetcher.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <iterator>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

DataFetcher::DataFetcher() {
    prev_total_ticks = 0;
    prev_idle_ticks = 0;
}

SystemInfo DataFetcher::fetchSystemInfo() {
    SystemInfo info = {0.0, 0.0, 0.0, 0.0, 0};

    //Memory Stats
    std::ifstream meminfo("/proc/meminfo");
    if (meminfo.is_open()) {
        std::string line;
        std::string key;
        long long value;
        std::string unit;

        long long memTotal = 0;
        long long memAvailable = 0;
        
        // Memory usage
        while (std::getline(meminfo, line)) {
            std::istringstream iss(line);
            iss >> key >> value >> unit;

            if (key == "MemTotal:") memTotal = value;
            if (key == "MemAvailable:") memAvailable = value;
        }
        
        //Total in Gb
        info.total_ram_gb = memTotal / 1024.0 / 1024.0;
        total_ram = memTotal / 1024.0;
        
        //Total in percent
        if (memTotal > 0) {
            info.ram_usage = (1.0 - ((double)memAvailable / memTotal)) * 100.0;
        }
    } else {
        std::cerr << "/proc/meminfo could not be opend. Exiting the program" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Uptime
    std::ifstream uptime("/proc/uptime");
    if (uptime.is_open()) {
        double uptime_seconds;
        uptime >> uptime_seconds;
        info.uptime = static_cast<unsigned long long>(uptime_seconds);
    } else {
        std::cerr << "/proc/uptime could not be opend. Exiting the program" << std::endl;
        exit(EXIT_FAILURE);
    }

    //CPU Stats
    std::ifstream stat("/proc/stat");
    if (stat.is_open()) {
        std::string line;
        std::getline(stat, line);
        
        std::istringstream iss(line);
        std::string cpu_label;
        long long user, nice, system, idle_time, iowait, irq, softirq, steal, guest, guest_nice;

        iss >> cpu_label >> user >> nice >> system >> idle_time >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

        long long current_idle = idle_time + iowait;
        long long current_total = user + nice + system + current_idle + irq + softirq + steal;

        long long delta_total = current_total - prev_total_ticks;
        long long delta_idle  = current_idle - prev_idle_ticks;

        if (delta_total > 0) {
            info.cpu_usage = ((double)(delta_total - delta_idle) / delta_total) * 100.0;
        }

        total_cpu_usage = delta_total;
        prev_total_ticks = current_total;
        prev_idle_ticks = current_idle;
    } else {
        std::cerr << "/proc/stat could not be opend. Exiting the program" << std::endl;
        exit(EXIT_FAILURE);
    }

    //CPU temp

    bool temp_found = false;

    for (const auto& entry : fs::directory_iterator("/sys/class/thermal"))
    {
        std::string dir = entry.path().filename().string();

        if (dir.rfind("thermal_zone") == 0)
        {
            fs::path dir_type = entry.path() / "type";
            std::ifstream type_file(dir_type);
            if (type_file.is_open())
            {
                std::string type_line;
                getline(type_file, type_line);
                if (type_line == "x86_pkg_temp")
                {
                    fs::path temp_file = entry.path() / "temp";
                    std::ifstream temps(temp_file);
                    if (temps.is_open())
                    {
                        std::string temp_line;
                        getline(temps, temp_line);
                        info.cpu_temp = std::stoi(temp_line) / 1000.0;
                        temp_found = true;
                        break;

                    } else{
                        continue;;                        
                    }
                    
                }
                
            } else {
                continue;
            }
            
        } else {
            continue;
        }
        
    }
    
    if (!temp_found)
    {
        std::cerr << "Critical issue: CPU temp could not be found. Exiting the program" << std::endl;
        exit(EXIT_FAILURE);
    }
    

    return info;
}

std::vector<ProcessInfo> DataFetcher::fetchTopProcesses() {
    std::vector<ProcessInfo> processes;

    std::unordered_map<int, unsigned long long> current_tick_map;

    for (const auto& entry : fs::directory_iterator("/proc")) {
        std::string filename = entry.path().filename().string();
        
        if (filename.find_first_not_of("0123456789") == std::string::npos) {
            int pid = std::stoi(filename);
            ProcessInfo curr_process;
            curr_process.pid = pid;

            fs::path process_path_comm = fs::path("/proc") / std::to_string(pid) / "comm";
            fs::path process_path_statm = fs::path("/proc") / std::to_string(pid) / "statm";
            fs::path process_path_stat = fs::path("/proc") / std::to_string(pid) / "stat";

            // --- READING NAME ---
            std::ifstream myProcess_comm(process_path_comm);
            if (myProcess_comm.is_open()) {
                std::getline(myProcess_comm, curr_process.name);
            } else {
                std::cerr << process_path_comm << "could not be opened. Ignoring the process" << pid << std::endl;
                break;;
            }

            // --- READING RAM ---
            std::ifstream myProcess_statm(process_path_statm);
            if (myProcess_statm.is_open()) {
                long long dummy, rss;
                myProcess_statm >> dummy >> rss;

                double ram_usage_mb = (rss * 4096) / 1024.0 / 1024.0;

                if (total_ram > 0) { 
                    curr_process.ram_usage = (ram_usage_mb / total_ram) * 100.0;
                } else {
                    curr_process.ram_usage = 0.0;
                }
            } else {
                std::cerr << process_path_statm << "could not be opened. Ignoring the process" << pid << std::endl;
                break;;
            }

            // --- READING CPU & STATUS ---
            std::ifstream myProcess_stat(process_path_stat);
            if (myProcess_stat.is_open()) {
                std::string line;
                std::getline(myProcess_stat, line);

                size_t rparen_pos = line.find_last_of(')');
                if (rparen_pos != std::string::npos) {
                    std::string stats_only = line.substr(rparen_pos + 2);
                    std::istringstream iss(stats_only);
                    
                    std::string state;
                    long long utime, stime;
                    std::string dummy;

                    iss >> state; 
                    for (int i = 0; i < 10; ++i) iss >> dummy;
                    iss >> utime >> stime;

                    curr_process.state = state;
                    unsigned long long current_process_ticks = utime + stime;
                    double cpu_usage = 0.0;

                    if (prev_process_ticks.find(pid) != prev_process_ticks.end()) {
                        unsigned long long prev_ticks = prev_process_ticks[pid];
                        unsigned long long delta_process = current_process_ticks - prev_ticks;
                        
                        if (total_cpu_usage > 0) {
                            cpu_usage = ((double)delta_process / (double)total_cpu_usage) * 100.0;
                        }
                    }

                    curr_process.cpu_usage = cpu_usage;
                    current_tick_map[pid] = current_process_ticks;
                }
            } else {
                std::cerr << process_path_stat << "could not be opened. Ignoring the process" << pid << std::endl;
                break;;
            }

            processes.push_back(curr_process);
        }
    }

    prev_process_ticks = current_tick_map;

    return processes;
}

void DataFetcher::sortProcess(std::vector<ProcessInfo>& vec, sortOption prio){
    switch (prio)
    {
    case sortOption::PID:
        std::sort(vec.begin(), vec.end(), [](const ProcessInfo& a,const ProcessInfo& b){
           return a.pid < b.pid;
        });
        break;

    case sortOption::CPU:
        std::sort(vec.begin(), vec.end(), [](const ProcessInfo& a,const ProcessInfo& b){
           return a.cpu_usage > b.cpu_usage;
        });
        break;

    case sortOption::RAM:
        std::sort(vec.begin(), vec.end(), [](const ProcessInfo& a,const ProcessInfo& b){
           return a.ram_usage > b.ram_usage;
        });
        break;

    case sortOption::NAME:
        std::sort(vec.begin(), vec.end(), [](const ProcessInfo& a,const ProcessInfo& b){
           return a.name < b.name;
        });
        break;

    case sortOption::STATE:
        std::sort(vec.begin(), vec.end(), [](const ProcessInfo& a,const ProcessInfo& b){
           return a.state < b.state;
        });
        break;

    default:
        break;
    }
}