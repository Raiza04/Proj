#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "main.hpp"

class Editor{
private: 
    string filename;
    string content;

public:

    
    void create();
    void save();
    void load(const string& file);
    void write();
    void del();
    void show();

};

#endif