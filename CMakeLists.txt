cmake_minimum_required(VERSION 3.14.0)

project(mz)

set(CMAKE_CXX_STANDARD 11)

set(root_dir ${CMAKE_SOURCE_DIR})
set(runtime_install_dir ${root_dir}/bin)

option(USE_DOUBLE_OPT "use double precision" ON)
option(USE_BOOST_SHARED_PTR "use boost shared_ptr" ON)
option(USE_GOOGLE_GLOG_OPT "use google glog" ON)

if(USE_DOUBLE_OPT)
  add_definitions(-DUSE_DOUBLE_PRECISION)
endif()

if(USE_BOOST_SHARED_PTR)
  add_definitions(-DUSE_BOOST_SHARED_PTR)
endif()

if(USE_GOOGLE_GLOG_OPT)
  add_definitions(-DUSE_GOOGLE_GLOG)
endif()

if(WIN32)
  set(vcpkg_root "E:\\work\\vcpkg\\installed\\x64-windows")
  include_directories(${vcpkg_root}/include)
  link_directories(${vcpkg_root}/lib)

  # Use vcpkg toolchain file
  set(CMAKE_TOOLCHAIN_FILE "${vcpkg_root}/../../scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

  add_compile_options("/MP")
  add_definitions(-D_USE_MATH_DEFINES)
  add_definitions(-DNOMINMAX)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES)

  # Find OGRE and required components
  list(APPEND CMAKE_MODULE_PATH "${vcpkg_root}/share/jxr")
  find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem Overlay)

  include_directories(${OGRE_INCLUDE_DIRS} ${OGRE_Bites_INCLUDE_DIRS} ${OGRE_RTShaderSystem_INCLUDE_DIRS} ${OGRE_Overlay_INCLUDE_DIRS})

  set(lib_sys shlwapi)
  set(lib_log glog.lib gflags.lib)
  set(lib_vis ${OGRE_LIBRARIES} ${OGRE_Bites_LIBRARIES} ${OGRE_RTShaderSystem_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
else()
  add_compile_options(-fPIC)
  add_compile_options(-Wall)

  include_directories(/usr/include/eigen3)

  # Find OGRE and required components
  find_package(OGRE REQUIRED COMPONENTS Bites Main RTShaderSystem Overlay)

  include_directories(${OGRE_INCLUDE_DIRS} ${OGRE_Bites_INCLUDE_DIRS} ${OGRE_RTShaderSystem_INCLUDE_DIRS} ${OGRE_Overlay_INCLUDE_DIRS})

  set(lib_sys pthread)
  set(lib_log glog gflags)
  set(lib_vis ${OGRE_LIBRARIES} ${OGRE_Bites_LIBRARIES} ${OGRE_RTShaderSystem_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
endif(WIN32)

# build mz_dynamics core files
set(lib_mzcore mz_core)
set(lib_mzvisualizer mz_visualizer)
add_subdirectory(${root_dir}/mz)

# build demos
add_subdirectory(${root_dir}/mz_demo)
