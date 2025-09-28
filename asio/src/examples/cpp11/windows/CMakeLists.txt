project(cpp11_windows)
file(GLOB_RECURSE CPP11_WINDOWS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_windows)

target_sources(cpp11_windows PRIVATE ${CPP11_WINDOWS_SOURCES})

link_example(${PROJECT_NAME})