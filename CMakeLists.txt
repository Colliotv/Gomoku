cmake_minimum_required(VERSION 3.3)
project(Gomoku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX clang++)

include_directories(includes)
set(SOURCE_FILES main.cpp includes/referee src/referee/Piece.cpp src/referee/Board.cpp src/referee/Referee.cpp src/referee)
add_executable(Gomoku ${SOURCE_FILES})