cmake_minimum_required(VERSION 3.5)

project(TEST)

add_definitions(-std=c++11)
set(CMAKE_CXX_STANDART 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(SOURCES
    ./main.cpp
)

link_directories(/usr/local/lib)

add_executable(TEST ${SOURCES})
