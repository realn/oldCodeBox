#pragma once

#ifdef AUDIODRVINTERFACE_EXPORTS
#define AUDIODRVINTERFACE_API __declspec(dllexport)
#else
#define AUDIODRVINTERFACE_API __declspec(dllimport)

#pragma comment(lib, "AudioDrvInterface.lib")
#endif
