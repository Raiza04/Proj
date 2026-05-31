#!/bin/bash

# Exit immediately if a command fails
set -e

echo "=== Starting build process for FileOrganizerDaemon ==="

# 1. Create build directory (if it doesn't exist)
mkdir -p build

# 2. Enter the directory
cd build

# 3. Let CMake generate the Makefiles (and download json.hpp if needed)
echo "=== Configuring CMake ==="
cmake ..

# 4. Compile the project
echo "=== Compiling project ==="
make

# 5. Return to the main directory
cd ..

echo "=== Build completed successfully! ==="
echo "You can now start your daemon with:"
echo "./build/file_daemon"
