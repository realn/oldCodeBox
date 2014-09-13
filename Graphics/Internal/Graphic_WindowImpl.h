#pragma once

#include <Types.h>
#include <SmartPointers_RefPtr.h>

#include "../Include/Graphic_Window.h"

#include <Windows.h>

namespace CB {
	namespace Internal{
		class CWindowClass;
	}

	namespace Graphic {
		class CWindow::CWindowImpl{
		public:
			CRefPtr<Internal::CWindowClass>	pWinClass;
			HWND	hWindow;
			Style	uStyle;
		};
	}
}