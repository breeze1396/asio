project(cpp11_porthopper)
file(GLOB_RECURSE CPP11_PORTHOPPER_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_porthopper)

target_sources(cpp11_porthopper PRIVATE ${CPP11_PORTHOPPER_SOURCES})

link_example(${PROJECT_NAME})