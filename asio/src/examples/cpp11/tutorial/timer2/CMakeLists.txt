project(cpp11_tutorial_timer2)
file(GLOB_RECURSE CPP11_TUTORIAL_TIMER2_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_timer2)

target_sources(cpp11_tutorial_timer2 PRIVATE ${CPP11_TUTORIAL_TIMER2_SOURCES})

link_example(${PROJECT_NAME})