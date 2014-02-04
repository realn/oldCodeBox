#pragma once

#include <Types.h>

namespace CB{
	//=================================================
	//	Interface used for shered communication between 
	//	diffrent contexts.
	//=================================================
	class IDeviceContext{
	public:
		/// <summary>
		/// Return masked HDC pointer.
		/// </summary>
		/// <returns>
		/// Device Context Handle.
		/// </returns>
		virtual void*	Get() const = 0;
	};
}