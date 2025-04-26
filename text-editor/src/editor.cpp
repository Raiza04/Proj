#include "editor.hpp"

void Editor::create(const string file){

}

void Editor::save(){
    if (filename.empty())
    {
        cout << "No file provided. Enter the name of the file you wnat to save ..." << endl;
        getline(std::cin, filename);
    }
    
}

void Editor::load(const string file){

}

void Editor::edit(const string file){

}

void Editor::del(const string file){

}

void Editor::show(const string file){

}