#include "main.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    int choice = 0;
    Editor myfile;
    cout << "=====   MENU   =====" << endl;
    cout << "1.) Open File" << endl;
    cout << "2.) Show File" << endl;
    cout << "3.) Add new line at the end" << endl;
    cout << "4.) Replace a line" << endl;
    cout << "5.) Delete line" << endl;
    cout << "6.) Save File" << endl;
    cout << "7.) Exit" << endl;

    do {
        cout << "Enter your Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Error: Input not a number. Try again.\n";
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                string filename, filetype;
                cout << "Enter file name (without extension): ";
                cin >> filename;
                cout << "Enter file extension (e.g., txt): ";
                cin >> filetype;
                myfile = Editor(filename + "." + filetype);
                break;
            }
            case 2:
                myfile.printContent();
                break;
            case 3:
                myfile.addline_end();
                break;
            case 4:
                int lineNumber;
                cout << "\nwhich line do want to change? Enter a number\n" << endl;
                cin >> lineNumber;
                myfile.replaceLine(lineNumber);
                break;
            case 5:
                int line_to_delete;
                cout << "\nwhich line do want to delete? Enter a number\n" << endl;
                cin >> line_to_delete;
                myfile.deleteline(line_to_delete);
                break;
            case 6:
                myfile.save();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
