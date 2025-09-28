project(cpp11_handler_tracking)
file(GLOB_RECURSE CPP11_HANDLER_TRACKING_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_handler_tracking)

target_sources(cpp11_handler_tracking PRIVATE ${CPP11_HANDLER_TRACKING_SOURCES})

link_example(${PROJECT_NAME})