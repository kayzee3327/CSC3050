cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
project(assignment2)

add_executable(
    simulator
    simulation.cpp
)

add_subdirectory(checkpoint)
add_subdirectory(IInstruction)
add_subdirectory(JInstruction)
add_subdirectory(RInstruction)
add_subdirectory(initialization)

target_link_libraries(
    simulator
    checkpoint
    IInstruction
    JInstruction
    RInstruction
    initialization
)

