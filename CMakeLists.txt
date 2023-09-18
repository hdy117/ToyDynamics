cmake_minimum_required(VERSION 3.14.0)

project(mz)

set(CMAKE_CXX_STANDARD 11)

set(root_dir ${CMAKE_SOURCE_DIR})
set(runtime_install_dir ${root_dir}/bin)

option(USE_DOUBLE_OPT "use double precision" ON)
option(USE_BOOST_SHARED_PTR "use boost shared_ptr" ON)

if(USE_DOUBLE_OPT)
  add_definitions(-DUSE_DOUBLE_PRECISION)
endif()

if(USE_BOOST_SHARED_PTR)
  add_definitions(-DUSE_BOOST_SHARED_PTR)
endif()

if(WIN32)
  set(vcpkg_root "E:\\work\\vcpkg\\installed\\x64-windows")
  include_directories(${vcpkg_root}/include)
  link_directories(${vcpkg_root}/lib)

  add_compile_options("/MP")
  add_definitions(-D_USE_MATH_DEFINES)
  add_definitions(-DNOMINMAX)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES)

  set(lib_sys shlwapi)
  set(lib_log glog.lib gflags.lib)
else()
  add_compile_options(-fPIC)
  add_compile_options(-Wall)

  include_directories(/usr/include/eigen3)
  set(lib_sys pthread)
  set(lib_log glog gflags)
endif(WIN32)

# build mz_dynamics core files
set(lib_mzcore mz_core)
add_subdirectory(${root_dir}/mz)

# build demos
add_subdirectory(${root_dir}/mz_demo)
