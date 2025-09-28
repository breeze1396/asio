project(cpp11_tutorial_daytime2)
file(GLOB_RECURSE CPP11_TUTORIAL_DAYTIME2_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_daytime2)

target_sources(cpp11_tutorial_daytime2 PRIVATE ${CPP11_TUTORIAL_DAYTIME2_SOURCES})

link_example(${PROJECT_NAME})