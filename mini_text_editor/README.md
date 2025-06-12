# Mini Text Editor (Terminal)

**Description**  
This project is a simple text editor that runs in the terminal and only uses standard C++ libraries.  
It provides the following features:  
- Open files  
- Display file contents  
- Edit lines (add, delete, replace)  
- Save changes back to the file

**Important:**  
You must always select option 1 first to load a file. Otherwise, the program may exhibit undefined behavior.

---

## Features

| Option | Description                  |
|--------|------------------------------|
| 1      | Open a file                  |
| 2      | Show file contents           |
| 3      | Add a new line at the end    |
| 4      | Replace a line               |
| 5      | Delete a line                |
| 6      | Save changes to the file     |
| 7      | Exit the program             |

---

## Compilation and Execution

This project includes a Makefile, so you can easily build and run it by typing the following commands in your terminal:

```bash
make        # compiles the program
make run    # compiles and runs the program
make clean  # removes compiled files
````

If make is not installed on your system, you can install it on Linux by running:

```
sudo apt-get install make
```

## Example Usage
When the program starts, you will be prompted to enter the name of the file you want to edit.
After loading the file, you can use the menu options to display the contents, edit lines, and save your changes.

## Notes
Currently, there is no function to create new files.
For stable usage, always load a file first (option 1).
