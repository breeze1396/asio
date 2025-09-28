project(cpp11_local)
file(GLOB_RECURSE CPP11_LOCAL_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_local)

target_sources(cpp11_local PRIVATE ${CPP11_LOCAL_SOURCES})

link_example(${PROJECT_NAME})