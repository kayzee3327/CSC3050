set(CMAKE_CXX_STANDARD 17)

add_library(
    simulation STATIC
    simulation.hpp simulation.cpp
)

link_directories(../checkpoint)
link_directories(../IInstruction)
link_directories(../initialization)
link_directories(../JInstruction)
link_directories(../RInstruction)

set(
    simulation_dependencies 
    checkpoint
    IInstruction
    initialization
    JInstruction
    RInstruction
)

add_dependencies(
    simulation
    ${simulation_dependencies}
)