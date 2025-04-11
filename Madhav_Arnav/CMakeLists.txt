cmake_minimum_required(VERSION 3.10)
project(SimpleTowerDefenceGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# List of source files
set(SOURCES
    src/main.cpp
    src/enemies.cpp
    src/defenders.cpp
)

# Create executable
add_executable(SimpleTowerDefenceGame ${SOURCES})
