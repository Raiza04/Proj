#include "editor.hpp"

void Editor::create(){
    content = "";
    cout << "New file has been created ... \n";

}

void Editor::save(){
    if (filename.empty())
    {
        cout << "No file provided. Enter the name of the file you wnat to save ..." << endl;
        getline(std::cin, filename);
    }

    ofstream out(filename);
    if (out)
    {
        out << content;
        out.close();
        cout << "DThe file has been saved ... \n";
    } else {
        cout << "Error. The file could not be loaded ... \n";
    }
}

void Editor::load(const string& file){
    ifstream in(file);
    if(in){
        filename = file;
        content = "";
        string line;
        while (getline(cin, line))
        {
            content += line + "\n";
        }
        in.close();
        cout << "File successfully loaded ... \n";
    } else {
        cout << "Failed to load the file ... \n";
    }
}

void Editor::write(){
    string line;
    getline(cin, line);
    content += line + "\n";
}

void Editor::del(){
    ofstream out(filename);

    if (out)
    {
        content = "";
    }
    
    
}

void Editor::show(){

    string text;    
    while (getline(cin, text))
    {
        cout << text << endl;
    }
    
}