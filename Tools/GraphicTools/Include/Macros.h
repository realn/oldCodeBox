#pragma once

#ifdef GRAPHICTOOLS_EXPORTS
#define GRAPHICTOOLS_API __declspec(dllexport)
#else
#define GRAPHICTOOLS_API __declspec(dllimport)
#endif
