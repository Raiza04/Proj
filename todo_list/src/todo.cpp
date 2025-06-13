#include "todo.hpp"


Todo::Todo(){
    ifstream inFile ("data.txt");
    if (!inFile.is_open())
    {
        cerr << "File could not be Open" << endl;
        cerr << "Execute the file in the right directory" << endl;
        exit(101);
    }
    
    string line;
    while(std::getline(inFile, line)){
        std::stringstream ss(line);
        int val;
        string task;
        ss >> val;
        std::getline(ss >> std::ws, task);
        mytodo.push_back({task, val});
    }
}

void Todo::showTasks(){

    int i = 1;
    for (auto& pair: mytodo)
    {
        if (pair.second == 0)
        {
            cout << i << ".) " << pair.first << " ----- " << " [ ] " << endl;

        } else {

            cout << i << ".) " << pair.first << " ----- " << " [X] " << endl;
        }
        
        i++;
    }
    
}

void Todo::addTask(string task){
    if (task.empty())
    {
        cout << "No task entered. Try again" << endl;
        return;
    }
    mytodo.push_back({task, 0});
}

void Todo::deleteTask(int index){
    if (index > 0 && index <= static_cast<int>(mytodo.size()))
    {
        mytodo.erase(mytodo.begin() + index - 1);
    } else {
        cerr << "Out of bound. Try again" << endl;
    }
}

void Todo::editTask(int index){
    if (index > 0 && index <= static_cast<int>(mytodo.size()))
    {
        if (mytodo[index - 1].second == 0)
        {
            mytodo[index - 1].second = 1;
        } else {
            mytodo[index - 1].second = 0;
        }
        
    } else {
        cerr << "Out of bound. Try again" << endl;
    }
}

void Todo::save(){
    ofstream outFile("data.txt");
    if (!outFile.is_open())
    {
        cerr << "File not found to save" << endl;
        exit(102);
    }
    
    for (auto& pair : mytodo)
    {
        outFile << pair.second << " " << pair.first << endl;
    }
    
}

bool getIntInput(int& result) {
    cin >> result;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cerr << "Invalid input. Try again" << endl;
        return false;
    }
    return true;
}

void showmenu(){

    cout << "=== MENU ===" << endl;
    cout << "1.) Show all tasks" << endl;
    cout << "2.) Add task" << endl;
    cout << "3.) Delete task" << endl;
    cout << "4.) Edit status" << endl;
    cout << "5.) Exit" << endl;

}
