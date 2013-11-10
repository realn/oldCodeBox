#pragma once

#include <Types.h>
#include "OpenGL_Types.h"

#include "WinPlatform.h"

DECLARE_HANDLE(HPBUFFER);

namespace WGL{
	//	WGL_extensions_string
	extern const int8* wglGetExtensionsString (HDC hdc);

	enum PBUFFER_TOKENS : GLenum{
		WGL_DRAW_TO_PBUFFER_           = 0x202D,
		WGL_MAX_PBUFFER_PIXELS_        = 0x202E,
		WGL_MAX_PBUFFER_WIDTH_         = 0x202F,
		WGL_MAX_PBUFFER_HEIGHT_        = 0x2030,
		WGL_PBUFFER_LARGEST_           = 0x2033,
		WGL_PBUFFER_WIDTH_             = 0x2034,
		WGL_PBUFFER_HEIGHT_            = 0x2035,
		WGL_PBUFFER_LOST_              = 0x2036,
	};

	//	WGL_pbuffer
	extern HPBUFFER		wglCreatePbuffer (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
	extern HDC			wglGetPbufferDC (HPBUFFER hPbuffer);
	extern int			wglReleasePbufferDC (HPBUFFER hPbuffer, HDC hDC);
	extern BOOL			wglDestroyPbuffer (HPBUFFER hPbuffer);
	extern BOOL			wglQueryPbuffer (HPBUFFER hPbuffer, int iAttribute, int *piValue);

	enum PIXEL_FORMAT_TOKENS : GLenum{
		WGL_NUMBER_PIXEL_FORMATS      = 0x2000,
		WGL_DRAW_TO_WINDOW            = 0x2001,
		WGL_DRAW_TO_BITMAP            = 0x2002,
		WGL_ACCELERATION              = 0x2003,
		WGL_NEED_PALETTE              = 0x2004,
		WGL_NEED_SYSTEM_PALETTE       = 0x2005,
		WGL_SWAP_LAYER_BUFFERS        = 0x2006,
		WGL_SWAP_METHOD               = 0x2007,
		WGL_NUMBER_OVERLAYS           = 0x2008,
		WGL_NUMBER_UNDERLAYS          = 0x2009,
		WGL_TRANSPARENT               = 0x200A,
		WGL_TRANSPARENT_RED_VALUE     = 0x2037,
		WGL_TRANSPARENT_GREEN_VALUE   = 0x2038,
		WGL_TRANSPARENT_BLUE_VALUE    = 0x2039,
		WGL_TRANSPARENT_ALPHA_VALUE   = 0x203A,
		WGL_TRANSPARENT_INDEX_VALUE   = 0x203B,
		WGL_SHARE_DEPTH               = 0x200C,
		WGL_SHARE_STENCIL             = 0x200D,
		WGL_SHARE_ACCUM               = 0x200E,
		WGL_SUPPORT_GDI               = 0x200F,
		WGL_SUPPORT_OPENGL            = 0x2010,
		WGL_DOUBLE_BUFFER             = 0x2011,
		WGL_STEREO                    = 0x2012,
		WGL_PIXEL_TYPE                = 0x2013,
		WGL_COLOR_BITS                = 0x2014,
		WGL_RED_BITS                  = 0x2015,
		WGL_RED_SHIFT                 = 0x2016,
		WGL_GREEN_BITS                = 0x2017,
		WGL_GREEN_SHIFT               = 0x2018,
		WGL_BLUE_BITS                 = 0x2019,
		WGL_BLUE_SHIFT                = 0x201A,
		WGL_ALPHA_BITS                = 0x201B,
		WGL_ALPHA_SHIFT               = 0x201C,
		WGL_ACCUM_BITS                = 0x201D,
		WGL_ACCUM_RED_BITS            = 0x201E,
		WGL_ACCUM_GREEN_BITS          = 0x201F,
		WGL_ACCUM_BLUE_BITS           = 0x2020,
		WGL_ACCUM_ALPHA_BITS          = 0x2021,
		WGL_DEPTH_BITS                = 0x2022,
		WGL_STENCIL_BITS              = 0x2023,
		WGL_AUX_BUFFERS               = 0x2024,
		WGL_NO_ACCELERATION           = 0x2025,
		WGL_GENERIC_ACCELERATION      = 0x2026,
		WGL_FULL_ACCELERATION         = 0x2027,
		WGL_SWAP_EXCHANGE             = 0x2028,
		WGL_SWAP_COPY                 = 0x2029,
		WGL_SWAP_UNDEFINED            = 0x202A,
		WGL_TYPE_RGBA                 = 0x202B,
		WGL_TYPE_COLORINDEX           = 0x202C,
	};

	//	WGL_pixel_format
	extern BOOL wglGetPixelFormatAttribiv (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
	extern BOOL wglGetPixelFormatAttribfv (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
	extern BOOL wglChoosePixelFormat (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

	enum MAKE_CURRENT_READ_TOKENS : GLenum{
		ERROR_INVALID_PIXEL_TYPE      = 0x2043,
		ERROR_INCOMPATIBLE_DEVICE_CONTEXTS = 0x2054,
	};

	//	WGL_make_current_read
	extern BOOL	wglMakeContextCurrent (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
	extern HDC	wglGetCurrentReadDC (void);

	enum CREATE_CONTEXT_TOKENS{
		WGL_CONTEXT_DEBUG_BIT          = 0x00000001,
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT  = 0x00000002,
		WGL_CONTEXT_MAJOR_VERSION      = 0x2091,
		WGL_CONTEXT_MINOR_VERSION      = 0x2092,
		WGL_CONTEXT_LAYER_PLANE        = 0x2093,
		WGL_CONTEXT_FLAGS              = 0x2094,
		WGL_ERROR_INVALID_VERSION      = 0x2095,
	};

	//	WGL_create_context
	extern HGLRC wglCreateContextAttribs (HDC hDC, HGLRC hShareContext, const int *attribList);

	enum CREATE_CONTEXT_PROFILE_TOKENS{
		 WGL_CONTEXT_PROFILE_MASK      = 0x9126,
		 WGL_CONTEXT_CORE_PROFILE_BIT  = 0x00000001,
		 WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT = 0x00000002,
		 WGL_ERROR_INVALID_PROFILE     = 0x2096,
	};

	enum MULTISAMPLE_TOKENS{
		WGL_SAMPLE_BUFFERS            = 0x2041,
		WGL_SAMPLES                   = 0x2042,
	};

	namespace Loader{
		enum class Extension{
			ExtensionsString,
			PixelBuffer,
			PixelFormat,
			MakeCurrentRead,
			CreateContext,
			CreateContextProfile,
			Multisample,
		};

		extern const bool	SetDeviceContext(HDC hDC);
		extern const bool	IsSupported(const Extension uExtension);
		extern const bool	Load(const Extension uExtension);
	}
}