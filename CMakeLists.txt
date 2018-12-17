cmake_minimum_required(VERSION 3.12)
project(IPac)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(IPac main.cpp Classes/Player.cpp Classes/Player.h)

target_link_libraries(IPac ${SDL2_LIBRARIES})