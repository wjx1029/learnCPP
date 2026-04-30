cmake_minimum_required(VERSION 3.0)
project(MyApp)

# 指定库的头文件路径
include_directories(${CMAKE_SOURCE_DIR}/../MathLib/include)

# 添加可执行文件
add_executable(MyApp main.cpp)

# 链接静态库或动态库

# 静态库
# target_link_libraries(MyApp ${CMAKE_SOURCE_DIR}/../MathLib/build/lib/libmymath_static.a)

# 动态库（需要确保运行时可以找到动态库）
target_link_libraries(MyApp ${CMAKE_SOURCE_DIR}/../MathLib/build/lib/libmymath_shared.so)

