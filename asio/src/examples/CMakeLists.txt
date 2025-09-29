# ASIO 示例构建配置

# 设置boost所有的组件
set(BOOST_LIBS 
    "system"
    "atomic"
    "program_options"
    "test_exec_monitor"
    "container"
    "graph"
    "regex"
    "timer"
    "context"
    "iostreams"
    "serialization"
    "type_erasure"
    "contract"
    "log"
    "stacktrace_basic"
    "unit_test_framework"
    "coroutine"
    "log_setup"
    "stacktrace_noop"
    "wserialization"
)



find_package(Boost REQUIRED COMPONENTS ${BOOST_LIBS})
find_package(OpenSSL QUIET)
if(OpenSSL_FOUND)
    message(STATUS "OpenSSL found, SSL examples will be available")
endif()

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
    message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
endif()


# 用于自动发现示例的函数
function(link_example project_name)
    target_link_libraries(${project_name} PRIVATE 
        asio
        ${Boost_LIBRARIES}
    )

    # 如果找到了 OpenSSL，则链接它
    if(OpenSSL_FOUND)
        target_link_libraries(${project_name} PRIVATE 
            OpenSSL::Crypto
            OpenSSL::SSL
        )
    endif()
endfunction()


# 递归遍历当前文件夹及子文件夹，查找所有 CmakeLists.txt 文件
file(GLOB_RECURSE example_cmake_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    */CMakeLists.txt
)

if(APPLE)
    list(FILTER example_cmake_files EXCLUDE REGEX ".*windows.*")
    list(FILTER example_cmake_files EXCLUDE REGEX ".*files.*")
endif()


foreach(cmake_file ${example_cmake_files})
    # 获取示例目录
    get_filename_component(example_dir ${cmake_file} DIRECTORY)
    get_filename_component(example_name ${example_dir} NAME)
    
    # 添加子目录
    add_subdirectory(${example_dir})
endforeach()
