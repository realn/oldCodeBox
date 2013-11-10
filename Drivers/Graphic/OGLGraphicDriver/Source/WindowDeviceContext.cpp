#include "../Internal/WindowDeviceContext.h"

namespace CB{
	CWindowDeviceContext::CWindowDeviceContext() : 
		m_hDC(0)
	{}

	CWindowDeviceContext::CWindowDeviceContext(CRefPtr<Window::IWindow> pWindow) :
		m_pWindow(pWindow),
		m_hDC(GetDC((HWND)pWindow->GetHandle()))
	{}

	CWindowDeviceContext::~CWindowDeviceContext(){ 
		this->Release();
	}

	void	CWindowDeviceContext::Release(){
		if(m_hDC){ 
			ReleaseDC((HWND)this->m_pWindow->GetHandle(), this->m_hDC); 
			m_hDC = 0; 
		} 
	}

	void	CWindowDeviceContext::SetWindow(CRefPtr<Window::IWindow> pWindow){
		this->Release();
		this->m_pWindow = pWindow;
		this->m_hDC = GetDC((HWND)this->m_pWindow->GetHandle());
	}

	CRefPtr<Window::IWindow>	CWindowDeviceContext::GetWindow() const {
		return this->m_pWindow;
	}
	HDC&	CWindowDeviceContext::Get() const{ 
		return m_hDC; 
	}
}