#include "data_fetcher.hpp"
#include "ui_renderer.hpp"
#include <chrono>
#include <thread>

int main() {
    DataFetcher fetcher;
    UIRenderer renderer;
    
    AppState state = AppState::DASHBOARD;

    SystemInfo sys_info = fetcher.fetchSystemInfo();
    std::vector<ProcessInfo> processes = fetcher.fetchTopProcesses();
    fetcher.sortProcess(processes, sortOption::CPU);

    auto last_update_time = std::chrono::steady_clock::now();

    while (state != AppState::EXIT) {
        
        state = renderer.handleInput(state);

        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_update_time).count();

        if (elapsed_time >= 1) {
            sys_info = fetcher.fetchSystemInfo();
            processes = fetcher.fetchTopProcesses();
            fetcher.sortProcess(processes, sortOption::CPU);
            
            last_update_time = current_time;
        }

        renderer.renderDashboard(sys_info, processes);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}