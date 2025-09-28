project(cpp11_http_server)
file(GLOB_RECURSE CPP11_HTTP_SERVER_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_http_server)

target_sources(cpp11_http_server PRIVATE ${CPP11_HTTP_SERVER_SOURCES})

link_example(${PROJECT_NAME})