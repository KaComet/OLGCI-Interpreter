cmake_minimum_required(VERSION 3.17)
project(olgci)

set(CMAKE_CXX_STANDARD 17)

# Make sure the output binary will be placed in the bin directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(olgci
        main.cpp
        src/Truthtable.cpp
        src/Truthtable.h
        src/Common.h
        src/Common.cpp
        src/Sequence.cpp
        src/Sequence.h
        include/TextTable.h)