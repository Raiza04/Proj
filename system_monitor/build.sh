#!/bin/bash
set -e

echo "=== Starting the build-process for the System Monitor ... ==="

mkdir -p build
cd build

echo "=== Configuring CMake ... ==="
cmake ..

echo "=== Compiling Projekt ... ==="
make

cd ..

echo "=== Build successful!!! ==="
echo "You can start the monitor with: ./build/sysmon"
