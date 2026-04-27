set(SOURCES
    bitBoard.c
    bitBoard.h)

add_library(bitBoard ${SOURCES})

target_include_directories(bitBoard INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})