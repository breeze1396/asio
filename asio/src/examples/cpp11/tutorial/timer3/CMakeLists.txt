project(cpp11_tutorial_timer3)
file(GLOB_RECURSE CPP11_TUTORIAL_TIMER3_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_timer3)

target_sources(cpp11_tutorial_timer3 PRIVATE ${CPP11_TUTORIAL_TIMER3_SOURCES})

link_example(${PROJECT_NAME})