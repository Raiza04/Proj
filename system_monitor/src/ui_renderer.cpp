#include "ui_renderer.hpp"
#include <ncurses.h>
#include <string>

UIRenderer::UIRenderer() {
    initscr();             
    noecho();              
    curs_set(0);           
    cbreak();              
    keypad(stdscr, TRUE); 
    nodelay(stdscr, TRUE); 
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_CYAN, -1);
    init_pair(5, COLOR_MAGENTA, -1);

    sys_win = newwin(LINES/3, COLS/2, 0, 0);
    prog_bar = newwin(LINES/3, COLS/2, 0, COLS/2);
    proc_win = newwin((LINES/3)*2, COLS, (LINES/3), 0);
}


UIRenderer::~UIRenderer() {
    delwin(sys_win);
    delwin(proc_win);
    endwin();
}


AppState UIRenderer::handleInput(AppState currentState) {
    int ch = getch();

    switch (ch)
    {
    case ERR:
        return currentState;
    
    case 'q':
    case 'Q':
        return AppState::EXIT;
    
    case KEY_RESIZE:
        delwin(sys_win);
        delwin(proc_win);
        delwin(prog_bar);
        sys_win = newwin(LINES/3, COLS/2, 0, 0);
        prog_bar = newwin(LINES/3, COLS/2, 0, COLS/2);
        proc_win = newwin((LINES/3)*2, COLS, (LINES/3), 0);
        break;

    default:
        break;
    }

    return currentState;
}


void UIRenderer::renderDashboard(const SystemInfo& sysInfo, const std::vector<ProcessInfo>& processes) {
    if (sys_win == nullptr || proc_win == nullptr || prog_bar == nullptr) {
        return;
    } 

    werase(sys_win);
    werase(proc_win);
    werase(prog_bar);
    box(sys_win, 0, 0);
    box(proc_win, 0, 0);
    box(prog_bar, 0, 0);

    // ====== Sys-info window ======
    int sys_line = 0;
    int sys_maxy = getmaxy(sys_win) - 1;
        wattron(sys_win,COLOR_PAIR(4) | A_BOLD);
        mvwprintw(sys_win, sys_line++, (COLS/4) - 13, "|=== SYSTEM  MONITOR ===|");
        wattroff(sys_win, COLOR_PAIR(4) | A_BOLD);
        
        if(sys_line < sys_maxy) mvwprintw(sys_win ,sys_line++, 1, "CPU Load: %.2f %%", sysInfo.cpu_usage);
        if(sys_line < sys_maxy) mvwprintw(sys_win ,sys_line++, 1, "CPU Temp: %.2f °C", sysInfo.cpu_temp);
        if(sys_line < sys_maxy) mvwprintw(sys_win ,sys_line++, 1, "RAM Load: %.2f %%", sysInfo.ram_usage);
        if(sys_line < sys_maxy) mvwprintw(sys_win, sys_line++, 1, "RAM Total: %.2f GB", sysInfo.total_ram_gb);
        int hours   = sysInfo.uptime / 3600;
        int minutes = (sysInfo.uptime % 3600) / 60;
        int seconds = sysInfo.uptime % 60;

        if(sys_line < sys_maxy) mvwprintw(sys_win , sys_line++, 1, "Uptime: %02d:%02d:%02d ",hours, minutes, seconds);

        if(sys_line < sys_maxy) mvwprintw(sys_win, sys_line++, 1, "Loaded processes: %d", static_cast<int>(processes.size()));

        wattron(sys_win, COLOR_PAIR(5));
        if(sys_line < sys_maxy) mvwprintw(sys_win, sys_line, 1, "'q' to quit...");
        wattroff(sys_win, COLOR_PAIR(5));
    
    // ====== Progress bar ======
    int prog_line = 0;
    int prog_maxy = getmaxy(prog_bar) - 1;

    wattron(prog_bar,COLOR_PAIR(4) | A_BOLD);
    mvwprintw(prog_bar, prog_line++, (COLS/4) - 8, "|=== STATS ===|");
    wattroff(prog_bar, COLOR_PAIR(4) | A_BOLD);

    wattron(prog_bar, A_BOLD);
    if(prog_line < prog_maxy) mvwprintw(prog_bar, prog_line ,1, "CPU ");
    wattroff(prog_bar, A_BOLD);
    if(prog_line < prog_maxy) drawProgressBar(prog_bar, prog_line++, 5, sysInfo.cpu_usage, 30);
    
    wattron(prog_bar, A_BOLD);
    if(prog_line < prog_maxy) mvwprintw(prog_bar, prog_line,1, "RAM ");
    wattroff(prog_bar, A_BOLD);
    if(prog_line < prog_maxy) drawProgressBar(prog_bar, prog_line++, 5, sysInfo.ram_usage, 30);

    // ====== Process window ====== 
    wattron(proc_win,COLOR_PAIR(4) | A_BOLD);
    mvwprintw(proc_win, 0, (COLS/2) - 10, "|=== Processes ===|");
    wattroff(proc_win, COLOR_PAIR(4) | A_BOLD);

    wattron(proc_win, COLOR_PAIR(4) | A_BOLD);
    mvwprintw(proc_win ,1, 1, "%-6s %-16s %-6s %-8s %-8s", "PID", "NAME", "STATE", "CPU%", "RAM%");
    wattroff(proc_win, COLOR_PAIR(4) | A_BOLD);

    int max_rows = (LINES / 3) * 2 - 3; // 3 comes from border above and at the buttom and the headline line so 1+1+1 = 3
    if (processes.size() < max_rows) max_rows = processes.size();

    for (int i = 0; i < max_rows; ++i) {
        const auto& p = processes[i];
        mvwprintw(proc_win ,2 + i, 1, "%-6d %-16s %-6s %-8.1f %-8.1f", 
                p.pid, 
                p.name.substr(0, 15).c_str(),
                p.state.c_str(), 
                p.cpu_usage, 
                p.ram_usage);
    }

    wrefresh(sys_win);
    wrefresh(proc_win);
    wrefresh(prog_bar);
}

void UIRenderer::drawProgressBar(WINDOW* win, int y, int x, double percentage, int bar_width) {
    
    int filled_chars = static_cast<int>((percentage / 100.0) * bar_width);

    mvwprintw(win ,y, x, "[");
    
    if (percentage > 80.0) wattron(win,COLOR_PAIR(3));      
    else if (percentage > 50.0) wattron(win,COLOR_PAIR(2)); 
    else wattron(win,COLOR_PAIR(1));                        

    for (int i = 0; i < filled_chars; ++i) {
        wprintw(win,"|");
    }
    
    wattroff(win, A_COLOR);

    for (int i = filled_chars; i < bar_width; ++i) {
        wprintw(win, ".");
    }

    wprintw(win, "] %6.2f%%", percentage);
}