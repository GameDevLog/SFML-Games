cmake_minimum_required(VERSION 3.1)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" TARGET_NAME ${TARGET_NAME})

set(SRC main.cpp)

project(${TARGET_NAME})
message(${TARGET_NAME})

find_package(SFML 2.5 COMPONENTS ${PACKAGE} REQUIRED)
add_executable(${TARGET_NAME} ${SRC})
target_link_libraries(${TARGET_NAME} ${LIBS})
