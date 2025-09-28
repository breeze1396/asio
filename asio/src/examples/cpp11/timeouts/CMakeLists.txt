project(cpp11_timeouts)
file(GLOB_RECURSE CPP11_TIMEOUTS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_timeouts)

target_sources(cpp11_timeouts PRIVATE ${CPP11_TIMEOUTS_SOURCES})

link_example(${PROJECT_NAME})