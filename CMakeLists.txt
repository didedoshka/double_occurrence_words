cmake_minimum_required(VERSION 3.29.0)
project(double_occurrence_words)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_executable(main main.cpp)
add_executable(assembly_number_2 assembly_number_2.cpp)

