cmake_minimum_required(VERSION 3.16)
project(asciiConverter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Add the executable
add_executable(asciiConverter
  src/main.cpp
  src/ascii_converter.cpp
  src/ascii_converter.hpp
)

# Link the necessary libraries
target_link_libraries(asciiConverter
  PRIVATE
    ${OpenCV_LIBS}
)

# Set the output directory for the executable
set_target_properties(asciiConverter PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)