cmake_minimum_required(VERSION 3.14.0)

project(MoZiCore)

set(lib_mozicore MoZiCore)
set(root_dir ${CMAKE_SOURCE_DIR})

# include cyclone core dir
include_directories(${root_dir}/..)

if(WIN32)
  set(lib_sys shlwapi)
esle()
  set(lib_sys pthread)
endif(WIN32)

aux_source_directory(${root_dir} src_files)

add_library(${lib_mozicore} SHARED ${src_files})
target_link_libraries(${lib_mozicore} ${lib_sys})
