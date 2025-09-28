project(cpp11_tutorial_timer1)
file(GLOB_RECURSE CPP11_TUTORIAL_TIMER1_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_timer1)

target_sources(cpp11_tutorial_timer1 PRIVATE ${CPP11_TUTORIAL_TIMER1_SOURCES})

link_example(${PROJECT_NAME})