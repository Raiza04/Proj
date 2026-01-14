cmake_minimum_required(VERSION 3.16)
project(asciiConverter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Try system OpenCV first
find_package(OpenCV QUIET)

if(NOT OpenCV_FOUND)
  message(STATUS "OpenCV not found on system. Fetching OpenCV...")

  FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.9.0
  )

  set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)
  set(BUILD_opencv_python OFF CACHE BOOL "" FORCE)
  set(BUILD_opencv_java OFF CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(opencv)
endif()

add_executable(asciiConverter
  src/main.cpp
  src/ascii_converter.cpp
  src/ascii_converter.hpp
)

# ✅ THIS IS THE KEY LINE
target_link_libraries(asciiConverter
  PRIVATE
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
)

set_target_properties(asciiConverter PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
