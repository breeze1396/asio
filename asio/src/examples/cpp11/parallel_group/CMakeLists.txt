project(cpp11_parallel_group)
file(GLOB_RECURSE CPP11_PARALLEL_GROUP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_parallel_group)

target_sources(cpp11_parallel_group PRIVATE ${CPP11_PARALLEL_GROUP_SOURCES})

link_example(${PROJECT_NAME})