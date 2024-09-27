cmake_minimum_required(VERSION 3.10)
project(chessBot)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g -lcriterion")

add_subdirectory(src)
add_subdirectory(tests)

