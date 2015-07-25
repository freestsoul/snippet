#cmake mimum version.
cmake_minimum_required (VERSION 2.8)

#project info
project (demo5)

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
add_executable(demo5 ${DIR_SRCS})

#添加链接库
target_link_libraries(demo5 ${EXTRA_LIBS})

#指定安装路径
install (TARGETS demo5 DESTINATION bin)
install (FILES "${POJECT_BINARY_DIR}/config.h"
  DESTINATION include)

#启用测试
enable_testing()

#测试程序是否成功运行
add_test (test_run demo5 5 2)

#测试帮助信息是否可以正常提示
add_test (test_usage demo5)
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "usage: .* base exponent")

#测试5的平方
add_test (test_5_2 demo5 5 2)
set_tests_properties (test_5_2
  PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

#定义一个宏，用于简化测试工作
macro (do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} demo5 ${arg1} ${arg2})
  set_tests_properties (test_${arg1}_${arg2}
	PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

#利用宏测试一系列数据
do_test (5 2 "is 25")
do_test (10 5 "is 100000")
do_test (2 10 "is 1024")
