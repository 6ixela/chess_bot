set(SOURCES
    bot.c
    bot.h)

add_library(bot ${SOURCES})

target_include_directories(bot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../piece 
                                      ${CMAKE_CURRENT_SOURCE_DIR}/../game
                                      ${CMAKE_CURRENT_SOURCE_DIR}/../move
                                      ${CMAKE_CURRENT_SOURCE_DIR}/../utils)
target_include_directories(bot INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
