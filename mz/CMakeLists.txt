cmake_minimum_required(VERSION 3.14.0)

add_definitions(-DSIM_BUILD_DLL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mz_core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/visualizer)