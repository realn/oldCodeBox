#pragma once

#ifdef OALAUDIODRIVER_EXPORTS
#define OALAUDIODRIVER_API __declspec(dllexport)
#else
#define OALAUDIODRIVER_API __declspec(dllimport)
#endif
