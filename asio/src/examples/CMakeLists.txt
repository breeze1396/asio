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

add_subdirectory(cpp11)
add_subdirectory(cpp14)
add_subdirectory(cpp17)
add_subdirectory(cpp20)