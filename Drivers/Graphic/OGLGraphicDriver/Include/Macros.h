#pragma once

#ifdef OGLGRAPHICDRIVER_EXPORTS
#define OGLGRAPHICDRIVER_API __declspec(dllexport)
#else
#define OGLGRAPHICDRIVER_API __declspec(dllimport)
#endif

