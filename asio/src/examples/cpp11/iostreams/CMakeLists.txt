project(cpp11_iostreams)
file(GLOB_RECURSE CPP11_IOSTREAMS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_iostreams)

target_sources(cpp11_iostreams PRIVATE ${CPP11_IOSTREAMS_SOURCES})

link_example(${PROJECT_NAME})