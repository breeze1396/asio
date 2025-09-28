project(cpp11_futures)
file(GLOB_RECURSE CPP11_FUTURES_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(cpp11_futures)

target_sources(cpp11_futures PRIVATE ${CPP11_FUTURES_SOURCES})

link_example(${PROJECT_NAME})