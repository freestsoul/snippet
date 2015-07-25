#cmake mimum version.
cmake_minimum_required (VERSION 2.8)

#project info
project (demo4)

#加入配置文件,用于处理cmake对源码的处理
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/../config.h"
)

#是否使用自己的MathFunctions库
option (USE_MYMATH
  "Use provided math implementation" OFF)

#是否加入MathFunctions库
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/math")
  add_subdirectory (math)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

#查找目录下所有源文件
#并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

#添加math子目录
#add_subdirectory(math)

#指定生成目标
add_executable(demo4 ${DIR_SRCS})

#添加链接库
target_link_libraries(demo4 ${EXTRA_LIBS})