#查找当前目录下所有源文件
#并将名称保存到DIR_LIB_SRCS变量
aux_source_directory(. DIR_LIB_SRCS)

#生成链接库
add_library(MathFunctions ${DIR_LIB_SRCS})

#指定MathFuctions库的安装路径
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)