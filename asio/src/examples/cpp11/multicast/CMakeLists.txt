project(cpp11_multicast)
file(GLOB_RECURSE CPP11_MULTICAST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_multicast)

target_sources(cpp11_multicast PRIVATE ${CPP11_MULTICAST_SOURCES})

link_example(${PROJECT_NAME})