project(cpp11_services)
file(GLOB_RECURSE CPP11_SERVICES_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_services)

target_sources(cpp11_services PRIVATE ${CPP11_SERVICES_SOURCES})

link_example(${PROJECT_NAME})