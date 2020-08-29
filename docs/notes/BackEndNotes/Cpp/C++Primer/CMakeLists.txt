# LEETCODE PROJECT CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(CppPrimer)

set(CMAKE_CXX_STANDARD 11)

#aux_source_directory(. SRC_LIST)
#add_library(LEETCODE ${SRC_LIST})

add_executable(CppPrimer ch13/13.4.cpp ch13/Message.cpp ch13/Folder.cpp)

message("pan: build with debug mode.")