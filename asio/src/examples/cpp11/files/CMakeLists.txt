project(cpp11_files)
file(GLOB_RECURSE CPP11_FILES_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_files)

target_sources(cpp11_files PRIVATE ${CPP11_FILES_SOURCES})

link_example(${PROJECT_NAME})