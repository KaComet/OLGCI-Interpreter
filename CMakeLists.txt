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
        include/TextTable.h 
        src/Lexer/Lexer.h 
        src/Lexer/ILexerComponent.h 
        src/Lexer/Lexer.cpp 
        src/Lexer/DefineLexerComponent.cpp 
        src/Lexer/DefineLexerComponent.h 
        src/Lexer/Environment.cpp 
        src/Lexer/Environment.h 
        src/Lexer/LexerCommon.h 
        src/Lexer/PrintLexerComponent.cpp 
        src/Lexer/PrintLexerComponent.h)


project(testing)

set(CMAKE_CXX_STANDARD 17)

# Make sure the output binary will be placed in the bin directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(testing
        testing.cpp
        src/Truthtable.cpp
        src/Truthtable.h
        src/Common.h
        src/Common.cpp
        src/Sequence.cpp
        src/Sequence.h
        include/TextTable.h 
        testing.cpp)