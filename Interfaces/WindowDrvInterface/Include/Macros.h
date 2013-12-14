#pragma once

#ifdef WINDOWMNGINTERFACE_EXPORTS
#define WINDOWDRVINTERFACE_API __declspec(dllexport)
#else
#define WINDOWDRVINTERFACE_API __declspec(dllimport)

#pragma comment(lib, "WindowDrvInterface.lib")
#endif