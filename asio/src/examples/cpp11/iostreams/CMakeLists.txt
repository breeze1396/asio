project(cpp11_iostreams)
file(GLOB executors_files *.cpp)

foreach(file ${executors_files})
    get_filename_component(file_we ${file} NAME_WE)
    add_executable(iostreams_${file_we} ${file})
    link_example(iostreams_${file_we})
endforeach()
