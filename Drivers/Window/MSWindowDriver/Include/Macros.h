#pragma once

#ifdef WINDOWMANAGER_EXPORTS
#define WINDOWMANAGER_API __declspec(dllexport)
#else
#define WINDOWMANAGER_API __declspec(dllimport)
#endif
