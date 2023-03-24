cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
project(assignment2)

add_executable(
    simulator
    simulator.cpp
)
find_library(
    simu_path
    simulation
)
link_directories(
    simu_path
)
add_dependencies(
    simulator
    simulation
)