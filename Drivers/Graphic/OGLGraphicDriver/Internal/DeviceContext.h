#pragma once

#include <Types.h>
#include <CBString.h>
#include "DeviceContextInterface.h"

namespace CB{
	//====================================
	//	Pure Device Context class
	//====================================
	class CDeviceContext :
		public IDeviceContext
	{
	private:
		/// <summary>
		/// Pointer to device context handle.
		/// </summary>
		mutable void* m_hDC;

	public:
		CDeviceContext();
		CDeviceContext(const CString& strDeviceName);
		CDeviceContext(void* hDC);
		~CDeviceContext();

		void* Get() const override;

	private:
		CR_NOCOPY(CDeviceContext);
		CR_NOASSIGN(CDeviceContext);
	};
}