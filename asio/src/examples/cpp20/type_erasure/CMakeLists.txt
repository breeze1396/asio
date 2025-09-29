project(cpp20_type_erasure)
file(GLOB files *.cpp)

add_executable(${PROJECT_NAME} ${files})
link_example(${PROJECT_NAME})