cmake_minimum_required(VERSION 3.14.0)

project(MoZi)

set(root_dir ${CMAKE_SOURCE_DIR})

option(USE_DOUBLE_OPT "use double precision" ON)

if(USE_DOUBLE_OPT)
  add_definitions(-DUSE_DOUBLE_PRECISION)
endif()

add_subdirectory(${root_dir}/mozi)
