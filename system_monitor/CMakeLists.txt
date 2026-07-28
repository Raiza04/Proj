cmake_minimum_required(VERSION 3.12)

project(SystemMonitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

add_executable(sysmon 
    src/main.cpp 
    src/data_fetcher.cpp 
    src/ui_renderer.cpp
)

target_include_directories(sysmon PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(sysmon PRIVATE ${CURSES_LIBRARIES})