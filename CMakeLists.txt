cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CURRENT_SOURCE_DIR ./)

# add dirs
add_subdirectory(./backend)
add_subdirectory(./frontend)
