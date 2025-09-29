project(cpp11_multicast)
file(GLOB executors_files *.cpp)

foreach(file ${executors_files})
    get_filename_component(file_we ${file} NAME_WE)
    add_executable(multicast_${file_we} ${file})
    link_example(multicast_${file_we})
endforeach()