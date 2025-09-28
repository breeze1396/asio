project(cpp11_http_server2)
file(GLOB_RECURSE CPP11_HTTP_SERVER2_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_http_server2)

target_sources(cpp11_http_server2 PRIVATE ${CPP11_HTTP_SERVER2_SOURCES})

link_example(${PROJECT_NAME})