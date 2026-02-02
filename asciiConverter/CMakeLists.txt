cmake_minimum_required(VERSION 3.16)
project(asciiConverter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sucht nach einer installierten OpenCV Version auf dem PC
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBRARIES}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(asciiConverter src/main.cpp src/ascii_converter.cpp)

# Verlinkt Header und Libraries automatisch
target_link_libraries(asciiConverter PRIVATE ${OpenCV_LIBRARIES})
target_include_directories(asciiConverter PRIVATE ${OpenCV_INCLUDE_DIRS})
