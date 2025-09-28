project(cpp11_timers)
file(GLOB_RECURSE CPP11_TIMERS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_timers)

target_sources(cpp11_timers PRIVATE ${CPP11_TIMERS_SOURCES})

link_example(${PROJECT_NAME})