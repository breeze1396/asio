project(cpp11_fork)
file(GLOB_RECURSE CPP11_FORK_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_fork)

target_sources(cpp11_fork PRIVATE ${CPP11_FORK_SOURCES})

link_example(${PROJECT_NAME})