#pragma once

#include <CBString.h>
#include <Math_Rectangle.h>

namespace CB{
	class CDisplayOutputInfo{
	public:
		CString				strDevice;
		CString				strName;
		Math::CRectangle	rcBounds;
	};
}