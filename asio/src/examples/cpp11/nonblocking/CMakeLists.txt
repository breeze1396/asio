project(cpp11_nonblocking)
file(GLOB_RECURSE CPP11_NONBLOCKING_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_nonblocking)

target_sources(cpp11_nonblocking PRIVATE ${CPP11_NONBLOCKING_SOURCES})

link_example(${PROJECT_NAME})