cmake_minimum_required(VERSION 3.14)
project(organizer LANGUAGES CXX)

# ---- C++17 is mandatory ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- path where we want the header ----
set(NLOHMANN_JSON_HPP "${CMAKE_CURRENT_SOURCE_DIR}/json.hpp")

# ---- download header if user doesn't have it ----
if(NOT EXISTS "${NLOHMANN_JSON_HPP}")
    message(STATUS "json.hpp not found – downloading …")
    file(DOWNLOAD
         https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
         "${NLOHMANN_JSON_HPP}"
         TIMEOUT 30)
endif()

# ---- build the executable ----
add_executable(organizer organizer.cpp)

# ---- tell compiler where the header lives (same dir) ----
target_include_directories(organizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})