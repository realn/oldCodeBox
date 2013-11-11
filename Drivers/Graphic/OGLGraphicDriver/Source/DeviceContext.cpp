#include "../Internal/DeviceContext.h"
#include <Exception.h>

namespace CB{
	CDeviceContext::CDeviceContext() : 
		m_hDC(0)
	{}
	CDeviceContext::CDeviceContext(HDC hDC) : 
		m_hDC(hDC)
	{}

	CDeviceContext::CDeviceContext(const CString& strDeviceName) :
		m_hDC(0)
	{
		this->m_hDC = CreateDCW(strDeviceName.GetPointer(), strDeviceName.GetPointer(), 0, 0);
		if(this->m_hDC == 0){
			CR_THROWWIN(GetLastError(), L"Failed to create context for device " + strDeviceName);
		}
	}

	CDeviceContext::~CDeviceContext(){ 
		if(m_hDC){ 
			DeleteDC(m_hDC); 
			m_hDC = 0; 
		} 
	}

	const CDeviceContext&	CDeviceContext::operator=(HDC hDC){
		this->m_hDC = hDC;
		return *this;
	}

	HDC& CDeviceContext::Get() const { 
		return m_hDC; 
	}
}