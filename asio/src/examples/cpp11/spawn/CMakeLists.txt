project(cpp11_spawn)
file(GLOB_RECURSE CPP11_SPAWN_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_spawn)

target_sources(cpp11_spawn PRIVATE ${CPP11_SPAWN_SOURCES})

link_example(${PROJECT_NAME})