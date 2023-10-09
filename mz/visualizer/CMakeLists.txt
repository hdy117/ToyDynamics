cmake_minimum_required(VERSION 3.14.0)

project(${lib_mzvisualizer})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} vis_srcs)
file(GLOB vis_headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(${lib_mzvisualizer} SHARED ${vis_srcs} ${vis_headers})
target_link_libraries(${lib_mzvisualizer} ${lib_vis} ${lib_mzcore})
install(TARGETS ${lib_mzvisualizer} RUNTIME DESTINATION ${runtime_install_dir})