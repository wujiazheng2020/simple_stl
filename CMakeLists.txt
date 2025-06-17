cmake_minimum_required(VERSION 3.16)
project(simple_stl)

# SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
# SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")

SET(CMAKE_CXX_FLAGS "-O3 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-O3 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

add_compile_options(-std=c++11)

find_package (glog REQUIRED)

include_directories(
  include
)

# fetch gtest
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
# )
# FetchContent_MakeAvailable(googletest)
find_package(GTest REQUIRED)

# function construct
enable_testing()

function(AddTest dir_path)
  file(GLOB_RECURSE SRCS ${dir_path}/*.cc)
  foreach(ABS_PATH ${SRCS})
    get_filename_component(EXE_NAME ${ABS_PATH} NAME_WE)
    add_executable(${EXE_NAME} ${ABS_PATH})
    target_link_libraries(${EXE_NAME} gtest_main glog::glog gtest)
    gtest_discover_tests(${EXE_NAME})
  endforeach()
endfunction(AddTest)

AddTest(tests)
