cmake_minimum_required(VERSION 3.21)
project(OnePlusLL)
set(CMAKE_CXX_STANDARD 20)

link_directories(./Tools/OpenCilk)
include_directories(./Tools/OpenCilk/include)

link_directories(./Tools/GoogleTests)
add_subdirectory(./Tools/GoogleTests/googletest)

link_directories(./Tools/PCTL)
include_directories(./Tools/PCTL/pctl/include)
include_directories(./Tools/PCTL/cmdline/include)
include_directories(./Tools/PCTL/chunkedseq/include)

list(APPEND CMAKE_PREFIX_PATH "./Tools/LibPytorch/libtorch")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_compile_options(-g -fcilkplus -DUSE_CILK_PLUS_RUNTIME -std=c++17 )#-Rpass-analysis=loop-spawning-ti

add_executable(OnePlusLL
        main.cpp
        inst.h
        solvers/one_plus_l_l.h
        solvers/ea_parameters.h
        solvers/solver_interface.h
        advisers/basic_advisers.h
        advisers/adviser_interface.h
        tasks/task_interface.h tasks/onemax.h)

target_link_libraries(OnePlusLL pthread cilkrts)

add_executable(OnePlusLL_tests run_tests.cpp)
target_link_libraries(OnePlusLL_tests pthread cilkrts gtest gtest_main)

add_executable(PyTorch_usage main.cpp)
target_link_libraries(PyTorch_usage "${TORCH_LIBRARIES}")
set_property(TARGET PyTorch_usage PROPERTY CXX_STANDARD 14)

