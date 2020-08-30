# LEETCODE PROJECT CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(LEETCODE)

set(CMAKE_CXX_STANDARD 11)

#aux_source_directory(. SRC_LIST)
#add_library(LEETCODE ${SRC_LIST})

add_executable(LEETCODE edit-distance.cpp base-dp.cpp)

message("pan: build with debug mode.")



## 指定 CMAKE 的最小版本，它是是可选的
#cmake_minimum_required(VERSION 3.16)
#
#
## 设置项目名称，它是是可选的。它会引入两个变量 LEETCODE_BINARY_DIR 和 LEETCODE_SOURCE_DIR，
## 同时，CMAKE 自动定义了两个等价的变量 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR。
#project(LEETCODE)
#
#
## 设置 C++ 标准的版本
#set(CMAKE_CXX_STANDARD 11)
#
#
## 指定编译包含的源文件
## 1. 明确指定包含哪些源文件
#add_library(LEETCODE leetcode.cpp leetcode1.cpp leetcode2.cpp)
## 2. 搜索所有的 cpp 文件
#aux_source_directory(. SRC_LIST) # 搜索当前目录下的所有.cpp文件，并将列表存储在一个变量中
#add_library(LEETCODE ${SRC_LIST})   # 将列表内容包含进去
## 3. 自定义搜索规则
#file(GLOB SRC_LIST "*.cpp" "protocol/*.cpp")
#add_library(LEETCODE ${SRC_LIST})
#
#
## 设置包含的目录
#include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
#
#
## 设置链接库的目录
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
#
#
## 设置变量
## 1. set 直接设置变量的值
#set(SRC_LIST main.cpp test.cpp)
#add_executable(LEETCODE ${SRC_LIST})
#
## 2. set 追加设置变量的值
#set(SRC_LIST main.cpp)
#set(SRC_LIST ${SRC_LIST} test.cpp)
#add_executable(LEETCODE ${SRC_LIST})
#
## 3. list 追加或者删除变量的值
#set(SRC_LIST main.cpp)
#list(APPEND SRC_LIST test.cpp)
#list(REMOVE_ITEM SRC_LIST main.cpp)
#add_executable(LEETCODE ${SRC_LIST})
#
#
## 条件控制
#
#
## 打印信息
##message(${PROJECT_SOURCE_DIR})
##message("build with debug mode")
##message(WARNING "this is WARNING message")
##message(FATAL_ERROR "this build has many error") # FATAL_ERROR 会导致编译失败
#
#
## 包含其他 CMAKE 文件
#include(./common.cmake) # 指定包含文件的全路径
#
#
## 设置编译类型
## 1. 生成可执行文件。在 Windows 下得到 leetcode.exe。在 Linux 下得到 leetcode。
#add_executable(LEETCODE leetcode.cpp)
#
## 2. 生成静态库。在 Windows 下得到 leetcode.lib。在 Linux 下得到 leetcode.a。
#add_library(common STATIC leetcode.cpp)
#
## 3. 生成动态库或共享库。在 Windows 下得到 leetcode.dll。在 Linux 下得到 leetcode.so。
#add_library(common SHARED leetcode.cpp)
#
#
## 常用变量
## 1. 预定义变量
##PROJECT_SOURCE_DIR：工程的根目录
##PROJECT_BINARY_DIR：运行 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}/build
##PROJECT_NAME：返回通过 project 命令定义的项目名称
##CMAKE_CURRENT_SOURCE_DIR：当前处理的 CMakeLists.txt 所在的路径
##CMAKE_CURRENT_BINARY_DIR：target 编译目录
##CMAKE_CURRENT_LIST_DIR：CMakeLists.txt 的完整路径
##CMAKE_CURRENT_LIST_LINE：当前所在的行
##CMAKE_MODULE_PATH：定义自己的 cmake 模块所在的路径，SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)，然后可以用INCLUDE命令来调用自己的模块
##EXECUTABLE_OUTPUT_PATH：重新定义目标二进制可执行文件的存放位置
##LIBRARY_OUTPUT_PATH：重新定义目标链接库文件的存放位置
#
## 2. 环境变量
##$ENV{Name}  # 使用环境变量
##set(ENV{Name} value) # 写入环境变量
#
## 3. 系统信息
##CMAKE_MAJOR_VERSION：cmake 主版本号，比如 3.4.1 中的 3
##CMAKE_MINOR_VERSION：cmake 次版本号，比如 3.4.1 中的 4
##CMAKE_PATCH_VERSION：cmake 补丁等级，比如 3.4.1 中的 1
##CMAKE_SYSTEM：系统名称，比如 Linux-­2.6.22
##CMAKE_SYSTEM_NAME：不包含版本的系统名，比如 Linux
##CMAKE_SYSTEM_VERSION：系统版本，比如 2.6.22
##CMAKE_SYSTEM_PROCESSOR：处理器名称，比如 i686
##UNIX：在所有的类 UNIX 平台下该值为 TRUE，包括 OS X 和 cygwin
##WIN32：在所有的 win32 平台下该值为 TRUE，包括 cygwin
#
#
## 参考链接：http://mrdede.com/?p=3754