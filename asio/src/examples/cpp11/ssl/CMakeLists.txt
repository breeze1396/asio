project(cpp11_ssl)
file(GLOB_RECURSE CPP11_SSL_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_ssl)

target_sources(cpp11_ssl PRIVATE ${CPP11_SSL_SOURCES})

link_example(${PROJECT_NAME})