#include "stdafx.h"
#include "../Internal/Graphic_RenderContext.h"
#include "../Internal/Graphic_DeviceContext.h"
#include "../Internal/Graphic_RCBindGuard.h"
#include "../Internal/Graphic_GLConsts.h"

#include <Logger.h>
#include <CBString.h>
#include <CBString_Funcs.h>
#include <Collection_List.h>

#pragma comment(lib, "opengl32.lib")

#define APIENTRYP	__stdcall*
#define WINAPI		__stdcall
DECLARE_HANDLE(HPBUFFER);

#undef near
#undef far

namespace GL{
	extern "C" __declspec(dllimport) void* __stdcall wglGetProcAddress(const char*);

	namespace PROC{
		//	VERSION 1_0
		extern "C"{
			__declspec(dllimport) void __stdcall glCullFace (GLenum mode);
			__declspec(dllimport) void __stdcall glFrontFace (GLenum mode);
			__declspec(dllimport) void __stdcall glHint (GLenum target, GLenum mode);
			__declspec(dllimport) void __stdcall glLineWidth (GLfloat width);
			__declspec(dllimport) void __stdcall glPointSize (GLfloat size);
			__declspec(dllimport) void __stdcall glPolygonMode (GLenum face, GLenum mode);
			__declspec(dllimport) void __stdcall glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
			__declspec(dllimport) void __stdcall glTexParameterf (GLenum target, GLenum pname, GLfloat param);
			__declspec(dllimport) void __stdcall glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
			__declspec(dllimport) void __stdcall glTexParameteri (GLenum target, GLenum pname, GLint param);
			__declspec(dllimport) void __stdcall glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
			__declspec(dllimport) void __stdcall glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
			__declspec(dllimport) void __stdcall glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
			__declspec(dllimport) void __stdcall glDrawBuffer (GLenum mode);
			__declspec(dllimport) void __stdcall glClear (GLbitfield mask);
			__declspec(dllimport) void __stdcall glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
			__declspec(dllimport) void __stdcall glClearStencil (GLint s);
			__declspec(dllimport) void __stdcall glClearDepth (GLdouble depth);
			__declspec(dllimport) void __stdcall glStencilMask (GLuint mask);
			__declspec(dllimport) void __stdcall glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
			__declspec(dllimport) void __stdcall glDepthMask (GLboolean flag);
			__declspec(dllimport) void __stdcall glDisable (GLenum cap);
			__declspec(dllimport) void __stdcall glEnable (GLenum cap);
			__declspec(dllimport) void __stdcall glFinish (void);
			__declspec(dllimport) void __stdcall glFlush (void);
			__declspec(dllimport) void __stdcall glBlendFunc (GLenum sfactor, GLenum dfactor);
			__declspec(dllimport) void __stdcall glLogicOp (GLenum opcode);
			__declspec(dllimport) void __stdcall glStencilFunc (GLenum func, GLint ref, GLuint mask);
			__declspec(dllimport) void __stdcall glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
			__declspec(dllimport) void __stdcall glDepthFunc (GLenum func);
			__declspec(dllimport) void __stdcall glPixelStoref (GLenum pname, GLfloat param);
			__declspec(dllimport) void __stdcall glPixelStorei (GLenum pname, GLint param);
			__declspec(dllimport) void __stdcall glReadBuffer (GLenum mode);
			__declspec(dllimport) void __stdcall glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
			__declspec(dllimport) void __stdcall glGetBooleanv (GLenum pname, GLboolean *params);
			__declspec(dllimport) void __stdcall glGetDoublev (GLenum pname, GLdouble *params);
			__declspec(dllimport) GLenum __stdcall glGetError (void);
			__declspec(dllimport) void __stdcall glGetFloatv (GLenum pname, GLfloat *params);
			__declspec(dllimport) void __stdcall glGetIntegerv (GLenum pname, GLint *params);
			__declspec(dllimport) const GLubyte *__stdcall glGetString (GLenum name);
			__declspec(dllimport) void __stdcall glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
			__declspec(dllimport) void __stdcall glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
			__declspec(dllimport) void __stdcall glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
			__declspec(dllimport) void __stdcall glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
			__declspec(dllimport) void __stdcall glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
			__declspec(dllimport) GLboolean __stdcall glIsEnabled (GLenum cap);
			__declspec(dllimport) void __stdcall glDepthRange (GLdouble near, GLdouble far);
			__declspec(dllimport) void __stdcall glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
		}

		//	VERSION 1_1
		extern "C"{
			__declspec(dllimport) void __stdcall glDrawArrays (GLenum mode, GLint first, GLsizei count);
			__declspec(dllimport) void __stdcall glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
			__declspec(dllimport) void __stdcall glGetPointerv (GLenum pname, GLvoid **params);
			__declspec(dllimport) void __stdcall glPolygonOffset (GLfloat factor, GLfloat units);
			__declspec(dllimport) void __stdcall glCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
			__declspec(dllimport) void __stdcall glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
			__declspec(dllimport) void __stdcall glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
			__declspec(dllimport) void __stdcall glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
			__declspec(dllimport) void __stdcall glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
			__declspec(dllimport) void __stdcall glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
			__declspec(dllimport) void __stdcall glBindTexture (GLenum target, GLuint texture);
			__declspec(dllimport) void __stdcall glDeleteTextures (GLsizei n, const GLuint *textures);
			__declspec(dllimport) void __stdcall glGenTextures (GLsizei n, GLuint *textures);
			__declspec(dllimport) GLboolean __stdcall glIsTexture (GLuint texture);
		}

		//	VERSION 1_2
		typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
		typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
		typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
		typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

		//	VERSION 1_3
		typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
		typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
		typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
		typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
		typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
		typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
		typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
		typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
		typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, GLvoid *img);

		//	VERSION 1_4
		typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
		typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
		typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC) (GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount);
		typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum pname, GLfloat param);
		typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum pname, const GLfloat *params);
		typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC) (GLenum pname, GLint param);
		typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC) (GLenum pname, const GLint *params);
		typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);

		//	VERSION 1_5
		typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
		typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
		typedef GLboolean (APIENTRYP PFNGLISQUERYPROC) (GLuint id);
		typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
		typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
		typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
		typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
		typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
		typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
		typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
		typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
		typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
		typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
		typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
		typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data);
		typedef void *(APIENTRYP PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
		typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
		typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
		typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, GLvoid **params);

		//	GL_EXT_STENCIL_TWO_SIDE
		typedef void (APIENTRYP PFNGLACTIVESTENCILFACEPROC) (GLenum face);

		//	GL_EXT_BLEND_FUNC_SEPARATE
		typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
	}

	namespace EXT{
		const CB::CString	VERTEX_BUFFER_OBJECT = L"vertex_buffer_object";
		const CB::CString	GENERATE_MIPMAP = L"generate_mipmap";
		const CB::CString	TEXTURE_FILTER_ANISOTROPIC = L"texture_filter_anisotropic";
		const CB::CString	STENCIL_TWO_SIDE = L"stencil_two_side";
	}
}

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

	namespace EXT{
		const CB::CString	PIXEL_FORMAT = L"pixel_format";
		const CB::CString	PBUFFER = L"pbuffer";
		const CB::CString	MAKE_CURRENT_READ = L"make_current_read";
		const CB::CString	CREATE_CONTEXT = L"create_context";
		const CB::CString	CREATE_CONTEXT_PROFILE = L"create_context_profile";
		const CB::CString	MULTISAMPLE = L"multisample";
	}
}

namespace CB{
	namespace Internal{
		class CRenderContext::CData{
		public:
			HGLRC	m_hRC;

			#pragma region GLvars

		#define GL_PROC(A,B)	GL::PROC::A B

			//	VERSION 1.2
			GL_PROC(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
			GL_PROC(PFNGLTEXIMAGE3DPROC, glTexImage3D);
			GL_PROC(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
			GL_PROC(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

			//	VERSION 1.3
			GL_PROC(PFNGLACTIVETEXTUREPROC, glActiveTexture);
			GL_PROC(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
			GL_PROC(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);

			//	VERSION 1.4
			GL_PROC(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
			GL_PROC(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
			GL_PROC(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
			GL_PROC(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
			GL_PROC(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
			GL_PROC(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
			GL_PROC(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
			GL_PROC(PFNGLBLENDCOLORPROC, glBlendColor);
			GL_PROC(PFNGLBLENDEQUATIONPROC, glBlendEquation);

			//	VERSION 1.5
			GL_PROC(PFNGLGENQUERIESPROC, glGenQueries);
			GL_PROC(PFNGLDELETEQUERIESPROC, glDeleteQueries);
			GL_PROC(PFNGLISQUERYPROC, glIsQuery);
			GL_PROC(PFNGLBEGINQUERYPROC, glBeginQuery);
			GL_PROC(PFNGLENDQUERYPROC, glEndQuery);
			GL_PROC(PFNGLGETQUERYIVPROC, glGetQueryiv);
			GL_PROC(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
			GL_PROC(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
			GL_PROC(PFNGLBINDBUFFERPROC, glBindBuffer);
			GL_PROC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
			GL_PROC(PFNGLGENBUFFERSPROC, glGenBuffers);
			GL_PROC(PFNGLISBUFFERPROC, glIsBuffer);
			GL_PROC(PFNGLBUFFERDATAPROC, glBufferData);
			GL_PROC(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
			GL_PROC(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
			GL_PROC(PFNGLMAPBUFFERPROC, glMapBuffer);
			GL_PROC(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
			GL_PROC(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
			GL_PROC(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

			//	EXT Stencil Two Side
			GL_PROC(PFNGLACTIVESTENCILFACEPROC, glActiveStencilFace);

		#undef GL_PROC

			#pragma endregion

			#pragma region WGLvars

		#define GL_PROC(A,B)	WGL::PROC::A B

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

			#pragma endregion

		public:
			CData(HGLRC hRC);

			//	Core

			const bool LoadVersion12();
			const bool LoadVersion13();
			const bool LoadVersion14();
			const bool LoadVersion15();

			//	Extensions

			const bool LoadVBO();
			const bool LoadStencilTwoSide();

			// WGL Extensions

			const bool LoadExtensionsString();
			const bool LoadPixelBuffer();
			const bool LoadPixelFormat();
			const bool LoadMakeCurrentRead();
			const bool LoadCreateContext();

		private:
			typedef const bool (CRenderContext::CData::*load_proc)(const CB::CString&);

			template<typename _Type>
			_Type LoadGLProc(const CB::CString& strProcName, const CB::CString& strSufix);

			const bool	LoadProcVersion12(const CB::CString& strSufix);
			const bool	LoadProcVersion13(const CB::CString& strSufix);
			const bool	LoadProcVersion14(const CB::CString& strSufix);
			const bool	LoadProcVersion15(const CB::CString& strSufix);

			const bool	LoadProcVBO(const CB::CString& strSufix);
			const bool	LoadProcStencilTwoSide(const CB::CString& strSufix);

			const bool	LoadProcExtensionsString(const CB::CString& strSufix);
			const bool	LoadProcPixelBuffer(const CB::CString& strSufix);
			const bool	LoadProcPixelFormat(const CB::CString& strSufix);
			const bool	LoadProcMakeCurrentRead(const CB::CString& strSufix);
			const bool	LoadProcCreateContext(const CB::CString& strSufix);

			template<load_proc _Func>
			const bool	LoadProcs(); 	
		};

		CRenderContext::CData::CData(HGLRC hRC) :
			m_hRC(hRC)
		{
	#define GL_PROC(A,B)	this->B = 0
			
			#pragma region GLvars

			//	VERSION 1.2
			GL_PROC(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
			GL_PROC(PFNGLTEXIMAGE3DPROC, glTexImage3D);
			GL_PROC(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
			GL_PROC(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

			//	VERSION 1.3
			GL_PROC(PFNGLACTIVETEXTUREPROC, glActiveTexture);
			GL_PROC(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
			GL_PROC(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);

			//	VERSION 1.4
			GL_PROC(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
			GL_PROC(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
			GL_PROC(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
			GL_PROC(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
			GL_PROC(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
			GL_PROC(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
			GL_PROC(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
			GL_PROC(PFNGLBLENDCOLORPROC, glBlendColor);
			GL_PROC(PFNGLBLENDEQUATIONPROC, glBlendEquation);

			//	VERSION 1.5
			GL_PROC(PFNGLGENQUERIESPROC, glGenQueries);
			GL_PROC(PFNGLDELETEQUERIESPROC, glDeleteQueries);
			GL_PROC(PFNGLISQUERYPROC, glIsQuery);
			GL_PROC(PFNGLBEGINQUERYPROC, glBeginQuery);
			GL_PROC(PFNGLENDQUERYPROC, glEndQuery);
			GL_PROC(PFNGLGETQUERYIVPROC, glGetQueryiv);
			GL_PROC(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
			GL_PROC(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
			GL_PROC(PFNGLBINDBUFFERPROC, glBindBuffer);
			GL_PROC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
			GL_PROC(PFNGLGENBUFFERSPROC, glGenBuffers);
			GL_PROC(PFNGLISBUFFERPROC, glIsBuffer);
			GL_PROC(PFNGLBUFFERDATAPROC, glBufferData);
			GL_PROC(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
			GL_PROC(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
			GL_PROC(PFNGLMAPBUFFERPROC, glMapBuffer);
			GL_PROC(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
			GL_PROC(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
			GL_PROC(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

			//	EXT Stencil Two Side
			GL_PROC(PFNGLACTIVESTENCILFACEPROC, glActiveStencilFace);

			#pragma endregion

			#pragma region WGLvars

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

			#pragma endregion

	#undef GL_PROC
		}

		template<typename _Type>
		_Type CRenderContext::CData::LoadGLProc(const CB::CString& strProcName, const CB::CString& strSufix){
			auto szProcName = CB::String::ToANSI(strProcName + strSufix);

			_Type pProc = reinterpret_cast<_Type>(::wglGetProcAddress(reinterpret_cast<const char*>(szProcName.GetPointer())));
			if(pProc){
				CB::Log::Write(L"Loaded GL Procedure " + strProcName + strSufix, CB::Log::LogLevel::Debug);
				return pProc;
			}
			else{
				CB::Log::Write(L"Failed to load GL Procedure " + strProcName + strSufix, CB::Log::LogLevel::Debug);
				return 0;
			}
		}

	#pragma region Loading Functions

	#define GL_PROC(A,B)	if(this->B == 0){ this->B = LoadGLProc<GL::PROC::A>(L#B, strSufix); } if(this->B == 0) return false;

	#pragma region Core Loading

		const bool	CRenderContext::CData::LoadProcVersion12(const CB::CString& strSufix){
			GL_PROC(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
			GL_PROC(PFNGLTEXIMAGE3DPROC, glTexImage3D);
			GL_PROC(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
			GL_PROC(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

			return true;
		}

		const bool	CRenderContext::CData::LoadProcVersion13(const CB::CString& strSufix){
			GL_PROC(PFNGLACTIVETEXTUREPROC, glActiveTexture);
			GL_PROC(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
			GL_PROC(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
			GL_PROC(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
			GL_PROC(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);

			return true;
		}

		const bool	CRenderContext::CData::LoadProcVersion14(const CB::CString& strSufix){
			GL_PROC(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
			GL_PROC(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
			GL_PROC(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
			GL_PROC(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
			GL_PROC(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
			GL_PROC(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
			GL_PROC(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
			GL_PROC(PFNGLBLENDCOLORPROC, glBlendColor);
			GL_PROC(PFNGLBLENDEQUATIONPROC, glBlendEquation);

			return true;
		}

		const bool	CRenderContext::CData::LoadProcVersion15(const CB::CString& strSufix){
			GL_PROC(PFNGLGENQUERIESPROC, glGenQueries);
			GL_PROC(PFNGLDELETEQUERIESPROC, glDeleteQueries);
			GL_PROC(PFNGLISQUERYPROC, glIsQuery);
			GL_PROC(PFNGLBEGINQUERYPROC, glBeginQuery);
			GL_PROC(PFNGLENDQUERYPROC, glEndQuery);
			GL_PROC(PFNGLGETQUERYIVPROC, glGetQueryiv);
			GL_PROC(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
			GL_PROC(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
			GL_PROC(PFNGLBINDBUFFERPROC, glBindBuffer);
			GL_PROC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
			GL_PROC(PFNGLGENBUFFERSPROC, glGenBuffers);
			GL_PROC(PFNGLISBUFFERPROC, glIsBuffer);
			GL_PROC(PFNGLBUFFERDATAPROC, glBufferData);
			GL_PROC(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
			GL_PROC(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
			GL_PROC(PFNGLMAPBUFFERPROC, glMapBuffer);
			GL_PROC(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
			GL_PROC(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
			GL_PROC(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

			return true;
		}

	#pragma endregion

	#pragma region Extension Loading

		const bool CRenderContext::CData::LoadProcVBO(const CB::CString& strSufix){
			GL_PROC(PFNGLBINDBUFFERPROC, glBindBuffer);
			GL_PROC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
			GL_PROC(PFNGLGENBUFFERSPROC, glGenBuffers);
			GL_PROC(PFNGLISBUFFERPROC, glIsBuffer);
			GL_PROC(PFNGLBUFFERDATAPROC, glBufferData);
			GL_PROC(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
			GL_PROC(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
			GL_PROC(PFNGLMAPBUFFERPROC, glMapBuffer);
			GL_PROC(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
			GL_PROC(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
			GL_PROC(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

			return true;
		}

		const bool CRenderContext::CData::LoadProcStencilTwoSide(const CB::CString& strSufix){
			GL_PROC(PFNGLACTIVESTENCILFACEPROC, glActiveStencilFace);
		
			return true;
		}

	#pragma endregion

	#undef GL_PROC

	#define GL_PROC(A,B)	if(this->B == 0){ this->B = LoadGLProc<WGL::PROC::A>(L#B, strSufix); } if(this->B == 0) return false;

	#pragma region WGL Extension Loading

		const bool CRenderContext::CData::LoadProcExtensionsString(const CB::CString& strSufix){
			GL_PROC(PFNWGLGETEXTENSIONSSTRINGPROC, wglGetExtensionsString);

			return true;
		}

		const bool CRenderContext::CData::LoadProcPixelBuffer(const CB::CString& strSufix){
			GL_PROC(PFNWGLCREATEPBUFFERPROC, wglCreatePbuffer);
			GL_PROC(PFNWGLGETPBUFFERDCPROC, wglGetPbufferDC);
			GL_PROC(PFNWGLRELEASEPBUFFERDCPROC, wglReleasePbufferDC);
			GL_PROC(PFNWGLDESTROYPBUFFERPROC, wglDestroyPbuffer);
			GL_PROC(PFNWGLQUERYPBUFFERPROC, wglQueryPbuffer);

			return true;
		}

		const bool CRenderContext::CData::LoadProcPixelFormat(const CB::CString& strSufix){
			GL_PROC(PFNWGLGETPIXELFORMATATTRIBIVPROC, wglGetPixelFormatAttribiv);
			GL_PROC(PFNWGLGETPIXELFORMATATTRIBFVPROC, wglGetPixelFormatAttribfv);
			GL_PROC(PFNWGLCHOOSEPIXELFORMATPROC, wglChoosePixelFormat);

			return true;
		}

		const bool CRenderContext::CData::LoadProcMakeCurrentRead(const CB::CString& strSufix){
			GL_PROC(PFNWGLMAKECONTEXTCURRENTPROC, wglMakeContextCurrent);
			GL_PROC(PFNWGLGETCURRENTREADDCPROC, wglGetCurrentReadDC);

			return true;
		}

		const bool CRenderContext::CData::LoadProcCreateContext(const CB::CString& strSufix){
			GL_PROC(PFNWGLCREATECONTEXTATTRIBSPROC, wglCreateContextAttribs);

			return true;
		}

	#pragma endregion

	#undef GL_PROC

		template<CRenderContext::CData::load_proc _Func>
		const bool CRenderContext::CData::LoadProcs(){
			if((this->*_Func)(L""))
				return true;

			if((this->*_Func)(L"ARB"))
				return true;

			if((this->*_Func)(L"EXT"))
				return true;

			if((this->*_Func)(L"SGIS"))
				return true;

			if((this->*_Func)(L"NV"))
				return true;

			if((this->*_Func)(L"ATI"))
				return true;

			return false;
		}
 
		// GL Core Loading

		const bool CRenderContext::CData::LoadVersion12(){
			CB::Log::Write(L"Loading GL Version 1.2", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcVersion12>();
		}

		const bool CRenderContext::CData::LoadVersion13(){
			CB::Log::Write(L"Loading GL Version 1.3", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcVersion13>();
		}

		const bool CRenderContext::CData::LoadVersion14(){
			CB::Log::Write(L"Loading GL Version 1.4", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcVersion14>();
		}

		const bool CRenderContext::CData::LoadVersion15(){
			CB::Log::Write(L"Loading GL Version 1.5", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcVersion15>();
		}
		
		// GL Extensions Loading

		const bool CRenderContext::CData::LoadVBO(){
			CB::Log::Write(L"Loading GL Vertex Buffer Objects Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcVBO>();
		}

		const bool CRenderContext::CData::LoadStencilTwoSide(){
			CB::Log::Write(L"Loading GL Stencil two side Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcStencilTwoSide>();
		}

		// WGL Extensions Loading

		const bool CRenderContext::CData::LoadExtensionsString(){
			CB::Log::Write(L"Loading WGL Extensions String Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcExtensionsString>();
		}

		const bool CRenderContext::CData::LoadPixelBuffer(){
			CB::Log::Write(L"Loading WGL Pixel Buffer Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcPixelBuffer>();
		}

		const bool CRenderContext::CData::LoadPixelFormat(){
			CB::Log::Write(L"Loading WGL Pixel Format Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcPixelFormat>();
		}

		const bool CRenderContext::CData::LoadMakeCurrentRead(){
			CB::Log::Write(L"Loading WGL Make Current Read Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcMakeCurrentRead>();
		}

		const bool CRenderContext::CData::LoadCreateContext(){
			CB::Log::Write(L"Loading WGL Create Context Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<&CRenderContext::CData::LoadProcCreateContext>();
		}

	#pragma endregion

		CRenderContext::CRenderContext(const CDeviceContext& DC) :
			m_pData(0)
		{
			this->CreateContext(DC);
			{
				CRCBindGuard guard;
				this->Bind(DC);
				this->CheckVersion();
				this->LoadExtensionInfo(DC);
			}
		}

		CRenderContext::CRenderContext(const CDeviceContext& DC, const CRenderContext& ShareRC) :
			m_pData(0)
		{
			this->CreateContext(DC);
			{
				CRCBindGuard guard;
				this->Bind(DC);
				this->wglShareLists(*this, ShareRC);
				this->CheckVersion();
				this->LoadExtensionInfo(DC);
			}
		}

		CRenderContext::CRenderContext(const CDeviceContext& DC, CRenderContext& baseRC, const Collection::ICountable<int32>& Attribs) :
			m_pData(0)
		{
			this->CreateContext(DC, baseRC, Attribs, 0);
			{
				CRCBindGuard guard;
				this->Bind(DC);
				this->CheckVersion();
				this->LoadExtensionInfo(DC);
			}
		}

		CRenderContext::CRenderContext(const CDeviceContext& DC, CRenderContext& baseRC, const Collection::ICountable<int32>& Attribs, const CRenderContext& ShareRC) :
			m_pData(0)
		{
			this->CreateContext(DC, baseRC, Attribs, ShareRC.GetHandle());
			{
				CRCBindGuard guard;
				this->Bind(DC);
				this->CheckVersion();
				this->LoadExtensionInfo(DC);
			}
		}

		CRenderContext::~CRenderContext(){
			auto pData = (CRenderContext::CData*)this->m_pData;
			if(pData->m_hRC){
				if(this->IsBinded()){
					wglMakeCurrent(0, 0);
				}
				wglDeleteContext(pData->m_hRC);
				pData->m_hRC = 0;
			}
			delete pData;
			this->m_pData = 0;
		}

		const bool	CRenderContext::Bind(const CDeviceContext& DC){
			return wglMakeCurrent((HDC)DC.GetHandle(), this->m_pData->m_hRC) ? true : false;
		}

		void	CRenderContext::Unbind(){
			wglMakeCurrent(0, 0);
		}

		const bool	CRenderContext::IsBinded() const{
			return wglGetCurrentContext() == this->m_pData->m_hRC;
		}

		void*	CRenderContext::GetHandle() const {
			return this->m_pData->m_hRC;
		}

		const bool	CRenderContext::IsSupported(const GLVersion uVersion) const{
			switch (uVersion){
			case GLVersion::V_1_2:	return m_uVersionMajor >= 1 && m_uVersionMinor >= 2;
			case GLVersion::V_1_3:	return m_uVersionMajor >= 1 && m_uVersionMinor >= 3;
			case GLVersion::V_1_4:	return m_uVersionMajor >= 1 && m_uVersionMinor >= 4;
			case GLVersion::V_1_5:	return m_uVersionMajor >= 1 && m_uVersionMinor >= 5;
			case GLVersion::V_2_0:	return m_uVersionMajor >= 2 && m_uVersionMinor >= 0;
			case GLVersion::V_2_1:	return m_uVersionMajor >= 2 && m_uVersionMinor >= 1;
			case GLVersion::V_3_0:	return m_uVersionMajor >= 3 && m_uVersionMinor >= 0;
			case GLVersion::V_3_1:	return m_uVersionMajor >= 3 && m_uVersionMinor >= 1;
			case GLVersion::V_3_2:	return m_uVersionMajor >= 3 && m_uVersionMinor >= 2;
			case GLVersion::V_3_3:	return m_uVersionMajor >= 3 && m_uVersionMinor >= 3;
			default:
				return false;
			}
		}

		const bool	CRenderContext::IsSupported(const GLExtension uExtension) const{
			switch (uExtension){
			case GLExtension::VertexBufferObjects:
				return IsGLExtensionSupported(GL::EXT::VERTEX_BUFFER_OBJECT);

			case GLExtension::MipMapGeneration:
				return IsGLExtensionSupported(GL::EXT::GENERATE_MIPMAP);

			case GLExtension::AnisotropicFiltering:
				return IsGLExtensionSupported(GL::EXT::TEXTURE_FILTER_ANISOTROPIC);

			case GLExtension::StencilTwoSide:
				return IsGLExtensionSupported(GL::EXT::STENCIL_TWO_SIDE);

			default:
				return false;
			}
		}

		const bool	CRenderContext::IsSupported(const WGLExtension uExtension) const{
			switch (uExtension){
			case WGLExtension::ExtensionsString:
				return !this->m_strWGLExtensions.IsEmptyOrWhiteSpace();

			case WGLExtension::PixelFormat:
				return IsWGLExtSupported(WGL::EXT::PIXEL_FORMAT);

			case WGLExtension::PixelBuffer:
				return IsWGLExtSupported(WGL::EXT::PBUFFER);

			case WGLExtension::MakeCurrentRead:
				return IsWGLExtSupported(WGL::EXT::MAKE_CURRENT_READ);

			case WGLExtension::CreateContext:
				return IsWGLExtSupported(WGL::EXT::CREATE_CONTEXT);

			case WGLExtension::CreateContextProfile:
				return IsWGLExtSupported(WGL::EXT::CREATE_CONTEXT_PROFILE);

			case WGLExtension::Multisample:
				return IsWGLExtSupported(WGL::EXT::MULTISAMPLE);

			default:
				return false;
			}
		}

		const bool	CRenderContext::Load(const GLVersion uVersion){
			switch (uVersion){
			case GLVersion::V_1_2:	return this->m_pData->LoadVersion12();
			case GLVersion::V_1_3:	return this->m_pData->LoadVersion13();
			case GLVersion::V_1_4:	return this->m_pData->LoadVersion14();
			case GLVersion::V_1_5:	return this->m_pData->LoadVersion15();

			default:
				return false;
			}
		}

		const bool	CRenderContext::Load(const GLExtension uExtension){
			switch (uExtension){
			case GLExtension::VertexBufferObjects:	return this->m_pData->LoadVBO();
			case GLExtension::StencilTwoSide:		return this->m_pData->LoadStencilTwoSide();

			case GLExtension::AnisotropicFiltering:
			case GLExtension::MipMapGeneration:
				return IsSupported(uExtension);

			default:
				return false;
			}
		}

		const bool	CRenderContext::Load(const WGLExtension uExtension){
			switch (uExtension){
			case WGLExtension::CreateContext:	return this->m_pData->LoadCreateContext();
			case WGLExtension::MakeCurrentRead:	return this->m_pData->LoadMakeCurrentRead();
			case WGLExtension::PixelBuffer:		return this->m_pData->LoadPixelBuffer();
			case WGLExtension::PixelFormat:		return this->m_pData->LoadPixelFormat();

			case WGLExtension::Multisample:
			case WGLExtension::ExtensionsString:
			case WGLExtension::CreateContextProfile:
				return IsSupported(uExtension);

			default:
				return false;
			}
		}

		void	CRenderContext::CheckVersion(){
			auto szVersion = this->glGetString(GL::GL_VERSION);	CR_GLCHECK();
			if(!szVersion){
				CR_THROW(L"failed to retrieve GL version.");
			}

			auto strVersion = String::FromANSI(reinterpret_cast<const int8*>(szVersion));

			//if(!GLUtils::GetVersion(strVersion, this->m_uVersionMajor, m_uVersionMinor)){
			//	CR_THROW(L"Failed to parse OGL Version: " + strVersion);
			//}
		}

		const int32	CRenderContext::ChoosePixelFormat(const CDeviceContext& DC, const Collection::ICountable<int32>& Attribs) const{
			if(!this->IsSupported(WGLExtension::PixelFormat)){
				CR_THROW(L"Pixel format WGL extension not supported.");
			}
			if(Attribs.GetLength() % 2 != 0){
				CR_THROW(L"Attribs arrays for pixel format is not multiple of 2.");
			}

			const bool bMultisample = this->IsSupported(WGLExtension::Multisample);
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

			if(newAttribsInt[newAttribsInt.GetLength() - 2] != 0 && newAttribsInt[newAttribsInt.GetLength() - 1] != 0){
				newAttribsInt.Add(0);
				newAttribsInt.Add(0);
			}

			int32 iPixelFormat;
			uint32 uNumPixelFormats;

			float32 newAttribsFloat[] = { 0.0f, 0.0f };

			if(this->wglChoosePixelFormat(DC, newAttribsInt.GetPointer(), newAttribsFloat, 1, &iPixelFormat, &uNumPixelFormats) && uNumPixelFormats > 0){
				return iPixelFormat;
			}

			return 0;
		}

		void	CRenderContext::CreateContext(const CDeviceContext& DC){		
			auto hRC = wglCreateContext(DC.GetHandle());
			if(hRC == 0){
				CR_THROWWIN(GetLastError(), L"Failed to create GL Legacy Context.");
			}
			this->m_pData = new CRenderContext::CData(hRC);
		}

		void	CRenderContext::CreateContext(const CDeviceContext& DC, CRenderContext& baseRC, const Collection::ICountable<int32>& Attribs, void* hShareRC){
			if(Attribs.GetLength() % 2 != 0){
				CR_THROW(L"Incorrect length attrib array for render context creation (not multiple of 2).");
			}

			Collection::CList<int32> newAttribs(Attribs);

			//if(!WGL::IsSupported(WGL::Extension::CreateContextProfile)){
			//	Log::Write(L"Context Profile extension unsupproted, removing attributes from array.");

			//	for(uint32 uIndex = newAttribs.GetLength(); uIndex > 0; uIndex -= 2){
			//		if(newAttribs[uIndex - 1] == WGL::WGL_CONTEXT_PROFILE_MASK){
			//			newAttribs.Remove(uIndex - 1);
			//			newAttribs.Remove(uIndex - 1);
			//		}
			//	}
			//}

			uint32 uLen = newAttribs.GetLength();
			if(newAttribs.GetLength() > 0 && newAttribs[uLen - 1] != 0 && newAttribs[uLen - 2] != 0){
				newAttribs.Add(0);
				newAttribs.Add(0);
			}

			HGLRC hRC = reinterpret_cast<HGLRC>( baseRC.wglCreateContextAttribs( DC, hShareRC, newAttribs.GetPointer() ) );
			if(hRC == 0){
				CR_THROWWIN(GetLastError(), L"Failed to create GL Core Context.");
			}
			this->m_pData = new CRenderContext::CData(hRC);		
		}

		void		CRenderContext::LoadExtensionInfo(const CDeviceContext& DC){
			if(!this->LoadGLExtensionInfo()){
				CR_THROW(L"Failed to load info about GL extensions.");
			}
			if(!this->LoadWGLExtensionInfo(DC)){
				CR_THROW(L"Failed to load info about WGL extensions.");
			}
		}

		const bool	CRenderContext::LoadGLExtensionInfo(){
			auto szExtString = reinterpret_cast<const int8*>(this->glGetString(GL::GL_EXTENSIONS));
			if(szExtString == 0){
				return false;
			}

			this->m_strExtensions = CB::String::FromANSI(szExtString);
			if(this->m_strExtensions.IsEmptyOrWhiteSpace()){
				return false;
			}
			return true;
		}

		const bool	CRenderContext::LoadWGLExtensionInfo(const CDeviceContext& DC){
			if(!this->m_pData->LoadExtensionsString())
				return false;

			const int8* szExtString = this->wglGetExtensionsString(DC);
			if(szExtString == 0)
				return false;

			this->m_strWGLExtensions = CB::String::FromANSI(szExtString);
			return true;
		}

		const bool	CRenderContext::IsGLExtensionSupported(const CB::CString& strPrefix, const CB::CString& strName) const{
			auto strExt = L"GL_" + strPrefix + L"_" + strName + L" ";
			if(this->m_strExtensions.Find(strExt)){
				CB::Log::Write(strExt + L" found on GL extension string.", CB::Log::LogLevel::Debug);
				return true;
			}
			else{
				CB::Log::Write(strExt + L" NOT found on GL extension string.", CB::Log::LogLevel::Debug);
				return false;
			}
		}

		const bool	CRenderContext::IsGLExtensionSupported(const CB::CString& strName) const{
			if(this->IsGLExtensionSupported(L"ARB", strName))
				return true;

			if(this->IsGLExtensionSupported(L"EXT", strName))
				return true;

			if(this->IsGLExtensionSupported(L"SGIS", strName))
				return true;

			if(this->IsGLExtensionSupported(L"NV", strName))
				return true;

			if(this->IsGLExtensionSupported(L"ATI", strName))
				return true;

			return false;
		}

		const bool	CRenderContext::IsWGLExtSupported(const CB::CString& strPrefix, const CB::CString& strName) const{
			auto strExt = L"WGL_" + strPrefix + L"_" + strName;
			if(this->m_strWGLExtensions.Find(strExt)){
				CB::Log::Write(strExt + L" found on WGL extension string.", CB::Log::LogLevel::Debug);
				return true;
			}
			else{
				CB::Log::Write(strExt + L" NOT found on WGL extension string.", CB::Log::LogLevel::Debug);
				return false;
			}
		}

		const bool	CRenderContext::IsWGLExtSupported(const CB::CString& strName) const{
			if(IsWGLExtSupported(L"ARB", strName))
				return true;

			if(IsWGLExtSupported(L"EXT", strName))
				return true;

			if(IsWGLExtSupported(L"SGIS", strName))
				return true;

			if(IsWGLExtSupported(L"NV", strName))
				return true;

			if(IsWGLExtSupported(L"ATI", strName))
				return true;
			return false;
		}

	#pragma region GL Methods

	#pragma region Version 1.0
		//	VERSION 1.0
		void CRenderContext::glCullFace (GLenum mode){
			return GL::PROC::glCullFace (mode);
		}
		void CRenderContext::glFrontFace (GLenum mode){
			return GL::PROC::glFrontFace (mode);
		}
		void CRenderContext::glHint (GLenum target, GLenum mode){
			return GL::PROC::glHint (target, mode);
		}
		void CRenderContext::glLineWidth (GLfloat width){
			return GL::PROC::glLineWidth (width);
		}
		void CRenderContext::glPointSize (GLfloat size){
			return GL::PROC::glPointSize (size);
		}
		void CRenderContext::glPolygonMode (GLenum face, GLenum mode){
			return GL::PROC::glPolygonMode (face, mode);
		}
		void CRenderContext::glScissor (GLint x, GLint y, GLsizei width, GLsizei height){
			return GL::PROC::glScissor (x, y, width, height);
		}
		void CRenderContext::glTexParameterf (GLenum target, GLenum pname, GLfloat param){
			return GL::PROC::glTexParameterf (target, pname, param);
		}
		void CRenderContext::glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params){
			return GL::PROC::glTexParameterfv (target, pname, params);
		}
		void CRenderContext::glTexParameteri (GLenum target, GLenum pname, GLint param){
			return GL::PROC::glTexParameteri (target, pname, param);
		}
		void CRenderContext::glTexParameteriv (GLenum target, GLenum pname, const GLint *params){
			return GL::PROC::glTexParameteriv (target, pname, params);
		}
		void CRenderContext::glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels){
			return GL::PROC::glTexImage1D (target, level, internalformat, width, border, format, type, pixels);
		}
		void CRenderContext::glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels){
			return GL::PROC::glTexImage2D (target, level, internalformat, width, height, border, format, type, pixels);
		}
		void CRenderContext::glDrawBuffer (GLenum mode){
			return GL::PROC::glDrawBuffer (mode);
		}
		void CRenderContext::glClear (GLbitfield mask){
			return GL::PROC::glClear (mask);
		}
		void CRenderContext::glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
			return GL::PROC::glClearColor (red, green, blue, alpha);
		}
		void CRenderContext::glClearStencil (GLint s){
			return GL::PROC::glClearStencil (s);
		}
		void CRenderContext::glClearDepth (GLdouble depth){
			return GL::PROC::glClearDepth (depth);
		}
		void CRenderContext::glStencilMask (GLuint mask){
			return GL::PROC::glStencilMask (mask);
		}
		void CRenderContext::glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){
			return GL::PROC::glColorMask (red, green, blue, alpha);
		}
		void CRenderContext::glDepthMask (GLboolean flag){
			return GL::PROC::glDepthMask (flag);
		}
		void CRenderContext::glDisable (GLenum cap){
			return GL::PROC::glDisable (cap);
		}
		void CRenderContext::glEnable (GLenum cap){
			return GL::PROC::glEnable (cap);
		}
		void CRenderContext::glFinish (void){
			return GL::PROC::glFinish ();
		}
		void CRenderContext::glFlush (void){
			return GL::PROC::glFlush ();
		}
		void CRenderContext::glBlendFunc (GLenum sfactor, GLenum dfactor){
			return GL::PROC::glBlendFunc (sfactor, dfactor);
		}
		void CRenderContext::glLogicOp (GLenum opcode){
			return GL::PROC::glLogicOp (opcode);
		}
		void CRenderContext::glStencilFunc (GLenum func, GLint ref, GLuint mask){
			return GL::PROC::glStencilFunc (func, ref, mask);
		}
		void CRenderContext::glStencilOp (GLenum fail, GLenum zfail, GLenum zpass){
			return GL::PROC::glStencilOp (fail, zfail, zpass);
		}
		void CRenderContext::glDepthFunc (GLenum func){
			return GL::PROC::glDepthFunc (func);
		}
		void CRenderContext::glPixelStoref (GLenum pname, GLfloat param){
			return GL::PROC::glPixelStoref (pname, param);
		}
		void CRenderContext::glPixelStorei (GLenum pname, GLint param){
			return GL::PROC::glPixelStorei (pname, param);
		}
		void CRenderContext::glReadBuffer (GLenum mode){
			return GL::PROC::glReadBuffer (mode);
		}
		void CRenderContext::glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels){
			return GL::PROC::glReadPixels (x, y, width, height, format, type, pixels);
		}
		void CRenderContext::glGetBooleanv (GLenum pname, GLboolean *params){
			return GL::PROC::glGetBooleanv (pname, params);
		}
		void CRenderContext::glGetDoublev (GLenum pname, GLdouble *params){
			return GL::PROC::glGetDoublev (pname, params);
		}
		GLenum glGetError (void){
			return GL::PROC::glGetError ();
		}
		void CRenderContext::glGetFloatv (GLenum pname, GLfloat *params){
			return GL::PROC::glGetFloatv (pname, params);
		}
		void CRenderContext::glGetIntegerv (GLenum pname, GLint *params){
			return GL::PROC::glGetIntegerv (pname, params);
		}
		const GLubyte* CRenderContext::glGetString (GLenum name) const{
			return GL::PROC::glGetString (name);
		}
		void CRenderContext::glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels){
			return GL::PROC::glGetTexImage (target, level, format, type, pixels);
		}
		void CRenderContext::glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params){
			return GL::PROC::glGetTexParameterfv (target, pname, params);
		}
		void CRenderContext::glGetTexParameteriv (GLenum target, GLenum pname, GLint *params){
			return GL::PROC::glGetTexParameteriv (target, pname, params);
		}
		void CRenderContext::glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params){
			return GL::PROC::glGetTexLevelParameterfv (target, level, pname, params);
		}
		void CRenderContext::glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params){
			return GL::PROC::glGetTexLevelParameteriv (target, level, pname, params);
		}
		GLboolean glIsEnabled (GLenum cap){
			return GL::PROC::glIsEnabled (cap);
		}
		void CRenderContext::glDepthRange (GLdouble near, GLdouble far){
			return GL::PROC::glDepthRange (near, far);
		}
		void CRenderContext::glViewport (GLint x, GLint y, GLsizei width, GLsizei height){
			return GL::PROC::glViewport (x, y, width, height);
		}
	#pragma endregion

	#pragma region Version 1.1
		//	VERSION 1.1
		void CRenderContext::glDrawArrays (GLenum mode, GLint first, GLsizei count){
			return GL::PROC::glDrawArrays (mode, first, count);
		}
		void CRenderContext::glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices){
			return GL::PROC::glDrawElements (mode, count, type, indices);
		}
		void CRenderContext::glGetPointerv (GLenum pname, GLvoid **params){
			return GL::PROC::glGetPointerv (pname, params);
		}
		void CRenderContext::glPolygonOffset (GLfloat factor, GLfloat units){
			return GL::PROC::glPolygonOffset (factor, units);
		}
		void CRenderContext::glCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){
			return GL::PROC::glCopyTexImage1D (target, level, internalformat, x, y, width, border);
		}
		void CRenderContext::glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){
			return GL::PROC::glCopyTexImage2D (target, level, internalformat, x, y, width, height, border);
		}
		void CRenderContext::glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){
			return GL::PROC::glCopyTexSubImage1D (target, level, xoffset, x, y, width);
		}
		void CRenderContext::glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
			return GL::PROC::glCopyTexSubImage2D (target, level, xoffset, yoffset, x, y, width, height);
		}
		void CRenderContext::glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels){
			return GL::PROC::glTexSubImage1D (target, level, xoffset, width, format, type, pixels);
		}
		void CRenderContext::glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels){
			return GL::PROC::glTexSubImage2D (target, level, xoffset, yoffset, width, height, format, type, pixels);
		}
		void CRenderContext::glBindTexture (GLenum target, GLuint texture){
			return GL::PROC::glBindTexture (target, texture);
		}
		void CRenderContext::glDeleteTextures (GLsizei n, const GLuint *textures){
			return GL::PROC::glDeleteTextures (n, textures);
		}
		void CRenderContext::glGenTextures (GLsizei n, GLuint *textures){
			return GL::PROC::glGenTextures (n, textures);
		}
		GLboolean CRenderContext::glIsTexture (GLuint texture){
			return GL::PROC::glIsTexture (texture);
		}
	#pragma endregion

	#pragma region Version 1.2
		//	VERSION 1.2
		void CRenderContext::glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices){
			this->m_pData->glDrawRangeElements (mode, start, end, count, type, indices);
		}

		void CRenderContext::glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels){
			this->m_pData->glTexImage3D (target, level, internalformat, width, height, depth, border, format, type, pixels);
		}

		void CRenderContext::glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){
			this->m_pData->glTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		}

		void CRenderContext::glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){
			this->m_pData->glCopyTexSubImage3D (target, level, xoffset, yoffset, zoffset, x, y, width, height);
		}
	#pragma endregion

	#pragma region Version 1.3
		//	VERSION 1.3
		void CRenderContext::glActiveTexture (GLenum texture){
			this->m_pData->glActiveTexture (texture);
		}

		void CRenderContext::glSampleCoverage (GLfloat value, GLboolean invert){
			this->m_pData->glSampleCoverage (value, invert);
		}

		void CRenderContext::glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data){
			this->m_pData->glCompressedTexImage3D (target, level, internalformat, width, height, depth, border, imageSize, data);
		}

		void CRenderContext::glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data){
			this->m_pData->glCompressedTexImage2D (target, level, internalformat, width, height, border, imageSize, data);
		}

		void CRenderContext::glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data){
			this->m_pData->glCompressedTexImage1D (target, level, internalformat, width, border, imageSize, data);
		}

		void CRenderContext::glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data){
			this->m_pData->glCompressedTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		}

		void CRenderContext::glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data){
			this->m_pData->glCompressedTexSubImage2D (target, level, xoffset, yoffset, width, height, format, imageSize, data);
		}

		void CRenderContext::glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data){
			this->m_pData->glCompressedTexSubImage1D (target, level, xoffset, width, format, imageSize, data);
		}

		void CRenderContext::glGetCompressedTexImage (GLenum target, GLint level, GLvoid *img){
			this->m_pData->glGetCompressedTexImage (target, level, img);
		}
	#pragma endregion

	#pragma region Version 1.4
		//	VERSION 1.4
		void CRenderContext::glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){
			this->m_pData->glBlendFuncSeparate (sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
		}

		void CRenderContext::glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount){
			this->m_pData->glMultiDrawArrays (mode, first, count, drawcount);
		}
	
		void CRenderContext::glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount){
			this->m_pData->glMultiDrawElements (mode, count, type, indices, drawcount);
		}
	
		void CRenderContext::glPointParameterf (GLenum pname, GLfloat param){
			this->m_pData->glPointParameterf (pname, param);
		}
	
		void CRenderContext::glPointParameterfv (GLenum pname, const GLfloat *params){
			this->m_pData->glPointParameterfv (pname, params);
		}
	
		void CRenderContext::glPointParameteri (GLenum pname, GLint param){
			this->m_pData->glPointParameteri (pname, param);
		}
	
		void CRenderContext::glPointParameteriv (GLenum pname, const GLint *params){
			this->m_pData->glPointParameteriv (pname, params);
		}
	
		void CRenderContext::glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
			this->m_pData->glBlendColor (red, green, blue, alpha);
		}
	
		void CRenderContext::glBlendEquation (GLenum mode){
			this->m_pData->glBlendEquation (mode);
		}
	#pragma endregion

	#pragma region Version 1.5

		void CRenderContext::glGenQueries (GLsizei n, GLuint *ids){
			this->m_pData->glGenQueries (n, ids);
		}
	
		void CRenderContext::glDeleteQueries (GLsizei n, const GLuint *ids){
			this->m_pData->glDeleteQueries (n, ids);
		}
	
		GLboolean CRenderContext::glIsQuery (GLuint id){
			return this->m_pData->glIsQuery (id);
		}
	
		void CRenderContext::glBeginQuery (GLenum target, GLuint id){
			this->m_pData->glBeginQuery (target, id);
		}
	
		void CRenderContext::glEndQuery (GLenum target){
			this->m_pData->glEndQuery (target);
		}
	
		void CRenderContext::glGetQueryiv (GLenum target, GLenum pname, GLint *params){
			this->m_pData->glGetQueryiv (target, pname, params);
		}
	
		void CRenderContext::glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params){
			this->m_pData->glGetQueryObjectiv (id, pname, params);
		}
	
		void CRenderContext::glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params){
			this->m_pData->glGetQueryObjectuiv (id, pname, params);
		}
	
		void CRenderContext::glBindBuffer (GLenum target, GLuint buffer){
			this->m_pData->glBindBuffer (target, buffer);
		}
	
		void CRenderContext::glDeleteBuffers (GLsizei n, const GLuint *buffers){
			this->m_pData->glDeleteBuffers (n, buffers);
		}
	
		void CRenderContext::glGenBuffers (GLsizei n, GLuint *buffers){
			this->m_pData->glGenBuffers (n, buffers);
		}
	
		GLboolean CRenderContext::glIsBuffer (GLuint buffer){
			return this->m_pData->glIsBuffer (buffer);
		}
	
		void CRenderContext::glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage){
			this->m_pData->glBufferData (target, size, data, usage);
		}
	
		void CRenderContext::glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data){
			this->m_pData->glBufferSubData (target, offset, size, data);
		}
	
		void CRenderContext::glGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data){
			this->m_pData->glGetBufferSubData (target, offset, size, data);
		}
	
		void* CRenderContext::glMapBuffer (GLenum target, GLenum access){
			return this->m_pData->glMapBuffer (target, access);
		}
	
		GLboolean CRenderContext::glUnmapBuffer (GLenum target){
			return this->m_pData->glUnmapBuffer (target);
		}
	
		void CRenderContext::glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params){
			this->m_pData->glGetBufferParameteriv (target, pname, params);
		}
	
		void CRenderContext::glGetBufferPointerv (GLenum target, GLenum pname, GLvoid **params){
			this->m_pData->glGetBufferPointerv (target, pname, params);
		}

	#pragma endregion

	#pragma region Extensions

		//	EXT Stencil Two Face
		void	CRenderContext::glActiveStencilFace(GLenum face){
			this->m_pData->glActiveStencilFace(face);
		}

	#pragma endregion

	#pragma region WGL Extensions

		PROC CRenderContext::wglGetProcAddress(const CString& strName){
			auto szProcName = CB::String::ToANSI(strName);
			return ::wglGetProcAddress(reinterpret_cast<const char*>(szProcName.GetPointer()));
		}

		bool CRenderContext::wglShareLists(const CRenderContext& shareTo, const CRenderContext& shareFrom){
			return ::wglShareLists((HGLRC)shareTo.GetHandle(), (HGLRC)shareFrom.GetHandle()) ? true : false;
		}

		//	WGL_extensions_string
		const int8* CRenderContext::wglGetExtensionsString (const CDeviceContext& DC){
			return this->m_pData->wglGetExtensionsString ((HDC)DC.GetHandle());
		}

		//	WGL_PBuffer
		void* CRenderContext::wglCreatePbuffer (const CDeviceContext& DC, int32 iPixelFormat, int32 iWidth, int32 iHeight, const int32 *piAttribList){
			return this->m_pData->wglCreatePbuffer ((HDC)DC.GetHandle(), iPixelFormat, iWidth, iHeight, piAttribList);
		}

		void* CRenderContext::wglGetPbufferDC (void* hPbuffer){
			return this->m_pData->wglGetPbufferDC ((HPBUFFER)hPbuffer);
		}
	
		int32	CRenderContext::wglReleasePbufferDC (void* hPbuffer, const CDeviceContext& DC){
			return this->m_pData->wglReleasePbufferDC ((HPBUFFER)hPbuffer, (HDC)DC.GetHandle());
		}
	
		bool CRenderContext::wglDestroyPbuffer (void* hPbuffer){
			return this->m_pData->wglDestroyPbuffer ((HPBUFFER)hPbuffer) ? true : false;
		}
	
		bool CRenderContext::wglQueryPbuffer (void* hPbuffer, int32 iAttribute, int32 *piValue){
			return this->m_pData->wglQueryPbuffer ((HPBUFFER)hPbuffer, iAttribute, piValue) ? true : false;
		}

		//	WGL_pixel_format
		bool CRenderContext::wglGetPixelFormatAttribiv (const CDeviceContext& DC, int32 iPixelFormat, int32 iLayerPlane, uint32 nAttributes, const int32 *piAttributes, int32 *piValues){
			return this->m_pData->wglGetPixelFormatAttribiv ((HDC)DC.GetHandle(), iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues) ? true : false;
		}
	
		bool CRenderContext::wglGetPixelFormatAttribfv (const CDeviceContext& DC, int32 iPixelFormat, int32 iLayerPlane, uint32 nAttributes, const int32 *piAttributes, float32 *pfValues){
			return this->m_pData->wglGetPixelFormatAttribfv ((HDC)DC.GetHandle(), iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues) ? true : false;
		}
	
		bool CRenderContext::wglChoosePixelFormat (const CDeviceContext& DC, const int32 *piAttribIList, const float32 *pfAttribFList, uint32 nMaxFormats, int32 *piFormats, uint32 *nNumFormats) const{
			return this->m_pData->wglChoosePixelFormat ((HDC)DC.GetHandle(), piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats) ? true : false;
		}

		//	WGL_make_current_read
		bool CRenderContext::wglMakeContextCurrent (const CDeviceContext& DrawDC, const CDeviceContext& ReadDC, const CRenderContext& GLRC){
			return this->m_pData->wglMakeContextCurrent ((HDC)DrawDC.GetHandle(), (HDC)ReadDC.GetHandle(), (HGLRC)GLRC.GetHandle()) ? true : false;
		}
	
		void* CRenderContext::wglGetCurrentReadDC (){
			return this->m_pData->wglGetCurrentReadDC ();
		}

		//	WGL_create_context
		void* CRenderContext::wglCreateContextAttribs (const CDeviceContext& DC, const CRenderContext& ShareContext, const int32 *attribList){
			return this->m_pData->wglCreateContextAttribs ((HDC)DC.GetHandle(), (HGLRC)ShareContext.GetHandle(), attribList);
		}

		void* CRenderContext::wglCreateContextAttribs (const CDeviceContext& DC, void* hShareContext, const int32 *attribList){
			return this->m_pData->wglCreateContextAttribs ((HDC)DC.GetHandle(), (HGLRC)hShareContext, attribList);
		}

	#pragma endregion

	#pragma endregion

	}
}

namespace GL{
	GLenum	glGetError(){
		return GL::PROC::glGetError();
	}
	const bool	CheckDCRC(const CB::Internal::CDeviceContext& DC, const CB::Internal::CRenderContext& RC){
		return (HDC)DC.GetHandle() == wglGetCurrentDC() && (HGLRC)RC.GetHandle() == wglGetCurrentContext();
	}
	const CB::CString	ToErrorString(GLenum uError){
		switch (uError)
		{
		case GL_INVALID_ENUM:		return L"Invalid Enum";
		case GL_INVALID_VALUE:		return L"Invalid Value";
		case GL_INVALID_OPERATION:	return L"Invalid Operation";
		case GL_OUT_OF_MEMORY:		return L"Out of Memory";

		default:
			return CB::String::ToHexString(uError);
		}
	}

	void	ReportGLError(GLenum uError, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine){
		CB::CString strError = L"GL Error: " + ToErrorString(uError);
#ifdef CR_GL_ERROR_AS_EXCEPTION
		throw Exception::CException(strError, strFunction, strFile, uLine);
#else
		CB::Log::Write(strError + L", " + strFunction + L", " + strFile + L", " + CB::String::ToString(uLine), CB::Log::LogLevel::Error);
#endif // CR_GL_ERROR_AS_EXCEPTION
	}
	void	ReportGLBindMismatch(const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine){
#ifdef CR_GL_ERROR_AS_EXCEPTION
		throw Exception::CException(L"Incorrect gl or device context currently bound.", strFunction, strFile, uLine);
#else
		CB::Log::Write(CB::CString(L"Incorrect GL or Device context currently bound. ") + strFunction + L", " + strFile + L", " + CB::String::ToString(uLine), CB::Log::LogLevel::Warning);
#endif // CR_GL_ERROR_AS_EXCEPTION
	}
}