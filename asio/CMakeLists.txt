cmake_minimum_required(VERSION 3.15)
project(asio VERSION 1.36.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall 
        -Wextra 
        -Wpedantic
        -Wno-unused-parameter
        -Wno-deprecated-declarations
    )
endif()

# 创建 ASIO 接口库
add_library(asio INTERFACE)

# 设置 ASIO 头文件包含目录
target_include_directories(asio INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 设置 ASIO 编译定义
target_compile_definitions(asio INTERFACE
    ASIO_STANDALONE=1
    ASIO_NO_DEPRECATED=1
)

# 链接必要的系统库
if(WIN32)
    target_link_libraries(asio INTERFACE ws2_32 wsock32)
elseif(UNIX)
    target_link_libraries(asio INTERFACE pthread)
endif()

# 检测 C++ 功能支持
include(CheckCXXSourceCompiles)

# 检查协程支持
check_cxx_source_compiles("
    #include <coroutine>
    int main() { 
        return 0; 
    }" HAS_COROUTINES)

if(HAS_COROUTINES)
    target_compile_definitions(asio INTERFACE ASIO_HAS_CO_AWAIT)
endif()

# 选项：是否构建示例
option(ASIO_BUILD_EXAMPLES "Build ASIO examples" ON)

if(ASIO_BUILD_EXAMPLES)
    add_subdirectory(src)
endif()

# 选项：是否构建测试
option(ASIO_BUILD_TESTS "Build ASIO tests" OFF)

if(ASIO_BUILD_TESTS)
    enable_testing()
    add_subdirectory(src/tests)
endif()