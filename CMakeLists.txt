cmake_minimum_required(VERSION 3.21)
project(OnePlusLL)
set(CMAKE_CXX_STANDARD 17)

link_directories(./Tools/OpenCilk)
include_directories(./Tools/OpenCilk/include)

link_directories(./Tools/GoogleTests)
add_subdirectory(./Tools/GoogleTests/googletest)

link_directories(./Tools/PCTL)
include_directories(./Tools/PCTL/pctl/include)
include_directories(./Tools/PCTL/cmdline/include)
include_directories(./Tools/PCTL/chunkedseq/include)

add_compile_options(-g -fcilkplus -DUSE_CILK_PLUS_RUNTIME -std=c++17 )#-Rpass-analysis=loop-spawning-ti

add_executable(OnePlusLL main.cpp one_plus_l_l.h parameter_advisor.h inst.h)
target_link_libraries(OnePlusLL pthread cilkrts)

add_executable(OnePlusLL_tests run_tests.cpp)
target_link_libraries(OnePlusLL_tests pthread cilkrts gtest gtest_main)

