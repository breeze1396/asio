project(cpp11_tutorial_timer5)
file(GLOB_RECURSE CPP11_TUTORIAL_TIMER5_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_timer5)

target_sources(cpp11_tutorial_timer5 PRIVATE ${CPP11_TUTORIAL_TIMER5_SOURCES})

link_example(${PROJECT_NAME})