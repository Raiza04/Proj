#pragma once

#include "process_info.hpp"
#include <vector>
#include <unordered_map>

enum class sortOption {
    PID,
    CPU,
    RAM,
    STATE,
    NAME
};

class DataFetcher {
public:
    DataFetcher();

    SystemInfo fetchSystemInfo();
    std::vector<ProcessInfo> fetchTopProcesses();
    void sortProcess(std::vector<ProcessInfo>& vec, sortOption prio);

private:
    // Store the data of the last call
    unsigned long long prev_total_ticks;
    unsigned long long prev_idle_ticks;
    double total_ram;
    unsigned long long total_cpu_usage;

    std::unordered_map<int, unsigned long long> prev_process_ticks;
};
