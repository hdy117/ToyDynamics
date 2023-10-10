cmake_minimum_required(VERSION 3.14.0)

project(demos)

set(demo_root_dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${demo_root_dir}/../mz ${demo_root_dir}/../mz_core ${demo_root_dir})

add_subdirectory(${demo_root_dir}/demo_gravity_damping_drag)
add_subdirectory(${demo_root_dir}/demo_static)
add_subdirectory(${demo_root_dir}/demo_constant_spring)