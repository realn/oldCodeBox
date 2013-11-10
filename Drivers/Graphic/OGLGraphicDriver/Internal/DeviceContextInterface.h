#pragma once

#include "WinPlatform.h"

namespace CB{
	//=================================================
	//	Interface used for shered communication between 
	//	diffrent contexts.
	//=================================================
	class IDeviceContext{
	public:
		virtual HDC&	Get() const = 0;
	};
}