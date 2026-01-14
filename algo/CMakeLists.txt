cmake_minimum_required(VERSION 3.14)
project(algo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(inc)

# --- SFML IMMER per FetchContent holen (sicherste Methode) ---
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)

# Optionen setzen, damit es schneller baut
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

# SFML bereitstellen
FetchContent_MakeAvailable(SFML)

# --- Executable ---
add_executable(sort main.cpp)

# Linken: FetchContent erzeugt Targets mit dem Prefix sfml-
target_link_libraries(sort PRIVATE sfml-graphics sfml-window sfml-system)