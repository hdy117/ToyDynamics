cmake_minimum_required(VERSION 3.14.0)

project(gravity_damping_drag_demo)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} src_files)
file(GLOB header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(gravity_damping_drag_demo ${src_files} ${header_files})
target_link_libraries(gravity_damping_drag_demo ${lib_mzcore} ${lib_glog} ${lib_sys})

install(TARGETS gravity_damping_drag_demo RUNTIME DESTINATION ${runtime_install_dir})