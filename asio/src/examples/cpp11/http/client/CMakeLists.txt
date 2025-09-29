project(cpp11_http_client)

file(GLOB executors_files *.cpp)

foreach(file ${executors_files})
    get_filename_component(file_we ${file} NAME_WE)
    add_executable(http_client_${file_we} ${file})
    link_example(http_client_${file_we})
endforeach()