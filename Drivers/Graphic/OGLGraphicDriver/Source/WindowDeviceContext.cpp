#include "../Internal/WindowDeviceContext.h"
#include "../Internal/WinPlatform.h"
#include <Logger.h>

namespace CB{
	CWindowDeviceContext::CWindowDeviceContext(CRefPtr<Window::IWindow> pWindow) :
		m_pWindow(pWindow),
		m_hDC(0)
	{
		this->m_hDC = (void*)GetDC(reinterpret_cast<HWND>(pWindow->GetHandle()));
		if(this->m_hDC == 0){
			CR_THROWWIN(GetLastError(), L"Failed to retrieve window device context of " + pWindow->GetTitle() + L".");
		}
	}

	CWindowDeviceContext::~CWindowDeviceContext(){ 
		this->Release();
	}

	void	CWindowDeviceContext::Release(){
		if(m_hDC){ 
			ReleaseDC((HWND)this->m_pWindow->GetHandle(), (HDC)this->m_hDC); 
			this->m_hDC = 0;
			this->m_pWindow.Release();
		} 
	}

	void	CWindowDeviceContext::SetWindow(CRefPtr<Window::IWindow> pWindow){
		this->Release();
		this->m_pWindow = pWindow;
		this->m_hDC = GetDC((HWND)this->m_pWindow->GetHandle());
		if(this->m_hDC == 0){
			CR_THROWWIN(GetLastError(), L"Failed to retrieve window device context of " + pWindow->GetTitle() + L".");
		}
	}

	CRefPtr<Window::IWindow>	CWindowDeviceContext::GetWindow() const {
		return this->m_pWindow;
	}

	void*	CWindowDeviceContext::Get() const{ 
		return m_hDC; 
	}

	const int32	CWindowDeviceContext::ChoosePixelFormat(const PIXELFORMATDESCRIPTOR& pfd) const{
		return ::ChoosePixelFormat((HDC)this->m_hDC, (::PIXELFORMATDESCRIPTOR*)&pfd);
	}

	void	CWindowDeviceContext::SetPixelFormat(const int32 iFormat){
		::PIXELFORMATDESCRIPTOR pfd = { 0 };
		pfd.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;

		if(!::SetPixelFormat((HDC)this->m_hDC, iFormat, &pfd)){
			CR_THROWWIN(GetLastError(), L"Failed to set pixel format nr " + String::ToString(iFormat) + L" to device context of window " + this->m_pWindow->GetTitle());
		}
	}

	const uint32	GetLastError(){
		return ::GetLastError();
	}
}