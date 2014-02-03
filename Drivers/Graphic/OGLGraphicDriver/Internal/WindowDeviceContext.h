#pragma once

#include "DeviceContextInterface.h"
#include <SmartPointers_RefPtr.h>
#include <WindowDriver.h>

namespace CB{

	enum PFD{
		/* pixel types */
		TYPE_RGBA        = 0,
		TYPE_COLORINDEX  = 1,

		/* layer types */
		MAIN_PLANE       = 0,
		OVERLAY_PLANE    = 1,
		UNDERLAY_PLANE   = (-1),

		/* PIXELFORMATDESCRIPTOR flags */
		DOUBLEBUFFER            = 0x00000001,
		STEREO                  = 0x00000002,
		DRAW_TO_WINDOW          = 0x00000004,
		DRAW_TO_BITMAP          = 0x00000008,
		SUPPORT_GDI             = 0x00000010,
		SUPPORT_OPENGL          = 0x00000020,
		GENERIC_FORMAT          = 0x00000040,
		NEED_PALETTE            = 0x00000080,
		NEED_SYSTEM_PALETTE     = 0x00000100,
		SWAP_EXCHANGE           = 0x00000200,
		SWAP_COPY               = 0x00000400,
		SWAP_LAYER_BUFFERS      = 0x00000800,
		GENERIC_ACCELERATED     = 0x00001000,
		SUPPORT_DIRECTDRAW      = 0x00002000,
		DIRECT3D_ACCELERATED    = 0x00004000,
		SUPPORT_COMPOSITION     = 0x00008000,

		/* PIXELFORMATDESCRIPTOR flags for use in ChoosePixelFormat only */
		DEPTH_DONTCARE          = 0x20000000,
		DOUBLEBUFFER_DONTCARE   = 0x40000000,
		STEREO_DONTCARE         = 0x80000000,
	};

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

	extern const uint32 GetLastError();
}