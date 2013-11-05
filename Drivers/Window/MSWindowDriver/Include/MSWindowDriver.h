#pragma once

#include "Macros.h"
#include "../../WindowDrvInterface/Include/WindowDriver.h"
#include "../../Common/Include/Module.h"

extern "C" WINDOWMANAGER_API CB::Window::IManager*	CreateManager(CB::Window::IDriver* pDriver);