#include "../Internal/DeviceContext.h"
#include "../Internal/WinPlatform.h"
#include <Exception.h>

namespace CB{
	CDeviceContext::CDeviceContext() : 
		m_hDC((void*)CreateCompatibleDC(0))
	{
		if(this->m_hDC == 0){
			CR_THROWWIN(GetLastError(), L"Failed to create compatible device context.");
		}
	}

	CDeviceContext::CDeviceContext(void* hDC) : 
		m_hDC(hDC)
	{}

	CDeviceContext::CDeviceContext(const CString& strDeviceName) :
		m_hDC(0)
	{
		this->m_hDC = (void*)CreateDCW(strDeviceName.GetPointer(), strDeviceName.GetPointer(), 0, 0);
		if(this->m_hDC == 0){
			CR_THROWWIN(GetLastError(), L"Failed to create context for device " + strDeviceName + L".");
		}
	}

	CDeviceContext::~CDeviceContext(){ 
		if(this->m_hDC){ 
			DeleteDC((HDC)this->m_hDC); 
			this->m_hDC = 0; 
		} 
	}

	void* CDeviceContext::Get() const { 
		return this->m_hDC; 
	}
}