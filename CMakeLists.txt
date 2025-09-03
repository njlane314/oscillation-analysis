cmake_minimum_required(VERSION 3.10)

project(oscillation_analysis)

find_package(ROOT REQUIRED COMPONENTS Core Graf Gpad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(plot_probability plot_probability.cpp)
target_include_directories(plot_probability PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(plot_probability ${ROOT_LIBRARIES})
