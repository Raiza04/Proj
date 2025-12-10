# 🎨 Sort Visualizer

A real-time sorting algorithm visualization tool built with C++ and SFML. Watch Bubble Sort, Quick Sort, Merge Sort, and Insertion Sort come to life with fully customizable parameters.

![Sort Visualizer Demo](https://via.placeholder.com/800x400?text=Sorting+Visualizer+Demo)

## ✨ Features

- **4 Sorting Algorithms**: Bubble, Quick, Merge, and Insertion Sort
- **Real-time Visualization**: See every comparison and swap as it happens
- **Fully Customizable**: Control algorithm, bar count, and speed via CLI
- **Argument Order Independence**: Flags can be used in any order
- **Auto-Scaling**: Dynamic bar width fits any window size
- **User-Friendly Build**: CMake + build script handles dependencies automatically

## 📋 Requirements

- **C++17** compatible compiler (GCC, Clang, MSVC)
- **CMake** 3.10+ (for build configuration)
- **No manual library installation needed** - CMake handles SFML automatically!

## 🛠️ Quick Start

### 1. Clone Repository
```bash
git clone <repository-url>
cd algo
```

### 2. Build & Run
```bash
# Make build script executable (first time only)
chmod +x build.sh

# Build the project
./build.sh

# Run with default settings
./build/sort
```

The `build.sh` script automatically:
- Creates a build directory
- Configures CMake
- Downloads SFML if not found
- Compiles everything
- Places executable in `./build/`

## 🚀 Usage

```bash
./build/sortvis -a <algorithm> -n <bar_count> -s <speed>
```

### Command-Line Arguments

| Flag | Description | Default | Options |
|------|-------------|---------|---------|
| `-a` | Sorting algorithm to visualize | `bubble` | `quick`, `merge`, `insert`, `bubble` |
| `-n` | Number of bars to sort | `300` | 1 - 800 (max window width) |
| `-s` | Delay between steps (ms) | `10` | Any non-negative integer |

### Examples

**Quicksort with 150 bars at 5ms speed:**
```bash
./build/sortvis -a quick -n 150 -s 5
```

**Bubblesort with 100 bars at max speed:**
```bash
./build/sortvis -a bubble -n 100 -s 0
```

**Mergesort with default settings:**
```bash
./build/sortvis -a merge
```

**Argument order doesn't matter!**
```bash
./build/sortvis -s 20 -n 200 -a insert  # Same as ./sortvis -a insert -n 200 -s 20
```

## 📁 Project Structure

```
algo/
├── CMakeLists.txt       # CMake configuration (handles SFML automatically)
├── build.sh            # One-click build script
├── README.md           # This file
├── main.cpp            # Entry point & argument parsing
└── inc/
    ├── main.hpp        # Core functions & global variables
    ├── bubblesort.hpp  # Bubble Sort implementation
    ├── quicksort.hpp   # Quick Sort implementation
    ├── mergesort.hpp   # Merge Sort implementation
    └── insertion.hpp   # Insertion Sort implementation
```

## 🎮 Controls & Visuals

- **Close Window**: Click X or press `Alt+F4` / `Cmd+Q`
- **Visual Indicators**:
  - ⚪ White bars: Unsorted elements
  - 🔴 Red bar: Currently being compared/swapped
- **Real-time Updates**: See algorithm progress step-by-step

## 💡 Pro Tips

- **Smooth animation**: `-s 5` to `-s 20`
- **Speed testing**: `-s 0` for maximum speed
- **Better visibility**: `-n 50` to `-n 150`
- **Quick preview**: Use fewer bars (`-n 50`) for faster demonstration

## 🐛 Troubleshooting

**"SFML download failed"**
- Check internet connection
- CMake will fall back to system SFML if available
- On Linux: `sudo apt-get install libsfml-dev` (Ubuntu/Debian)

**"Invalid bar number" error**
- Keep `-n` between 1 and 800

**"Unknown algorithm" error**
- Use exact names: `quick`, `merge`, `insert`, or `bubble`

**CMake version too old**
- Update CMake: `pip install --upgrade cmake` or download from [cmake.org](https://cmake.org/download/)

## 🤝 Contributing

Feel free to:
- Submit issues for bugs or feature requests
- Fork the repo and create pull requests
- Add new sorting algorithms
- Improve visualization effects

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

**Happy Sorting!** Watch those bars dance! 🕺💃