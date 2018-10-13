cmake_minimum_required(VERSION 3.5)

# Включение макросов для cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/build/cmake/macroses")
SET(CMAKE_SKIP_BUILD_RPATH TRUE)

set(SYSROOT ${CMAKE_BINARY_DIR})

# Конфигурация сборки:
set(BUILD_CONFIG "MAIN" CACHE STRING "Select build configuration")
set_property(CACHE BUILD_CONFIG PROPERTY STRINGS "MAIN" "TEST")

#set(DM_JSON_PATH sub/json/src)

if (BUILD_CONFIG STREQUAL "TEST")
    add_subdirectory(
        ./TEST
    )
elseif (BUILD_CONFIG STREQUAL "MAIN")
    add_subdirectory(
        ./MAIN
    )
endif()
