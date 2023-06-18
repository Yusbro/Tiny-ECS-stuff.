cmake_minimum_required(VERSION 3.12)

project(end_of_times)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(../include)
file(GLOB SOURCES ../src/*.cpp)

add_executable(game ${SOURCES})
target_link_libraries(game raylib)

