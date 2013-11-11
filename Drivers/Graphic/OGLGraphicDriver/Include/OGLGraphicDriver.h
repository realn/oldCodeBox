#pragma once

#include "Macros.h"
#include <GraphicDriver.h>

extern "C" OGLGRAPHICDRIVER_API CB::Graphic::IManager*	CreateManager(CB::Graphic::IDriver* pDriver, CB::Window::IManager* pWindowManager);