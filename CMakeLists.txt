cmake_minimum_required(VERSION 3.14)
project(YourProjectName)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# Google Test的头文件目录
include_directories(${CMAKE_SOURCE_DIR}/googletest/include)

# Google Test的库文件目录
link_directories(${CMAKE_SOURCE_DIR}/googletest/build/lib)

# 添加你的主项目可执行文件
add_executable(main main.cpp)

# 添加测试目标
add_executable(test_checkHit test/test_main.cpp)

# 链接Google Test库到你的测试可执行文件
target_link_libraries(test_checkHit gtest gtest_main)

# 如果需要，也可以链接你的项目库
# target_link_libraries(your_test your_project_library)