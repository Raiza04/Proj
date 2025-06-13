#include "todo.hpp"

int main(void){

    int choice = 0;
    Todo todoList;

    do
    {
        showmenu();
        cout << "Enter your choice" << endl;
        if (!getIntInput(choice))
        {
            continue;
        }
        
        switch (choice)
        {
        case 1:
            todoList.showTasks();
            break;

        case 2:{
            string task;
            cout << "\nEnter the task ..." << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(cin, task);
            todoList.addTask(task);
            break;
        }
        
        case 3:{
            int index;
            cout << "\nEnter which task you want to remove (number of the task) ..." << endl;
            todoList.showTasks();
            if (!getIntInput(index))
            {
                break;
            }

            todoList.deleteTask(index);
            break;
        }


        case 4:{
            int index;
            cout << "\nWhich task do want to update? Enter the number ..." << endl;
            todoList.showTasks();
            if (!getIntInput(index))
            {
                break;
            }

            todoList.editTask(index);
            break;
        }

        case 5:
            todoList.save();
            break;
        
        default:
            cout << "Invalid choice. Try again" << endl;
            break;
        }


    } while (choice != 5);
    
    

    return 0;
}