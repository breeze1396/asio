# 遍历所有文件夹，如果有 CMakeLists.txt 文件，则添加子目录
file(GLOB_RECURSE SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */CMakeLists.txt)
foreach(SUBDIR ${SUBDIRS})
    get_filename_component(DIR ${SUBDIR} DIRECTORY)
    add_subdirectory(${DIR})
endforeach()