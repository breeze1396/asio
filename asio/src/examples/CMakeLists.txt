# ASIO 示例构建配置

find_package(Boost)
find_package(OpenSSL QUIET)
if(OpenSSL_FOUND)
    message(STATUS "OpenSSL found, SSL examples will be available")
endif()


# 用于自动发现示例的函数
function(link_example project_name)
        target_link_libraries(${project_name} PRIVATE 
            asio
            Boost::boost
            OpenSSL::Crypto
        )
endfunction()


# 递归遍历当前文件夹及子文件夹，查找所有 CmakeLists.txt 文件
file(GLOB_RECURSE example_cmake_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    */CMakeLists.txt
)

foreach(cmake_file ${example_cmake_files})
    # 获取示例目录
    get_filename_component(example_dir ${cmake_file} DIRECTORY)
    get_filename_component(example_name ${example_dir} NAME)
    
    # 添加子目录
    add_subdirectory(${example_dir})
endforeach()
