#pragma once

#include "DeviceContextInterface.h"
#include <SmartPointers_RefPtr.h>
#include <WindowDriver.h>

namespace CB{
	/* Pixel format descriptor */
	typedef struct tagPIXELFORMATDESCRIPTOR{
		uint16  nSize;
		uint16  nVersion;
		uint32 dwFlags;
		byte  iPixelType;
		byte  cColorBits;
		byte  cRedBits;
		byte  cRedShift;
		byte  cGreenBits;
		byte  cGreenShift;
		byte  cBlueBits;
		byte  cBlueShift;
		byte  cAlphaBits;
		byte  cAlphaShift;
		byte  cAccumBits;
		byte  cAccumRedBits;
		byte  cAccumGreenBits;
		byte  cAccumBlueBits;
		byte  cAccumAlphaBits;
		byte  cDepthBits;
		byte  cStencilBits;
		byte  cAuxBuffers;
		byte  iLayerType;
		byte  bReserved;
		uint32 dwLayerMask;
		uint32 dwVisibleMask;
		uint32 dwDamageMask;
	} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;

	class CWindowDeviceContext :
		public IDeviceContext
	{
	private:
		CRefPtr<CB::Window::IWindow> m_pWindow;
		mutable void* m_hDC;

	public:
		CWindowDeviceContext(CRefPtr<Window::IWindow> pWindow);
		~CWindowDeviceContext();

		void	Release();

		void	SetWindow(CRefPtr<Window::IWindow> pWindow);
		CRefPtr<Window::IWindow>	GetWindow() const;

		void*	Get() const override;

		const int32	ChoosePixelFormat(const PIXELFORMATDESCRIPTOR& pfd) const;
		void		SetPixelFormat(const int32 iFormat);

	private:
		CR_NOCOPY(CWindowDeviceContext);
		CR_NOASSIGN(CWindowDeviceContext);
	};
}