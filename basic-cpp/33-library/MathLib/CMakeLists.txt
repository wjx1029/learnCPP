# 同时构建静态库和动态库

cmake_minimum_required(VERSION 3.0)
project(MyMathLib)

# 定义宏用于导出符号（仅在 Windows 平台）
if (WIN32)
    add_definitions(-DMYMATH_EXPORTS)
endif()

# 指定库的头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 创建静态库
add_library(mymath_static STATIC src/mymath.cpp)

# 创建动态库
add_library(mymath_shared SHARED src/mymath.cpp)

# 设置静态库的版本号（可选）
set_target_properties(mymath_static PROPERTIES VERSION 1.0.0 SOVERSION 1)

# 设置动态库的版本号（可选）
set_target_properties(mymath_shared PROPERTIES VERSION 1.0.0 SOVERSION 1)

# 安装静态库和动态库
install(TARGETS mymath_static mymath_shared
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

# 安装头文件
install(FILES include/mymath.h DESTINATION include)