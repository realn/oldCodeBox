#pragma once

#include "Macros.h"
#include <WindowDriver.h>

extern "C" WINDOWMANAGER_API CB::Window::IManager*	CreateManager(CB::Window::IDriver* pDriver);