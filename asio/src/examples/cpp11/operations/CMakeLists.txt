project(cpp11_operations)
file(GLOB_RECURSE CPP11_OPERATIONS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_operations)

target_sources(cpp11_operations PRIVATE ${CPP11_OPERATIONS_SOURCES})

link_example(${PROJECT_NAME})