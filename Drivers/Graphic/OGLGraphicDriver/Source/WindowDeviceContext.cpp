#include "../Internal/WindowDeviceContext.h"
#include "../Internal/OpenGL_WGL.h"
#include <Logger.h>

namespace CB{
	CWindowDeviceContext::CWindowDeviceContext() : 
		m_hDC(0)
	{}

	CWindowDeviceContext::CWindowDeviceContext(CRefPtr<Window::IWindow> pWindow) :
		m_pWindow(pWindow),
		m_hDC(0)
	{
		this->m_hDC = GetDC(reinterpret_cast<HWND>(pWindow->GetHandle()));
	}

	CWindowDeviceContext::~CWindowDeviceContext(){ 
		this->Release();
	}

	void	CWindowDeviceContext::Release(){
		if(m_hDC){ 
			ReleaseDC((HWND)this->m_pWindow->GetHandle(), this->m_hDC); 
			this->m_hDC = 0;
			this->m_pWindow->Release();
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

	const int32	CWindowDeviceContext::ChoosePixelFormat(const PIXELFORMATDESCRIPTOR& pfd) const{
		return ::ChoosePixelFormat(this->m_hDC, &pfd);
	}
	const int32	CWindowDeviceContext::ChoosePixelFormat(const Collection::ICountable<int32>& Attribs) const{
		if(!WGL::IsSupported(WGL::Extension::PixelFormat)){
			CR_THROW(L"Pixel format WGL extension not supported.");
		}
		if(Attribs.GetLength() % 2 != 0){
			CR_THROW(L"Attribs arrays for pixel format is not multiple of 2.");
		}
		const bool bMultisample = WGL::IsSupported(WGL::Extension::Multisample);
		if(!bMultisample){
			Log::Write(L"Multisample not supported - removing from attribute array.");
		}

		Collection::CList<int32> newAttribsInt;
		for(uint32 uIndex = 0; uIndex < Attribs.GetLength(); uIndex += 2){
			if(Attribs[uIndex] == 0 && Attribs[uIndex + 1] == 0){
				break;
			}

			if(!bMultisample && (Attribs[uIndex] == WGL::WGL_SAMPLES || Attribs[uIndex] == WGL::WGL_SAMPLE_BUFFERS)){
				continue;
			}

			newAttribsInt.Add(Attribs[uIndex]);
			newAttribsInt.Add(Attribs[uIndex + 1]);
		}

		if(newAttribsInt[newAttribsInt.GetLength() - 2] != 0 && newAttribsInt[newAttribsInt.GetLength() - 1]){
			newAttribsInt.Add(0);
			newAttribsInt.Add(0);
		}

		int32 iPixelFormat;
		uint32 uNumPixelFormats;

		float32 newAttribsFloat[] = { 0.0f, 0.0f };

		if(WGL::wglChoosePixelFormat(this->m_hDC, newAttribsInt.GetPointer(), newAttribsFloat, 1, &iPixelFormat, &uNumPixelFormats) && uNumPixelFormats > 0){
			return iPixelFormat;
		}

		return 0;
	}

	void	CWindowDeviceContext::SetPixelFormat(const int32 iFormat){
		PIXELFORMATDESCRIPTOR pfd = { 0 };
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;

		if(!::SetPixelFormat(this->m_hDC, iFormat, &pfd)){
			CR_THROWWIN(GetLastError(), L"Failed to set pixel format nr " + String::ToString(iFormat) + L" to device context of window " + this->m_pWindow->GetTitle());
		}
	}
}