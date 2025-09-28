project(cpp11_tutorial_daytime5)
file(GLOB_RECURSE CPP11_TUTORIAL_DAYTIME5_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_daytime5)

target_sources(cpp11_tutorial_daytime5 PRIVATE ${CPP11_TUTORIAL_DAYTIME5_SOURCES})

link_example(${PROJECT_NAME})