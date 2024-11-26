add_library(board
    board.c
    board.h
)

target_include_directories(board INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})