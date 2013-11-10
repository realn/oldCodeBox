#include "../Internal/DeviceContext.h"

namespace CB{
	CDeviceContext::CDeviceContext() : 
		m_hDC(0)
	{}
	CDeviceContext::CDeviceContext(HDC hDC) : 
		m_hDC(hDC)
	{}
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