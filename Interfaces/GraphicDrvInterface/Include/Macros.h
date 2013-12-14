#pragma once

#ifdef GRAPHICMNGINTERFACE_EXPORTS
#define GRAPHICDRVINTERFACE_API __declspec(dllexport)
#else
#define GRAPHICDRVINTERFACE_API __declspec(dllimport)

#pragma comment(lib, "GraphicDrvInterface.lib")
#endif