project(cpp11_invocation)
file(GLOB_RECURSE CPP11_INVOCATION_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_invocation)

target_sources(cpp11_invocation PRIVATE ${CPP11_INVOCATION_SOURCES})

link_example(${PROJECT_NAME})