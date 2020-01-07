cmake_minimum_required(VERSION 3.5)


add_subdirectory(StateMachine)

# StateMachine root path
target_include_directories(StateMachine_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
