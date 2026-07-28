#pragma once

#include <string>
#include <vector>

// Stores the global data of the whole PCs
struct SystemInfo {
    double cpu_usage;          // in percent (0.0 to 100.0)
    double cpu_temp;           // cpu temp in °C
    double ram_usage;          // in percent
    double total_ram_gb;       // RAM in Gigabyte
    unsigned long long uptime; // runtime in seconds
};

// Stores the data of each single process
struct ProcessInfo {
    int pid;                   // the process-ID
    std::string name;          // name of the process (i.e. "firefox")
    std::string state;         // State (i.e. "R" for running, "S" für sleeping)
    double cpu_usage;          // in percent
    double ram_usage;          // in percent
};
