#include "../Internal/OpenGL_WGL.h"

#include <CBString.h>
#include <CBStringEx.h>
#include <Logger.h>

namespace WGL{
	namespace PROC{
		typedef const int8 *(WINAPI * PFNWGLGETEXTENSIONSSTRINGPROC) (HDC hdc);

		//	Pixel Buffer
		typedef HPBUFFER (WINAPI * PFNWGLCREATEPBUFFERPROC) (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
		typedef HDC (WINAPI * PFNWGLGETPBUFFERDCPROC) (HPBUFFER hPbuffer);
		typedef int (WINAPI * PFNWGLRELEASEPBUFFERDCPROC) (HPBUFFER hPbuffer, HDC hDC);
		typedef BOOL (WINAPI * PFNWGLDESTROYPBUFFERPROC) (HPBUFFER hPbuffer);
		typedef BOOL (WINAPI * PFNWGLQUERYPBUFFERPROC) (HPBUFFER hPbuffer, int iAttribute, int *piValue);

		//	Pixel Format
		typedef BOOL (WINAPI * PFNWGLGETPIXELFORMATATTRIBIVPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
		typedef BOOL (WINAPI * PFNWGLGETPIXELFORMATATTRIBFVPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
		typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

		//	Make Current Read
		typedef BOOL (WINAPI * PFNWGLMAKECONTEXTCURRENTPROC) (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
		typedef HDC (WINAPI * PFNWGLGETCURRENTREADDCPROC) (void);

		//	Create Context
		typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

#define GL_PROC(A,B)	A B = 0

		GL_PROC(PFNWGLGETEXTENSIONSSTRINGPROC, wglGetExtensionsString);

		GL_PROC(PFNWGLCREATEPBUFFERPROC, wglCreatePbuffer);
		GL_PROC(PFNWGLGETPBUFFERDCPROC, wglGetPbufferDC);
		GL_PROC(PFNWGLRELEASEPBUFFERDCPROC, wglReleasePbufferDC);
		GL_PROC(PFNWGLDESTROYPBUFFERPROC, wglDestroyPbuffer);
		GL_PROC(PFNWGLQUERYPBUFFERPROC, wglQueryPbuffer);

		GL_PROC(PFNWGLGETPIXELFORMATATTRIBIVPROC, wglGetPixelFormatAttribiv);
		GL_PROC(PFNWGLGETPIXELFORMATATTRIBFVPROC, wglGetPixelFormatAttribfv);
		GL_PROC(PFNWGLCHOOSEPIXELFORMATPROC, wglChoosePixelFormat);

		GL_PROC(PFNWGLMAKECONTEXTCURRENTPROC, wglMakeContextCurrent);
		GL_PROC(PFNWGLGETCURRENTREADDCPROC, wglGetCurrentReadDC);

		GL_PROC(PFNWGLCREATECONTEXTATTRIBSPROC, wglCreateContextAttribs);

#undef GL_PROC
	}

	//==========================================================
	//	WGL external function mapers
	//==========================================================

#pragma region WGL funcs

	//	WGL_extensions_string
	const int8* wglGetExtensionsString (HDC hdc){
		return PROC::wglGetExtensionsString (hdc);
	}

	//	WGL_PBuffer
	HPBUFFER	wglCreatePbuffer (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList){
		return PROC::wglCreatePbuffer (hDC, iPixelFormat, iWidth, iHeight, piAttribList);
	}

	HDC			wglGetPbufferDC (HPBUFFER hPbuffer){
		return PROC::wglGetPbufferDC (hPbuffer);
	}
	
	int			wglReleasePbufferDC (HPBUFFER hPbuffer, HDC hDC){
		return PROC::wglReleasePbufferDC (hPbuffer, hDC);
	}
	
	BOOL		wglDestroyPbuffer (HPBUFFER hPbuffer){
		return PROC::wglDestroyPbuffer (hPbuffer);
	}
	
	BOOL		wglQueryPbuffer (HPBUFFER hPbuffer, int iAttribute, int *piValue){
		return PROC::wglQueryPbuffer (hPbuffer, iAttribute, piValue);
	}

	//	WGL_pixel_format
	BOOL wglGetPixelFormatAttribiv (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues){
		return PROC::wglGetPixelFormatAttribiv (hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues);
	}
	
	BOOL wglGetPixelFormatAttribfv (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues){
		return PROC::wglGetPixelFormatAttribfv (hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues);
	}
	
	BOOL wglChoosePixelFormat (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats){
		return PROC::wglChoosePixelFormat (hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats);
	}

	//	WGL_make_current_read
	BOOL	wglMakeContextCurrent (HDC hDrawDC, HDC hReadDC, HGLRC hglrc){
		return PROC::wglMakeContextCurrent (hDrawDC, hReadDC, hglrc);
	}
	
	HDC		wglGetCurrentReadDC (){
		return PROC::wglGetCurrentReadDC ();
	}

	//	WGL_create_context
	HGLRC wglCreateContextAttribs (HDC hDC, HGLRC hShareContext, const int *attribList){
		return PROC::wglCreateContextAttribs (hDC, hShareContext, attribList);
	}

#pragma endregion

	namespace Loader{
		//======================================================
		//	GLOBALS
		//======================================================

		HDC			g_hDC = 0;
		CB::CString	g_strWGLExtensions;

		//===============================================
		//	Raw proc loading funcs
		//===============================================

		template<typename _Type>
		_Type LoadGLProc(const CB::CString& strProcName, const CB::CString& strSufix){
			auto szProcName = CB::String::ToANSI(strProcName + strSufix);
			_Type pProc = reinterpret_cast<_Type>(wglGetProcAddress(reinterpret_cast<const char*>(szProcName.GetPointer())));
			if(pProc){
				CB::Log::Write(L"Loading GL Procedure " + strProcName + strSufix, CB::Log::LogLevel::Debug);
				return pProc;
			}
			else{
				CB::Log::Write(L"Failed to load GL Procedure " + strProcName + strSufix, CB::Log::LogLevel::Debug);
				return 0;
			}
		}

#define GL_PROC(A,B)	if(PROC::B == 0){ PROC::B = LoadGLProc<PROC::A>(L#B, strSufix); } if(PROC::B == 0) return false;
		
		const bool LoadProcExtensionsString(const CB::CString& strSufix){
			GL_PROC(PFNWGLGETEXTENSIONSSTRINGPROC, wglGetExtensionsString);

			return true;
		}

		const bool LoadProcPixelBuffer(const CB::CString& strSufix){
			GL_PROC(PFNWGLCREATEPBUFFERPROC, wglCreatePbuffer);
			GL_PROC(PFNWGLGETPBUFFERDCPROC, wglGetPbufferDC);
			GL_PROC(PFNWGLRELEASEPBUFFERDCPROC, wglReleasePbufferDC);
			GL_PROC(PFNWGLDESTROYPBUFFERPROC, wglDestroyPbuffer);
			GL_PROC(PFNWGLQUERYPBUFFERPROC, wglQueryPbuffer);

			return true;
		}

		const bool LoadProcPixelFormat(const CB::CString& strSufix){
			GL_PROC(PFNWGLGETPIXELFORMATATTRIBIVPROC, wglGetPixelFormatAttribiv);
			GL_PROC(PFNWGLGETPIXELFORMATATTRIBFVPROC, wglGetPixelFormatAttribfv);
			GL_PROC(PFNWGLCHOOSEPIXELFORMATPROC, wglChoosePixelFormat);

			return true;
		}

		const bool LoadProcMakeCurrentRead(const CB::CString& strSufix){
			GL_PROC(PFNWGLMAKECONTEXTCURRENTPROC, wglMakeContextCurrent);
			GL_PROC(PFNWGLGETCURRENTREADDCPROC, wglGetCurrentReadDC);

			return true;
		}

		const bool LoadProcCreateContext(const CB::CString& strSufix){
			GL_PROC(PFNWGLCREATECONTEXTATTRIBSPROC, wglCreateContextAttribs);

			return true;
		}

#undef GL_PROC

		//================================================
		//	Extension Proc loading abstract funcs
		//================================================

		typedef const bool (*load_proc)(const CB::CString&);

		template<load_proc _Func>
		const bool LoadProcs(){
			if(_Func(L"ARB"))
				return true;

			if(_Func(L"EXT"))
				return true;

			return false;
		}

		const bool LoadExtensionsString(){
			CB::Log::Write(L"Loading WGL Extensions String Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcExtensionsString>();
		}

		const bool LoadPixelBuffer(){
			CB::Log::Write(L"Loading WGL Pixel Buffer Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcPixelBuffer>();
		}

		const bool LoadPixelFormat(){
			CB::Log::Write(L"Loading WGL Pixel Format Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcPixelFormat>();
		}

		const bool LoadMakeCurrentRead(){
			CB::Log::Write(L"Loading WGL Make Current Read Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcMakeCurrentRead>();
		}

		const bool LoadCreateContext(){
			CB::Log::Write(L"Loading WGL Create Context Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcCreateContext>();
		}

		//================================================
		//	Extensions checking funcs
		//================================================
		
		const bool	IsWGLExtSupported(const CB::CString& strPrefix, const CB::CString& strName){
			auto strExt = L"WGL_" + strPrefix + L"_" + strName;
			if(g_strWGLExtensions.Find(strExt)){
				CB::Log::Write(strExt + L" found on WGL extension string.", CB::Log::LogLevel::Debug);
				return true;
			}
			else{
				CB::Log::Write(strExt + L" NOT found on WGL extension string.", CB::Log::LogLevel::Debug);
				return false;
			}
		}

		const bool	IsWGLExtSupported(const CB::CString& strName){
			if(IsWGLExtSupported(L"ARB", strName))
				return true;

			if(IsWGLExtSupported(L"EXT", strName))
				return true;

			return false;
		}

		//================================================
		//	External funcs
		//================================================

		const bool	SetDeviceContext(HDC hDC){
			g_hDC = hDC;

			if(!LoadExtensionsString())
				return false;

			const int8* szExtString = wglGetExtensionsString(g_hDC);
			if(szExtString == 0)
				return false;

			g_strWGLExtensions = CB::String::FromANSI(szExtString);
			return true;
		}

		const bool	IsSupported(const Extension uExtension){
			switch (uExtension){
			case Extension::ExtensionsString:
				return g_hDC != 0 && !g_strWGLExtensions.IsEmptyOrWhiteSpace();

			case Extension::PixelFormat:
				return IsWGLExtSupported(L"pixel_format");

			case Extension::PixelBuffer:
				return IsWGLExtSupported(L"pbuffer");

			case Extension::MakeCurrentRead:
				return IsWGLExtSupported(L"make_current_read");

			case Extension::CreateContext:
				return IsWGLExtSupported(L"create_context");

			case Extension::CreateContextProfile:
				return IsWGLExtSupported(L"create_context_profile");

			case Extension::Multisample:
				return IsWGLExtSupported(L"multisample");

			default:
				return false;
			}
		}

		const bool	Load(const Extension uExtension){
			switch (uExtension)
			{
			case Extension::CreateContext:
				return LoadCreateContext();

			case Extension::MakeCurrentRead:
				return LoadMakeCurrentRead();

			case Extension::PixelBuffer:
				return LoadPixelBuffer();

			case Extension::PixelFormat:
				return LoadPixelFormat();

			case Extension::Multisample:
			case Extension::ExtensionsString:
			case Extension::CreateContextProfile:
				return IsSupported(uExtension);

			default:
				return false;
			}
		}
	}

	void	ReportGLBindMismatch(const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine){
#ifdef CR_GL_ERROR_AS_EXCEPTION
		throw Exception::CException(L"Incorrect gl or device context currently bound.", strFunction, strFile, uLine);
#else
		CB::Log::Write(CB::CString(L"Incorrect GL or Device context currently bound. ") + strFunction + L", " + strFile + L", " + CB::String::ToString(uLine), CB::Log::LogLevel::Warning);
#endif // CR_GL_ERROR_AS_EXCEPTION
	}
}