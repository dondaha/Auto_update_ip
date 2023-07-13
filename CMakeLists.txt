cmake_minimum_required(VERSION 3.24)
project(Auto_update_ip)

set(CMAKE_CXX_STANDARD 17)

set(YAML_INCLUDE H:/Programs/c++/yaml-cpp-yaml-cpp-0.7.0/include)
set(YAML_LIB H:/Programs/c++/yaml-cpp-yaml-cpp-0.7.0/lib)

## 添加头文件目录
include_directories(${YAML_INCLUDE} include)

## 把src目录下的所有源文件添加到SOURCE_FILES变量中
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

## 添加ws2_32库
target_link_libraries(${PROJECT_NAME} Iphlpapi)
## 添加yaml-cpp库
target_link_libraries(${PROJECT_NAME} ${YAML_LIB}/libyaml-cppd.a)
