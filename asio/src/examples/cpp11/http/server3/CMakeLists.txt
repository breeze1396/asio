project(cpp11_http_server3)
file(GLOB_RECURSE CPP11_HTTP_SERVER3_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_http_server3)

target_sources(cpp11_http_server3 PRIVATE ${CPP11_HTTP_SERVER3_SOURCES})

link_example(${PROJECT_NAME})