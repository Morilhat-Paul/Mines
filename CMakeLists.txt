cmake_minimum_required(VERSION 3.15)
project(Mines
  LANGUAGES CXX
  VERSION 1.0
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies)
add_subdirectory(src)
