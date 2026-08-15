set(SOURCES
    game.c
    game.h)

add_library(game ${SOURCES})

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../piece)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../board)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../bitBoard)
target_include_directories(game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Game Manager library (depends on game and bot)
set(GAME_MANAGER_SOURCES
    game_manager.c
    game_manager.h)

add_library(game_manager ${GAME_MANAGER_SOURCES})

target_include_directories(game_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${CMAKE_CURRENT_SOURCE_DIR}/../bot
                                               ${CMAKE_CURRENT_SOURCE_DIR}/../move
                                               ${CMAKE_CURRENT_SOURCE_DIR}/../utils)
target_include_directories(game_manager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game_manager PUBLIC game bot move utils)