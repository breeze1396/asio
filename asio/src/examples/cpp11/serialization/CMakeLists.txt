project(cpp11_serialization)
file(GLOB_RECURSE CPP11_SERIALIZATION_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_serialization)

target_sources(cpp11_serialization PRIVATE ${CPP11_SERIALIZATION_SOURCES})

link_example(${PROJECT_NAME})