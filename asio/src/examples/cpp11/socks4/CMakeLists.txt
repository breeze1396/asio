project(cpp11_socks4)
file(GLOB_RECURSE CPP11_SOCKS4_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_socks4)

target_sources(cpp11_socks4 PRIVATE ${CPP11_SOCKS4_SOURCES})

link_example(${PROJECT_NAME})