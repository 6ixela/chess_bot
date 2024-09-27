# add_library(my_project_lib my_functions.c)
# set(SOURCES
#     board.c
#     board.h
#     main.c
#     piece.c
#     piece.h
#     )

cmake_minimum_required(VERSION 3.10)

add_subdirectory(game)
add_subdirectory(piece)
add_subdirectory(bot)
add_subdirectory(move)

add_executable(${PROJECT_NAME} main.c)

# Lier les bibliothèques
target_link_libraries(${PROJECT_NAME} PRIVATE game piece bot move)