#pragma once

#ifdef PAAUDIODRIVER_EXPORTS
#define PAAUDIODRIVER_API __declspec(dllexport)
#else
#define PAAUDIODRIVER_API __declspec(dllimport)
#endif
