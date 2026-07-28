#pragma once

#include "process_info.hpp"
#include <ncurses.h>
#include <vector>

enum class AppState {
    DASHBOARD,
    PROCESS_DETAILS,
    EXIT
};

class UIRenderer {
public:
    UIRenderer();
    ~UIRenderer();

    void renderDashboard(const SystemInfo& sysInfo, const std::vector<ProcessInfo>& processes);
    void drawProgressBar(WINDOW* win, int y, int x, double percentage, int bar_width);

    AppState handleInput(AppState currentState);
private:
    WINDOW* sys_win;
    WINDOW* proc_win;
    WINDOW* prog_bar;

};