# Simple ball gravity simulator

This project simulates simple collision detection with balls using **SFML (Simple and Fast Multimedia Library)**. It provides a real-time graphical view of how the gravitational force is applied to each ball.

## ✨ Supported features

- creating balls with random radius using the left mouse button
- A new ball gets created with every collision with the outer ball. This is bounded by the variable BALL_BOUND in main.hpp

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

---

## 🪄 Usage

Just execute the build.sh file to create the window and click with the left mouse button in the window where you want.<br>
If you want to experiment with the behaviour change the global variable in main.hpp and the private variable in ball.hpp such as elasticity and more.

---