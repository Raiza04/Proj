cmake_minimum_required(VERSION 3.14)
project(algo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(inc)

# Versuche zuerst: lokal installiertes SFML finden
find_package(SFML 2.5 COMPONENTS graphics window system QUIET)

# Wenn nicht gefunden → automatisch herunterladen
if(NOT SFML_FOUND)
    message(STATUS "SFML nicht gefunden – wird per FetchContent heruntergeladen...")

    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
    )

    # Nur notwendige Module bauen
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
    set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SFML)
endif()

# Executable
add_executable(sort main.cpp)

# Verlinke Bibliothek (egal ob lokal oder von FetchContent)
target_link_libraries(sort sfml-graphics sfml-window sfml-system)
