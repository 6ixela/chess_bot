cmake_minimum_required(VERSION 3.10)
project(chessBot C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

add_subdirectory(src)
# Ajouter les tests
# find_package(Criterion REQUIRED)
# add_executable(my_tests tests/test_my_code.c)
# target_link_libraries(my_tests Criterion::Criterion)

