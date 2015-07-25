#cmake mimum version.
cmake_minimum_required (VERSION 2.8)

#project info
project (demo2)

#查找目录下所有源文件
#并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(demo2 ${DIR_SRCS})
