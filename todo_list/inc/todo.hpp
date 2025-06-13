#ifndef TODO_HPP
#define TODO_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using std::string, std::ifstream, std::ofstream;
using std::cout, std::cin, std::endl, std::vector, std::cerr;

class Todo{
private:
    vector<std::pair<string, int>> mytodo;
public:
    Todo();
    void showTasks();
    void addTask(string task);
    void deleteTask(int index);
    void editTask(int index);
    void save();
};

bool getIntInput(int& result);
void showmenu();

#endif