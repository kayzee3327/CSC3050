set(CMAKE_CXX_STANDARD 17)

add_library(
    RInstruction STATIC
    RInstruction.hpp RInstruction.cpp
    Syscall Syscall.cpp
)

