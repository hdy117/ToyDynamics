cmake_minimum_required(VERSION 3.14.0)

project(demo_gravity_damping_drag)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} src_files)
file(GLOB header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(demo_gravity_damping_drag ${src_files} ${header_files})
target_link_libraries(demo_gravity_damping_drag ${lib_mzcore} ${lib_glog} ${lib_sys})

install(TARGETS demo_gravity_damping_drag RUNTIME DESTINATION ${runtime_install_dir})