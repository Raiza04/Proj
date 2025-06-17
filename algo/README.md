# Sorting Algorithm Visualizer

This project visualizes some of the most well-known sorting algorithms using **SFML (Simple and Fast Multimedia Library)**. It provides a real-time graphical view of how each algorithm sorts an array of randomly generated bars.

## ✨ Supported Sorting Algorithms

- 🫧 **Bubble Sort**
- ⚡ **Quick Sort**
- 🧩 **Merge Sort**

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

### Step 2: Grant premission

To be able to execute the build file you have to grant it execution premission. You can do that with

```bash

chmod +x build.sh

```

### Step 3: build and compile

By simply running the command below you can build and compile the project

```bash

./build.sh

```

This script will:

 - Create the build/ directory if it doesn't exist
 - Run CMake to configure the project
 - Clean previous build files
 - Compile the project
 - Run the visualizer

## Usage

Open main.cpp and choose which sorting algorithm you want to visualize by commenting/uncommenting the corresponding lines:

´´´cpp

// bubbleSort(window, values);
// quicksort(window, values, 0, values.size() - 1);
mergesort(window, values, 0, values.size() - 1);

´´´

Then rebuild and run again with

```bash

./build.sh

```

