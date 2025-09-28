project(cpp11_http_client)
file(GLOB_RECURSE CPP11_HTTP_CLIENT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_http_client)

target_sources(cpp11_http_client PRIVATE ${CPP11_HTTP_CLIENT_SOURCES})

link_example(${PROJECT_NAME})