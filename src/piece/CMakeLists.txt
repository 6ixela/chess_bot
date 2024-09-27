set(SOURCES
    piece.c
    piece.h)

add_library(piece ${SOURCES})

target_include_directories(piece PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
