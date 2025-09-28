project(cpp11_tutorial_daytime4)
file(GLOB_RECURSE CPP11_TUTORIAL_DAYTIME4_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_tutorial_daytime4)

target_sources(cpp11_tutorial_daytime4 PRIVATE ${CPP11_TUTORIAL_DAYTIME4_SOURCES})

link_example(${PROJECT_NAME})