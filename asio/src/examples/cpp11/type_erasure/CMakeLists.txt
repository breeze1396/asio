project(cpp11_type_erasure)
file(GLOB_RECURSE CPP11_TYPE_ERASURE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_type_erasure)

target_sources(cpp11_type_erasure PRIVATE ${CPP11_TYPE_ERASURE_SOURCES})

link_example(${PROJECT_NAME})