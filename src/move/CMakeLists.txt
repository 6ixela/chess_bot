set(SOURCES
    move.c
    move.h)

add_library(move ${SOURCES})

target_include_directories(move PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../piece 
                                       ${CMAKE_CURRENT_SOURCE_DIR}/../game
                                       ${CMAKE_CURRENT_SOURCE_DIR}/../utils
                                       ${CMAKE_CURRENT_SOURCE_DIR}/../bitBoard)
target_include_directories(move INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})