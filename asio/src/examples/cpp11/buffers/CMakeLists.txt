project(cpp11_reference_counted)
file(GLOB_RECURSE CPP11_ALLOCATION_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${CPP11_ALLOCATION_SOURCES})

link_example(${PROJECT_NAME})