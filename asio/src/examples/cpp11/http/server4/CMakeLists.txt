project(cpp11_http_server4)
file(GLOB_RECURSE CPP11_HTTP_SERVER4_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_http_server4)

target_sources(cpp11_http_server4 PRIVATE ${CPP11_HTTP_SERVER4_SOURCES})

link_example(${PROJECT_NAME})