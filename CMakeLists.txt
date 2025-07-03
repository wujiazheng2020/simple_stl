cmake_minimum_required(VERSION 3.16)
project(simple_stl)

# 编译选项
set(CMAKE_CXX_FLAGS "-O3 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-O3 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
add_compile_options(-std=c++17)

# 查找依赖
find_package(glog REQUIRED)
include_directories(include)

# 添加选项开关（默认 OFF）
option(SIMPLE_STL_ENABLE_TESTS "Enable unit tests" OFF)

# 如果开启测试
if(SIMPLE_STL_ENABLE_TESTS)
  find_package(GTest REQUIRED)
  enable_testing()

  function(AddTest dir_path)
    file(GLOB_RECURSE SRCS ${dir_path}/*.cc)
    foreach(ABS_PATH ${SRCS})
      get_filename_component(EXE_NAME ${ABS_PATH} NAME_WE)
      add_executable(${EXE_NAME} ${ABS_PATH})
      target_link_libraries(${EXE_NAME}
        PRIVATE
          gtest_main
          glog::glog
          gtest
      )
      gtest_discover_tests(${EXE_NAME})
    endforeach()
  endfunction()

  AddTest(tests)
endif()

