project(cpp11_icmp)
file(GLOB_RECURSE CPP11_ICMP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_icmp)

target_sources(cpp11_icmp PRIVATE ${CPP11_ICMP_SOURCES})

link_example(${PROJECT_NAME})