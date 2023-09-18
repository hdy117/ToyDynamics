cmake_minimum_required(VERSION 3.14.0)

project(${lib_mzcore})

set(CMAKE_CXX_STANDARD 11)

set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${root_dir})

if(WIN32)

else()

endif(WIN32)

file(GLOB header_files "${root_dir}/*.h")
aux_source_directory(${root_dir} src_files)

message(STATUS "srcfiles:${src_files}")
message(STATUS "module:${lib_mozicore}")
add_library(${lib_mzcore} SHARED ${header_files} ${src_files})
target_link_libraries(${lib_mzcore} ${lib_log} ${lib_sys})
install(TARGETS ${lib_mzcore} RUNTIME DESTINATION ${runtime_install_dir})
