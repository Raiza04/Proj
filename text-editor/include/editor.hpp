#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "main.hpp"

class Editor{
private: 
    string filename;
    string content;

public:

    
    void create(const string file);
    void save();
    void load(const string file);
    void edit(const string file);
    void del(const string file);
    void show(const string file);

};

#endif