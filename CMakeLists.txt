cmake_minimum_required(VERSION 3.10)

# set the project name
project(Maze)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)
# add the executable
include_directories(include)
# add_executable(maze main.cpp sdlHandle.cpp piece.cpp slotGrid.cpp)

file(GLOB SOURCES "src/*.cpp")
add_executable(maze ${SOURCES})

target_link_libraries(maze ${SDL2_LIBRARIES})