#pragma once

#define MZ_SEPERATOR "********************************\n"

#ifdef USE_GOOGLE_GLOG
#include "glog/logging.h"

#define LOG_0 VLOG(0) // info level
#define LOG_1 VLOG(1) // debug level

#define LOG_ERROR LOG(ERROR) // error level

#ifdef _WIN32
#pragma comment(lib, "glog.lib")
#pragma comment(lib, "gflags.lib")
#endif
#else
#include <iostream>

#define LOG_0 std::cout // info level
#define LOG_1 std::cout // debug level

#define LOG_ERROR std::cerr // error level
#endif
