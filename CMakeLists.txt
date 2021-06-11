cmake_minimum_required(VERSION 3.13)
project(leetcode)

set(CMAKE_CXX_STANDARD 14)
add_definitions("-g")
add_executable(leetcode zg_tool.hpp dp_set.cpp)
#add_executable(leetcode zg_tool.hpp tencent_tpc.cpp)