project(cpp11_allocation)
file(GLOB_RECURSE CPP11_ALLOCATION_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_allocation)

target_sources(cpp11_allocation PRIVATE ${CPP11_ALLOCATION_SOURCES})

link_example(${PROJECT_NAME})