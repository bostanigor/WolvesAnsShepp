cmake_minimum_required(VERSION 3.17)
project(WolvesAndSheep)

set(CMAKE_CXX_STANDARD 14)

add_executable(WolvesAndSheep main.cpp game_state.cpp game_state.h wolves_and_sheep.cpp wolves_and_sheep.h player.cpp player.h helper_structs.h)