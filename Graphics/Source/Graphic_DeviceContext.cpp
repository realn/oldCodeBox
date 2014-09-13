#include "stdafx.h"
#include "../Internal/Graphic_DeviceContext.h"

#include <CBString.h>
#include <CBString_Funcs.h>
#include <Exception.h>

namespace CB{
	namespace Internal{
		CDeviceContext::CDeviceContext( HWND hWindow ) :
			m_hWindow( hWindow ),
			m_hDC( nullptr )
		{
			this->m_hDC = GetWindowDC( this->m_hWindow );
		}

		CDeviceContext::~CDeviceContext(){
			if( this->m_hDC && this->m_hWindow ){
				ReleaseDC( this->m_hWindow, this->m_hDC );
				this->m_hDC = nullptr;
			}
		}

		void	CDeviceContext::SetWindow( HWND hWindow ){
			if( this->m_hDC && this->m_hWindow ){
				ReleaseDC( this->m_hWindow, this->m_hDC );
			}
			this->m_hWindow = hWindow;
			this->m_hDC = GetWindowDC( this->m_hWindow );
		}

		void	CDeviceContext::SetPixelFormat( const int32 iPixelFormat ){
			::PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;

			if(!::SetPixelFormat((HDC)this->m_hDC, iPixelFormat, &pfd)){
				CR_THROWWIN(GetLastError(), L"Failed to set pixel format nr " + String::ToString(iPixelFormat) + L" to device context.");
			}
		}

		HWND	CDeviceContext::GetWindow() const{
			return this->m_hWindow;
		}

		HDC	CDeviceContext::GetHandle() const{
			return this->m_hDC;
		}

		const int32	CDeviceContext::GetPixelFormat() const{
			return ::GetPixelFormat(this->m_hDC);		
		}

		const int32	CDeviceContext::ChoosePixelFormat(const PIXELFORMATDESCRIPTOR& pfd) const{
			return ::ChoosePixelFormat((HDC)this->m_hDC, (::PIXELFORMATDESCRIPTOR*)&pfd);
		}

		void	CDeviceContext::SwapBuffers(){
			if(!::SwapBuffers((HDC)this->m_hDC)){
				CR_THROWWIN(GetLastError(), L"Failed to swap buffer.");
			}
		}
	}
}