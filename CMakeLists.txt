cmake_minimum_required(VERSION 2.8)
project(Gomoku)

set(CMAKE_COVERAGE_LINK_FLAGS    "-lpthread -lX11 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_COVERAGE_LINK_FLAGS}")
set(CMAKE_CXX clang++)

include_directories(includes)
set(SOURCE_FILES src/start/main.cpp includes/graphics includes/referee src/referee/Piece.cpp src/referee/Board.cpp src/referee/Referee.cpp src/referee src/graphics/sfml.cpp includes/game)
add_executable(Gomoku ${SOURCE_FILES})
