cmake_minimum_required(VERSION 3.5)

set(PROJ_NAME TEST)
project(${PROJ_NAME})

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/backend)

set(SOURCES
	./main.cpp
)

add_executable(${PROJ_NAME} ${SOURCES})

target_link_libraries(${PROJ_NAME} SM_LIBS)
