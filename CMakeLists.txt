cmake_minimum_required (VERSION 2.8.11)
project (oceanofcode)
set(IMAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DIMAGE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory (src)