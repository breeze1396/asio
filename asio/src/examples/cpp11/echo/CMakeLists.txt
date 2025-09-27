file(GLOB echo_files *.cpp)

foreach(file ${echo_files})
    get_filename_component(file_we ${file} NAME_WE)
    add_executable(echo_${file_we} ${file})
    link_example(echo_${file_we})
endforeach()