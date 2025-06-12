#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using std::cout, std::cin, std::endl, std::cerr;
using std::string, std::vector;
using std::ifstream, std::ofstream;

class Editor {
private:
    vector<string> content;
    string filename;

public:
    Editor(string fname) : filename(std::move(fname)) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "\nFile not found. Try again.\n";
            return;
        }

        string line;
        while (std::getline(inFile, line)) {
            content.push_back(line);
        }

        cout << "\nFile upload successful\n" << endl;
    }

    Editor() = default;

    void printContent() const {
        cout << "\n";
        for (const auto& line : content) {
            cout << line << endl;
        }
        cout << "\n";
    }

    void addline_end() {
        cout << "\nEnter your text and press enter:\n";
        string line;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(cin, line);
        content.push_back(line);
    }

    void replaceLine(int lineNumber) {
        int index = lineNumber - 1;
        if (index < 0 || index >= static_cast<int>(content.size())) {
            cerr << "\nInvalid line number.\n";
            return;
        }

        cout << "\nThe line you're about to change is:\n";
        cout << content[index] << endl;
        cout << "\nDo you want to continue? (y/n): ";
        char answer;
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            string line;
            cout << "\nEnter your new line:\n";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(cin, line);
            content[index] = line;
        }
    }

    void deleteline(int lineNum) {
        int index = lineNum - 1;
        if (index >= 0 && index < static_cast<int>(content.size())) {
            content.erase(content.begin() + index);
        } else {
            cerr << "Out of bounds. Make sure your number is within range.\n";
        }
    }

    void save() const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "\nFailed to open file for saving.\n";
            return;
        }

        for (const auto& line : content) {
            outFile << line << endl;
        }

        cout << "\nFile saved successfully.\n";
    }
};

#endif
