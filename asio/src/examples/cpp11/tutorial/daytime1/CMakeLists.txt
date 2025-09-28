project(cpp11_tutorial_daytime1)
file(GLOB_RECURSE CPP11_TUTORIAL_DAYTIME1_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_daytime1)

target_sources(cpp11_tutorial_daytime1 PRIVATE ${CPP11_TUTORIAL_DAYTIME1_SOURCES})

link_example(${PROJECT_NAME})