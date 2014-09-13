#pragma once

#include <Types.h>

#include <Windows.h>

namespace CB{
	namespace Internal{
		class CDeviceContext{
		private:
			HWND	m_hWindow;
			HDC		m_hDC;

		public:
			CDeviceContext( HWND hWindow );
			~CDeviceContext();

			void	SetWindow( HWND hWindow );
			void	SetPixelFormat(const int32 iFormat);
						
			HWND	GetWindow() const;
			HDC		GetHandle() const;
			const int32	GetPixelFormat() const;

			const int32	ChoosePixelFormat(const PIXELFORMATDESCRIPTOR& pfd) const;
			void		SwapBuffers();
		};
	}
}