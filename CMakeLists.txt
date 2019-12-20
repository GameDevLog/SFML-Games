# cmake version
cmake_minimum_required(VERSION 3.1)

# project name
project(SFML-Games)

# c++ 11
set(CMAKE_CXX_STANDARD 11)
# sfml libs
set (PACKAGE "system" "window" "graphics" "audio" "network")
set (LIBS "sfml-system" "sfml-window" "sfml-graphics" "sfml-audio" "sfml-network")

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "/usr/local/lib/cmake/SFML")

message(${CMAKE_CURRENT_SOURCE_DIR}/src)
# list of sub subdirectory
execute_process(COMMAND ls ${CMAKE_CURRENT_SOURCE_DIR}/src OUTPUT_VARIABLE dirs)

string(REPLACE "\n" ";" dirs ${dirs})

foreach (dir ${dirs})
    message(${dir})
    add_subdirectory(src/${dir})
endforeach()
