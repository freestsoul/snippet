#cmake mimum version.
cmake_minimum_required (VERSION 2.8)

#project info
project (demo3)

#查找目录下所有源文件
#并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

#添加math子目录
add_subdirectory(math)

#指定生成目标
add_executable(demo3 ${DIR_SRCS})

#添加链接库
target_link_libraries(demo3 MathFunctions)