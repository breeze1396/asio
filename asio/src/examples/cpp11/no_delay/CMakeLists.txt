project(test_no_delay)
file(GLOB files *.cpp)

foreach(file ${files})
    get_filename_component(file_we ${file} NAME_WE)
    add_executable(${PROJECT_NAME}_${file_we} ${file})
    link_example(${PROJECT_NAME}_${file_we})
endforeach()