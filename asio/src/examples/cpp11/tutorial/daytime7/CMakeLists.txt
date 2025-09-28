project(cpp11_tutorial_daytime7)
file(GLOB_RECURSE CPP11_TUTORIAL_DAYTIME7_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_daytime7)

target_sources(cpp11_tutorial_daytime7 PRIVATE ${CPP11_TUTORIAL_DAYTIME7_SOURCES})

link_example(${PROJECT_NAME})