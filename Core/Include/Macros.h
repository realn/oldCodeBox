#pragma once

#ifdef _USRDLL
#ifdef COMMON_EXPORTS
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#pragma comment(lib, "Common.lib")
#endif
#else
#define COMMON_API
#endif