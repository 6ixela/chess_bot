set(SOURCES
    game.c
    game.h)

add_library(game ${SOURCES})

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../piece)
target_include_directories(game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})