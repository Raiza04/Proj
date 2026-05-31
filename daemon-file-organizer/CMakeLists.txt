cmake_minimum_required(VERSION 3.10)

project(FileOrganizerDaemon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(JSON_URL "https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp")
set(JSON_DIR "${CMAKE_SOURCE_DIR}/include/nlohmann")
set(JSON_FILE "${JSON_DIR}/json.hpp")

if(NOT EXISTS "${JSON_FILE}")
	message(STATUS "Downloading nlohmann/json.hpp...")
    file(MAKE_DIRECTORY "${JSON_DIR}")
    file(DOWNLOAD "${JSON_URL}" "${JSON_FILE}" SHOW_PROGRESS)
endif()

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(file_daemon main.cpp)
