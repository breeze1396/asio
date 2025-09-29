project(cpp11_serialization)
file(GLOB files *.cpp)

foreach(file ${files})
    get_filename_component(file_we ${file} NAME_WE)
    add_executable(serialization_${file_we} ${file})
    link_example(serialization_${file_we})
endforeach()