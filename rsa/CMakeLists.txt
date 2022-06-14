#cmake mimum version.
cmake_minimum_required(VERSION 2.8)

#project info
project(rsa)

include_directories(include /opt/homebrew/opt/openssl/include)
link_directories(/opt/homebrew/opt/openssl/lib)

# 指定生成目标
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ssl crypto pthread dl)