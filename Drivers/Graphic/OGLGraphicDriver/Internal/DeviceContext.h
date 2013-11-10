#pragma once

#include "DeviceContextInterface.h"

namespace CB{
	//====================================
	//	Pure Device Context class
	//====================================
	class CDeviceContext :
		public IDeviceContext
	{
	private:
		mutable HDC m_hDC;

	public:
		CDeviceContext();
		CDeviceContext(HDC hDC);
		~CDeviceContext();

		const CDeviceContext&	operator=(HDC hDC);

		HDC& Get() const override;
	};
}