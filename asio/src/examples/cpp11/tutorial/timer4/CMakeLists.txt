project(cpp11_tutorial_timer4)
file(GLOB_RECURSE CPP11_TUTORIAL_TIMER4_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_timer4)

target_sources(cpp11_tutorial_timer4 PRIVATE ${CPP11_TUTORIAL_TIMER4_SOURCES})

link_example(${PROJECT_NAME})