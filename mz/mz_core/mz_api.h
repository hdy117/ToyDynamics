#pragma once

#ifdef _WIN32
#ifdef SIM_BUILD_DLL
#define SIM_API __declspec(dllexport)
#pragma message("SIM_API is __declspec(dllexport)")
#else
#define SIM_API __declspec(dllimport)
#pragma message("SIM_API is __declspec(dllimport)")
#endif
#else
#define SIM_API
#pragma message("SIM_API is empty")
#endif