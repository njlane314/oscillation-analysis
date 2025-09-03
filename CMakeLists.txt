cmake_minimum_required(VERSION 3.10)

project(oscillation_analysis)

find_package(ROOT REQUIRED COMPONENTS Core Graf Gpad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(plot_probability plot_probability.cpp)
target_include_directories(plot_probability PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(plot_probability ${ROOT_LIBRARIES})

add_executable(plot_survival plot_survival.cpp)
target_include_directories(plot_survival PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(plot_survival ${ROOT_LIBRARIES})

add_executable(plot_mixing plot_mixing.cpp)
target_include_directories(plot_mixing PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(plot_mixing ${ROOT_LIBRARIES})

add_executable(plot_cp plot_cp.cpp)
target_include_directories(plot_cp PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(plot_cp ${ROOT_LIBRARIES})

add_executable(plot_baseline plot_baseline.cpp)
target_include_directories(plot_baseline PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(plot_baseline ${ROOT_LIBRARIES})

add_executable(plot_matter plot_matter.cpp)
target_include_directories(plot_matter PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(plot_matter ${ROOT_LIBRARIES})

