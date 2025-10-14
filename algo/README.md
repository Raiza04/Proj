# Sorting Algorithm Visualizer

This project visualizes some of the most well-known sorting algorithms using **SFML (Simple and Fast Multimedia Library)**. It provides a real-time graphical view of how each algorithm sorts an array of randomly generated bars.

## ✨ Supported Sorting Algorithms

- 🫧 **Bubble Sort**
- ⚡ **Quick Sort**
- 🧩 **Merge Sort**
- 🎚️ **Insertion Sort**

---

## 🛠 Requirements

- A C++ compiler (supporting C++11 or later)
- [CMake](https://cmake.org/)
- SFML (automatically handled by CMake)

---

## 🐧 Installation (Linux)

### Step 1: Install CMake

For Ubuntu/Debian-based systems:

```bash

sudo apt install cmake

```

For other OS such as mac os or windows you might have to compile it completly different then what is shown here.

### Step 2 build and compile

By simply running the command below you can build and compile the project with this line

```bash

./build.sh

```

Make sure that you are in the right directory (algo folder) to avoid errors

This script will:

 - Create the build/ directory if it doesn't exist
 - Run CMake to configure the project
 - Clean previous build files
 - Compile the project
 - Run the visualizer

**Note** that it is possible that the build.sh might not work on other OS than linux since it contains linux commands

---

### Hint: Grant Premission

In case you get errors stating that you lack premission to execute the build file you can fix it by running this line of code in your linux terminal

```bash

chmod +x build.sh

```

This line grants the build file the execution premission.

## 🪄 Usage

Open main.cpp and choose which sorting algorithm you want to visualize by commenting/uncommenting the corresponding lines:

```cpp

//quicksort(window, values, 0, values.size() - 1); <br>
//mergesort(window, values, 0, values.size() - 1); <br>
//sort.step(values, window); //Bubblesort <br>
insertion(window, values);

```

You can also adjust the variables in inc/main.hpp <br>

```cpp

#define BAR_NUM 200.0 // adjust the number of bars to sort
#define SLEEP 0 //adjust the speed to visulize

```

Then rebuild and run again with

```bash

./build.sh

```

---