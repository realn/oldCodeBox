#include "../Internal/GLRenderContext.h"
#include "../Internal/WinPlatform.h"
#include "../Internal/ContextBindGuard.h"
#include "../Internal/Utils.h"

#include <Exception.h>
#include <Collection_List.h>
#include <Logger.h>
#include <CBStringEx.h>

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
}

class CGLContextData{
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

	CGLContextData(HGLRC hRC) :
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
};

namespace CB{
#pragma region Loading Functions

	template<typename _Type>
	_Type LoadGLProc(const CB::CString& strProcName, const CB::CString& strSufix){
		auto szProcName = CB::String::ToANSI(strProcName + strSufix);
		_Type pProc = reinterpret_cast<_Type>(wglGetProcAddress(reinterpret_cast<const char*>(szProcName.GetPointer())));
		if(pProc){
			CB::Log::Write(L"Loaded GL Procedure " + strProcName + strSufix, CB::Log::LogLevel::Debug);
			return pProc;
		}
		else{
			CB::Log::Write(L"Failed to load GL Procedure " + strProcName + strSufix, CB::Log::LogLevel::Debug);
			return 0;
		}
	}

#define GL_PROC(A,B)	if(Data.B == 0){ Data.B = LoadGLProc<GL::PROC::A>(L#B, strSufix); } if(Data.B == 0) return false;

#pragma region Core Loading

	const bool	LoadProcVersion12(CGLContextData& Data, const CB::CString& strSufix){
		GL_PROC(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
		GL_PROC(PFNGLTEXIMAGE3DPROC, glTexImage3D);
		GL_PROC(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
		GL_PROC(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

		return true;
	}

	const bool	LoadProcVersion13(CGLContextData& Data, const CB::CString& strSufix){
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

	const bool	LoadProcVersion14(CGLContextData& Data, const CB::CString& strSufix){
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

	const bool	LoadProcVersion15(CGLContextData& Data, const CB::CString& strSufix){
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

	const bool LoadProcVBO(CGLContextData& Data, const CB::CString& strSufix){
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

	const bool LoadProcStencilTwoSide(CGLContextData& Data, const CB::CString& strSufix){
		GL_PROC(PFNGLACTIVESTENCILFACEPROC, glActiveStencilFace);
		
		return true;
	}

#pragma endregion

#undef GL_PROC

#define GL_PROC(A,B)	if(Data.B == 0){ Data.B = LoadGLProc<WGL::PROC::A>(L#B, strSufix); } if(Data.B == 0) return false;

#pragma region WGL Extension Loading

	const bool LoadProcExtensionsString(CGLContextData& Data, const CB::CString& strSufix){
		GL_PROC(PFNWGLGETEXTENSIONSSTRINGPROC, wglGetExtensionsString);

		return true;
	}

	const bool LoadProcPixelBuffer(CGLContextData& Data, const CB::CString& strSufix){
		GL_PROC(PFNWGLCREATEPBUFFERPROC, wglCreatePbuffer);
		GL_PROC(PFNWGLGETPBUFFERDCPROC, wglGetPbufferDC);
		GL_PROC(PFNWGLRELEASEPBUFFERDCPROC, wglReleasePbufferDC);
		GL_PROC(PFNWGLDESTROYPBUFFERPROC, wglDestroyPbuffer);
		GL_PROC(PFNWGLQUERYPBUFFERPROC, wglQueryPbuffer);

		return true;
	}

	const bool LoadProcPixelFormat(CGLContextData& Data, const CB::CString& strSufix){
		GL_PROC(PFNWGLGETPIXELFORMATATTRIBIVPROC, wglGetPixelFormatAttribiv);
		GL_PROC(PFNWGLGETPIXELFORMATATTRIBFVPROC, wglGetPixelFormatAttribfv);
		GL_PROC(PFNWGLCHOOSEPIXELFORMATPROC, wglChoosePixelFormat);

		return true;
	}

	const bool LoadProcMakeCurrentRead(CGLContextData& Data, const CB::CString& strSufix){
		GL_PROC(PFNWGLMAKECONTEXTCURRENTPROC, wglMakeContextCurrent);
		GL_PROC(PFNWGLGETCURRENTREADDCPROC, wglGetCurrentReadDC);

		return true;
	}

	const bool LoadProcCreateContext(CGLContextData& Data, const CB::CString& strSufix){
		GL_PROC(PFNWGLCREATECONTEXTATTRIBSPROC, wglCreateContextAttribs);

		return true;
	}

#pragma endregion

#undef GL_PROC

	typedef const bool (*load_proc)(CGLContextData& Data, const CB::CString&);

	template<load_proc _Func>
	const bool LoadProcs(CGLContextData& Data){
		if(_Func(Data, L""))
			return true;

		if(_Func(Data, L"ARB"))
			return true;

		if(_Func(Data, L"EXT"))
			return true;

		if(_Func(Data, L"SGIS"))
			return true;

		if(_Func(Data, L"NV"))
			return true;

		if(_Func(Data, L"ATI"))
			return true;

		return false;
	}
 
	// GL Core Loading

	const bool LoadVersion12(CGLContextData& Data){
		CB::Log::Write(L"Loading GL Version 1.2", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcVersion12>(Data);
	}

	const bool LoadVersion13(CGLContextData& Data){
		CB::Log::Write(L"Loading GL Version 1.3", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcVersion13>(Data);
	}

	const bool LoadVersion14(CGLContextData& Data){
		CB::Log::Write(L"Loading GL Version 1.4", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcVersion14>(Data);
	}

	const bool LoadVersion15(CGLContextData& Data){
		CB::Log::Write(L"Loading GL Version 1.5", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcVersion15>(Data);
	}
		
	// GL Extensions Loading

	const bool LoadVBO(CGLContextData& Data){
		CB::Log::Write(L"Loading GL Vertex Buffer Objects Extension.", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcVBO>(Data);
	}

	const bool LoadStencilTwoSide(CGLContextData& Data){
		CB::Log::Write(L"Loading GL Stencil two side Extension.", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcStencilTwoSide>(Data);
	}

	// WGL Extensions Loading

	const bool LoadExtensionsString(CGLContextData& Data){
		CB::Log::Write(L"Loading WGL Extensions String Extension.", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcExtensionsString>(Data);
	}

	const bool LoadPixelBuffer(CGLContextData& Data){
		CB::Log::Write(L"Loading WGL Pixel Buffer Extension.", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcPixelBuffer>(Data);
	}

	const bool LoadPixelFormat(CGLContextData& Data){
		CB::Log::Write(L"Loading WGL Pixel Format Extension.", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcPixelFormat>(Data);
	}

	const bool LoadMakeCurrentRead(CGLContextData& Data){
		CB::Log::Write(L"Loading WGL Make Current Read Extension.", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcMakeCurrentRead>(Data);
	}

	const bool LoadCreateContext(CGLContextData& Data){
		CB::Log::Write(L"Loading WGL Create Context Extension.", CB::Log::LogLevel::Debug);
		return LoadProcs<LoadProcCreateContext>(Data);
	}

#pragma endregion

	CGLRenderContext::CGLRenderContext(const IDeviceContext& DC) :
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

	CGLRenderContext::CGLRenderContext(const IDeviceContext& DC, const IRenderContext& ShareRC) :
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

	CGLRenderContext::CGLRenderContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs) :
		m_pData(0)
	{
		this->CreateContext(DC, Attribs, 0);
		{
			CRCBindGuard guard;
			this->Bind(DC);
			this->CheckVersion();
			this->LoadExtensionInfo(DC);
		}
	}

	CGLRenderContext::CGLRenderContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs, const IRenderContext& ShareRC) :
		m_pData(0)
	{
		this->CreateContext(DC, Attribs, ShareRC.Get());
		{
			CRCBindGuard guard;
			this->Bind(DC);
			this->CheckVersion();
			this->LoadExtensionInfo(DC);
		}
	}

	CGLRenderContext::~CGLRenderContext(){
		auto pData = (CGLContextData*)this->m_pData;
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

	const bool	CGLRenderContext::Bind(const IDeviceContext& DC){
		auto pData = (CGLContextData*)this->m_pData;
		return wglMakeCurrent((HDC)DC.Get(), pData->m_hRC) ? true : false;
	}

	void	CGLRenderContext::Unbind(){
		wglMakeCurrent(0, 0);
	}

	const bool	CGLRenderContext::IsBinded() const{
		auto pData = (CGLContextData*)this->m_pData;
		return wglGetCurrentContext() == pData->m_hRC;
	}

	void*	CGLRenderContext::Get() const {
		auto pData = (CGLContextData*)this->m_pData;
		return pData->m_hRC;
	}

	const bool	CGLRenderContext::IsSupported(const GLVersion uVersion) const{
		switch (uVersion){
		case GLVersion::V_1_2:	return m_uVMaj >= 1 && m_uVMin >= 2;
		case GLVersion::V_1_3:	return m_uVMaj >= 1 && m_uVMin >= 3;
		case GLVersion::V_1_4:	return m_uVMaj >= 1 && m_uVMin >= 4;
		case GLVersion::V_1_5:	return m_uVMaj >= 1 && m_uVMin >= 5;
		case GLVersion::V_2_0:	return m_uVMaj >= 2 && m_uVMin >= 0;
		case GLVersion::V_2_1:	return m_uVMaj >= 2 && m_uVMin >= 1;
		case GLVersion::V_3_0:	return m_uVMaj >= 3 && m_uVMin >= 0;
		case GLVersion::V_3_1:	return m_uVMaj >= 3 && m_uVMin >= 1;
		case GLVersion::V_3_2:	return m_uVMaj >= 3 && m_uVMin >= 2;
		case GLVersion::V_3_3:	return m_uVMaj >= 3 && m_uVMin >= 3;
		default:
			return false;
		}
	}

	const bool	CGLRenderContext::IsSupported(const GLExtension uExtension) const{
		switch (uExtension){
		case GLExtension::VertexBufferObjects:
			return IsGLExtensionSupported(L"vertex_buffer_object");

		case GLExtension::MipMapGeneration:
			return IsGLExtensionSupported(L"generate_mipmap");

		case GLExtension::AnisotropicFiltering:
			return IsGLExtensionSupported(L"texture_filter_anisotropic");

		case GLExtension::StencilTwoSide:
			return IsGLExtensionSupported(L"stencil_two_side");

		default:
			return false;
		}
	}

	const bool	CGLRenderContext::IsSupported(const WGLExtension uExtension) const{
		switch (uExtension){
		case WGLExtension::ExtensionsString:
			return !this->m_strWGLExtensions.IsEmptyOrWhiteSpace();

		case WGLExtension::PixelFormat:
			return IsWGLExtSupported(L"pixel_format");

		case WGLExtension::PixelBuffer:
			return IsWGLExtSupported(L"pbuffer");

		case WGLExtension::MakeCurrentRead:
			return IsWGLExtSupported(L"make_current_read");

		case WGLExtension::CreateContext:
			return IsWGLExtSupported(L"create_context");

		case WGLExtension::CreateContextProfile:
			return IsWGLExtSupported(L"create_context_profile");

		case WGLExtension::Multisample:
			return IsWGLExtSupported(L"multisample");

		default:
			return false;
		}
	}

	const bool	CGLRenderContext::Load(const GLVersion uVersion){
		auto pData = (CGLContextData*)this->m_pData;
		switch (uVersion){
		case GLVersion::V_1_2:
			return LoadVersion12(*pData);

		case GLVersion::V_1_3:
			return LoadVersion13(*pData);

		case GLVersion::V_1_4:
			return LoadVersion14(*pData);

		case GLVersion::V_1_5:
			return LoadVersion15(*pData);

		default:
			return false;
		}
	}

	const bool	CGLRenderContext::Load(const GLExtension uExtension){
		auto pData = (CGLContextData*)this->m_pData;
		switch (uExtension){
		case GLExtension::VertexBufferObjects:
			return LoadVBO(*pData);

		case GLExtension::StencilTwoSide:
			return LoadStencilTwoSide(*pData);

		case GLExtension::AnisotropicFiltering:
		case GLExtension::MipMapGeneration:
			return IsSupported(uExtension);

		default:
			return false;
		}
	}

	const bool	CGLRenderContext::Load(const WGLExtension uExtension){
		auto pData = (CGLContextData*)this->m_pData;
		switch (uExtension)
		{
		case WGLExtension::CreateContext:
			return LoadCreateContext(*pData);

		case WGLExtension::MakeCurrentRead:
			return LoadMakeCurrentRead(*pData);

		case WGLExtension::PixelBuffer:
			return LoadPixelBuffer(*pData);

		case WGLExtension::PixelFormat:
			return LoadPixelFormat(*pData);

		case WGLExtension::Multisample:
		case WGLExtension::ExtensionsString:
		case WGLExtension::CreateContextProfile:
			return IsSupported(uExtension);

		default:
			return false;
		}
	}

	void	CGLRenderContext::CheckVersion(){
		auto szVersion = this->glGetString(GL::GL_VERSION);	CR_GLCHECK();
		if(!szVersion){
			CR_THROW(L"failed to retrieve GL version.");
		}

		auto strVersion = String::FromANSI(reinterpret_cast<const int8*>(szVersion));

		if(!GLUtils::GetVersion(strVersion, m_uVMaj, m_uVMin)){
			CR_THROW(L"Failed to parse OGL Version: " + strVersion);
		}
	}

	const int32	CGLRenderContext::ChoosePixelFormat(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs) const{
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

		if(newAttribsInt[newAttribsInt.GetLength() - 2] != 0 && newAttribsInt[newAttribsInt.GetLength() - 1]){
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

	void	CGLRenderContext::CreateContext(const IDeviceContext& DC){
		auto pData = (CGLContextData*)this->m_pData;
		
		auto hRC = wglCreateContext((HDC)DC.Get());
		if(hRC == 0){
			CR_THROWWIN(GetLastError(), L"Failed to create GL Legacy Context.");
		}
		this->m_pData = new CGLContextData(hRC);
	}

	void	CGLRenderContext::CreateContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs, void* hShareRC){
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

		WGL::PROC::PFNWGLCREATECONTEXTATTRIBSPROC wglCreate = (WGL::PROC::PFNWGLCREATECONTEXTATTRIBSPROC)this->wglGetProcAddress((int8*)"wglCreateContextAttribsARB");
		if(wglCreate == 0){
			CR_THROWWIN(GetLastError(), L"Failed to load context creation proc.");
		}

		auto hRC = wglCreate((HDC)DC.Get(), (HGLRC)hShareRC, newAttribs.GetPointer());
		if(hRC == 0){
			CR_THROWWIN(GetLastError(), L"Failed to create GL Core Context.");
		}
		this->m_pData = new CGLContextData(hRC);		
	}

	void		CGLRenderContext::LoadExtensionInfo(const IDeviceContext& DC){
		if(!this->LoadGLExtensionInfo()){
			CR_THROW(L"Failed to load info about GL extensions.");
		}
		if(!this->LoadWGLExtensionInfo(DC)){
			CR_THROW(L"Failed to load info about WGL extensions.");
		}
	}

	const bool	CGLRenderContext::LoadGLExtensionInfo(){
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

	const bool	CGLRenderContext::LoadWGLExtensionInfo(const IDeviceContext& DC){
		if(!LoadExtensionsString(*(CGLContextData*)this->m_pData))
			return false;

		const int8* szExtString = this->wglGetExtensionsString(DC);
		if(szExtString == 0)
			return false;

		this->m_strWGLExtensions = CB::String::FromANSI(szExtString);
		return true;
	}

	const bool	CGLRenderContext::IsGLExtensionSupported(const CB::CString& strPrefix, const CB::CString& strName) const{
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

	const bool	CGLRenderContext::IsGLExtensionSupported(const CB::CString& strName) const{
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

	const bool	CGLRenderContext::IsWGLExtSupported(const CB::CString& strPrefix, const CB::CString& strName) const{
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

	const bool	CGLRenderContext::IsWGLExtSupported(const CB::CString& strName) const{
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


	inline CGLContextData* GetData(void* pData){
		return (CGLContextData*)pData;
	}

#pragma region GL Methods

#pragma region Version 1.0
	//	VERSION 1.0
	void CGLRenderContext::glCullFace (GLenum mode){
		return GL::PROC::glCullFace (mode);
	}
	void CGLRenderContext::glFrontFace (GLenum mode){
		return GL::PROC::glFrontFace (mode);
	}
	void CGLRenderContext::glHint (GLenum target, GLenum mode){
		return GL::PROC::glHint (target, mode);
	}
	void CGLRenderContext::glLineWidth (GLfloat width){
		return GL::PROC::glLineWidth (width);
	}
	void CGLRenderContext::glPointSize (GLfloat size){
		return GL::PROC::glPointSize (size);
	}
	void CGLRenderContext::glPolygonMode (GLenum face, GLenum mode){
		return GL::PROC::glPolygonMode (face, mode);
	}
	void CGLRenderContext::glScissor (GLint x, GLint y, GLsizei width, GLsizei height){
		return GL::PROC::glScissor (x, y, width, height);
	}
	void CGLRenderContext::glTexParameterf (GLenum target, GLenum pname, GLfloat param){
		return GL::PROC::glTexParameterf (target, pname, param);
	}
	void CGLRenderContext::glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params){
		return GL::PROC::glTexParameterfv (target, pname, params);
	}
	void CGLRenderContext::glTexParameteri (GLenum target, GLenum pname, GLint param){
		return GL::PROC::glTexParameteri (target, pname, param);
	}
	void CGLRenderContext::glTexParameteriv (GLenum target, GLenum pname, const GLint *params){
		return GL::PROC::glTexParameteriv (target, pname, params);
	}
	void CGLRenderContext::glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels){
		return GL::PROC::glTexImage1D (target, level, internalformat, width, border, format, type, pixels);
	}
	void CGLRenderContext::glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels){
		return GL::PROC::glTexImage2D (target, level, internalformat, width, height, border, format, type, pixels);
	}
	void CGLRenderContext::glDrawBuffer (GLenum mode){
		return GL::PROC::glDrawBuffer (mode);
	}
	void CGLRenderContext::glClear (GLbitfield mask){
		return GL::PROC::glClear (mask);
	}
	void CGLRenderContext::glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
		return GL::PROC::glClearColor (red, green, blue, alpha);
	}
	void CGLRenderContext::glClearStencil (GLint s){
		return GL::PROC::glClearStencil (s);
	}
	void CGLRenderContext::glClearDepth (GLdouble depth){
		return GL::PROC::glClearDepth (depth);
	}
	void CGLRenderContext::glStencilMask (GLuint mask){
		return GL::PROC::glStencilMask (mask);
	}
	void CGLRenderContext::glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){
		return GL::PROC::glColorMask (red, green, blue, alpha);
	}
	void CGLRenderContext::glDepthMask (GLboolean flag){
		return GL::PROC::glDepthMask (flag);
	}
	void CGLRenderContext::glDisable (GLenum cap){
		return GL::PROC::glDisable (cap);
	}
	void CGLRenderContext::glEnable (GLenum cap){
		return GL::PROC::glEnable (cap);
	}
	void CGLRenderContext::glFinish (void){
		return GL::PROC::glFinish ();
	}
	void CGLRenderContext::glFlush (void){
		return GL::PROC::glFlush ();
	}
	void CGLRenderContext::glBlendFunc (GLenum sfactor, GLenum dfactor){
		return GL::PROC::glBlendFunc (sfactor, dfactor);
	}
	void CGLRenderContext::glLogicOp (GLenum opcode){
		return GL::PROC::glLogicOp (opcode);
	}
	void CGLRenderContext::glStencilFunc (GLenum func, GLint ref, GLuint mask){
		return GL::PROC::glStencilFunc (func, ref, mask);
	}
	void CGLRenderContext::glStencilOp (GLenum fail, GLenum zfail, GLenum zpass){
		return GL::PROC::glStencilOp (fail, zfail, zpass);
	}
	void CGLRenderContext::glDepthFunc (GLenum func){
		return GL::PROC::glDepthFunc (func);
	}
	void CGLRenderContext::glPixelStoref (GLenum pname, GLfloat param){
		return GL::PROC::glPixelStoref (pname, param);
	}
	void CGLRenderContext::glPixelStorei (GLenum pname, GLint param){
		return GL::PROC::glPixelStorei (pname, param);
	}
	void CGLRenderContext::glReadBuffer (GLenum mode){
		return GL::PROC::glReadBuffer (mode);
	}
	void CGLRenderContext::glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels){
		return GL::PROC::glReadPixels (x, y, width, height, format, type, pixels);
	}
	void CGLRenderContext::glGetBooleanv (GLenum pname, GLboolean *params){
		return GL::PROC::glGetBooleanv (pname, params);
	}
	void CGLRenderContext::glGetDoublev (GLenum pname, GLdouble *params){
		return GL::PROC::glGetDoublev (pname, params);
	}
	GLenum glGetError (void){
		return GL::PROC::glGetError ();
	}
	void CGLRenderContext::glGetFloatv (GLenum pname, GLfloat *params){
		return GL::PROC::glGetFloatv (pname, params);
	}
	void CGLRenderContext::glGetIntegerv (GLenum pname, GLint *params){
		return GL::PROC::glGetIntegerv (pname, params);
	}
	const GLubyte* CGLRenderContext::glGetString (GLenum name) const{
		return GL::PROC::glGetString (name);
	}
	void CGLRenderContext::glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels){
		return GL::PROC::glGetTexImage (target, level, format, type, pixels);
	}
	void CGLRenderContext::glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params){
		return GL::PROC::glGetTexParameterfv (target, pname, params);
	}
	void CGLRenderContext::glGetTexParameteriv (GLenum target, GLenum pname, GLint *params){
		return GL::PROC::glGetTexParameteriv (target, pname, params);
	}
	void CGLRenderContext::glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params){
		return GL::PROC::glGetTexLevelParameterfv (target, level, pname, params);
	}
	void CGLRenderContext::glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params){
		return GL::PROC::glGetTexLevelParameteriv (target, level, pname, params);
	}
	GLboolean glIsEnabled (GLenum cap){
		return GL::PROC::glIsEnabled (cap);
	}
	void CGLRenderContext::glDepthRange (GLdouble near, GLdouble far){
		return GL::PROC::glDepthRange (near, far);
	}
	void CGLRenderContext::glViewport (GLint x, GLint y, GLsizei width, GLsizei height){
		return GL::PROC::glViewport (x, y, width, height);
	}
#pragma endregion

#pragma region Version 1.1
	//	VERSION 1.1
	void CGLRenderContext::glDrawArrays (GLenum mode, GLint first, GLsizei count){
		return GL::PROC::glDrawArrays (mode, first, count);
	}
	void CGLRenderContext::glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices){
		return GL::PROC::glDrawElements (mode, count, type, indices);
	}
	void CGLRenderContext::glGetPointerv (GLenum pname, GLvoid **params){
		return GL::PROC::glGetPointerv (pname, params);
	}
	void CGLRenderContext::glPolygonOffset (GLfloat factor, GLfloat units){
		return GL::PROC::glPolygonOffset (factor, units);
	}
	void CGLRenderContext::glCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){
		return GL::PROC::glCopyTexImage1D (target, level, internalformat, x, y, width, border);
	}
	void CGLRenderContext::glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){
		return GL::PROC::glCopyTexImage2D (target, level, internalformat, x, y, width, height, border);
	}
	void CGLRenderContext::glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){
		return GL::PROC::glCopyTexSubImage1D (target, level, xoffset, x, y, width);
	}
	void CGLRenderContext::glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
		return GL::PROC::glCopyTexSubImage2D (target, level, xoffset, yoffset, x, y, width, height);
	}
	void CGLRenderContext::glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels){
		return GL::PROC::glTexSubImage1D (target, level, xoffset, width, format, type, pixels);
	}
	void CGLRenderContext::glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels){
		return GL::PROC::glTexSubImage2D (target, level, xoffset, yoffset, width, height, format, type, pixels);
	}
	void CGLRenderContext::glBindTexture (GLenum target, GLuint texture){
		return GL::PROC::glBindTexture (target, texture);
	}
	void CGLRenderContext::glDeleteTextures (GLsizei n, const GLuint *textures){
		return GL::PROC::glDeleteTextures (n, textures);
	}
	void CGLRenderContext::glGenTextures (GLsizei n, GLuint *textures){
		return GL::PROC::glGenTextures (n, textures);
	}
	GLboolean CGLRenderContext::glIsTexture (GLuint texture){
		return GL::PROC::glIsTexture (texture);
	}
#pragma endregion

#pragma region Version 1.2
	//	VERSION 1.2
	void CGLRenderContext::glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices){
		GetData(this->m_pData)->glDrawRangeElements (mode, start, end, count, type, indices);
	}

	void CGLRenderContext::glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels){
		GetData(this->m_pData)->glTexImage3D (target, level, internalformat, width, height, depth, border, format, type, pixels);
	}

	void CGLRenderContext::glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){
		GetData(this->m_pData)->glTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	void CGLRenderContext::glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){
		GetData(this->m_pData)->glCopyTexSubImage3D (target, level, xoffset, yoffset, zoffset, x, y, width, height);
	}
#pragma endregion

#pragma region Version 1.3
	//	VERSION 1.3
	void CGLRenderContext::glActiveTexture (GLenum texture){
		GetData(this->m_pData)->glActiveTexture (texture);
	}

	void CGLRenderContext::glSampleCoverage (GLfloat value, GLboolean invert){
		GetData(this->m_pData)->glSampleCoverage (value, invert);
	}

	void CGLRenderContext::glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data){
		GetData(this->m_pData)->glCompressedTexImage3D (target, level, internalformat, width, height, depth, border, imageSize, data);
	}

	void CGLRenderContext::glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data){
		GetData(this->m_pData)->glCompressedTexImage2D (target, level, internalformat, width, height, border, imageSize, data);
	}

	void CGLRenderContext::glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data){
		GetData(this->m_pData)->glCompressedTexImage1D (target, level, internalformat, width, border, imageSize, data);
	}

	void CGLRenderContext::glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data){
		GetData(this->m_pData)->glCompressedTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	void CGLRenderContext::glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data){
		GetData(this->m_pData)->glCompressedTexSubImage2D (target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	void CGLRenderContext::glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data){
		GetData(this->m_pData)->glCompressedTexSubImage1D (target, level, xoffset, width, format, imageSize, data);
	}

	void CGLRenderContext::glGetCompressedTexImage (GLenum target, GLint level, GLvoid *img){
		GetData(this->m_pData)->glGetCompressedTexImage (target, level, img);
	}
#pragma endregion

#pragma region Version 1.4
	//	VERSION 1.4
	void CGLRenderContext::glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){
		GetData(this->m_pData)->glBlendFuncSeparate (sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	}

	void CGLRenderContext::glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount){
		GetData(this->m_pData)->glMultiDrawArrays (mode, first, count, drawcount);
	}
	
	void CGLRenderContext::glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount){
		GetData(this->m_pData)->glMultiDrawElements (mode, count, type, indices, drawcount);
	}
	
	void CGLRenderContext::glPointParameterf (GLenum pname, GLfloat param){
		GetData(this->m_pData)->glPointParameterf (pname, param);
	}
	
	void CGLRenderContext::glPointParameterfv (GLenum pname, const GLfloat *params){
		GetData(this->m_pData)->glPointParameterfv (pname, params);
	}
	
	void CGLRenderContext::glPointParameteri (GLenum pname, GLint param){
		GetData(this->m_pData)->glPointParameteri (pname, param);
	}
	
	void CGLRenderContext::glPointParameteriv (GLenum pname, const GLint *params){
		GetData(this->m_pData)->glPointParameteriv (pname, params);
	}
	
	void CGLRenderContext::glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
		GetData(this->m_pData)->glBlendColor (red, green, blue, alpha);
	}
	
	void CGLRenderContext::glBlendEquation (GLenum mode){
		GetData(this->m_pData)->glBlendEquation (mode);
	}
#pragma endregion

#pragma region Version 1.5

	void CGLRenderContext::glGenQueries (GLsizei n, GLuint *ids){
		GetData(this->m_pData)->glGenQueries (n, ids);
	}
	
	void CGLRenderContext::glDeleteQueries (GLsizei n, const GLuint *ids){
		GetData(this->m_pData)->glDeleteQueries (n, ids);
	}
	
	GLboolean CGLRenderContext::glIsQuery (GLuint id){
		return GetData(this->m_pData)->glIsQuery (id);
	}
	
	void CGLRenderContext::glBeginQuery (GLenum target, GLuint id){
		GetData(this->m_pData)->glBeginQuery (target, id);
	}
	
	void CGLRenderContext::glEndQuery (GLenum target){
		GetData(this->m_pData)->glEndQuery (target);
	}
	
	void CGLRenderContext::glGetQueryiv (GLenum target, GLenum pname, GLint *params){
		GetData(this->m_pData)->glGetQueryiv (target, pname, params);
	}
	
	void CGLRenderContext::glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params){
		GetData(this->m_pData)->glGetQueryObjectiv (id, pname, params);
	}
	
	void CGLRenderContext::glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params){
		GetData(this->m_pData)->glGetQueryObjectuiv (id, pname, params);
	}
	
	void CGLRenderContext::glBindBuffer (GLenum target, GLuint buffer){
		GetData(this->m_pData)->glBindBuffer (target, buffer);
	}
	
	void CGLRenderContext::glDeleteBuffers (GLsizei n, const GLuint *buffers){
		GetData(this->m_pData)->glDeleteBuffers (n, buffers);
	}
	
	void CGLRenderContext::glGenBuffers (GLsizei n, GLuint *buffers){
		GetData(this->m_pData)->glGenBuffers (n, buffers);
	}
	
	GLboolean CGLRenderContext::glIsBuffer (GLuint buffer){
		return GetData(this->m_pData)->glIsBuffer (buffer);
	}
	
	void CGLRenderContext::glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage){
		GetData(this->m_pData)->glBufferData (target, size, data, usage);
	}
	
	void CGLRenderContext::glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data){
		GetData(this->m_pData)->glBufferSubData (target, offset, size, data);
	}
	
	void CGLRenderContext::glGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data){
		GetData(this->m_pData)->glGetBufferSubData (target, offset, size, data);
	}
	
	void* CGLRenderContext::glMapBuffer (GLenum target, GLenum access){
		return GetData(this->m_pData)->glMapBuffer (target, access);
	}
	
	GLboolean CGLRenderContext::glUnmapBuffer (GLenum target){
		return GetData(this->m_pData)->glUnmapBuffer (target);
	}
	
	void CGLRenderContext::glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params){
		GetData(this->m_pData)->glGetBufferParameteriv (target, pname, params);
	}
	
	void CGLRenderContext::glGetBufferPointerv (GLenum target, GLenum pname, GLvoid **params){
		GetData(this->m_pData)->glGetBufferPointerv (target, pname, params);
	}

#pragma endregion

#pragma region Extensions

	//	EXT Stencil Two Face
	void	CGLRenderContext::glActiveStencilFace(GLenum face){
		GetData(this->m_pData)->glActiveStencilFace(face);
	}

#pragma endregion

#pragma region WGL Extensions

	PROC CGLRenderContext::wglGetProcAddress(const int8* szName){
		return ::wglGetProcAddress((const char*)szName);
	}

	bool CGLRenderContext::wglShareLists(const IRenderContext& shareTo, const IRenderContext& shareFrom){
		return ::wglShareLists((HGLRC)shareTo.Get(), (HGLRC)shareFrom.Get()) ? true : false;
	}

	//	WGL_extensions_string
	const int8* CGLRenderContext::wglGetExtensionsString (const IDeviceContext& DC){
		return GetData(this->m_pData)->wglGetExtensionsString ((HDC)DC.Get());
	}

	//	WGL_PBuffer
	void* CGLRenderContext::wglCreatePbuffer (const IDeviceContext& DC, int32 iPixelFormat, int32 iWidth, int32 iHeight, const int32 *piAttribList){
		return GetData(this->m_pData)->wglCreatePbuffer ((HDC)DC.Get(), iPixelFormat, iWidth, iHeight, piAttribList);
	}

	void* CGLRenderContext::wglGetPbufferDC (void* hPbuffer){
		return GetData(this->m_pData)->wglGetPbufferDC ((HPBUFFER)hPbuffer);
	}
	
	int32	CGLRenderContext::wglReleasePbufferDC (void* hPbuffer, const IDeviceContext& DC){
		return GetData(this->m_pData)->wglReleasePbufferDC ((HPBUFFER)hPbuffer, (HDC)DC.Get());
	}
	
	bool CGLRenderContext::wglDestroyPbuffer (void* hPbuffer){
		return GetData(this->m_pData)->wglDestroyPbuffer ((HPBUFFER)hPbuffer) ? true : false;
	}
	
	bool CGLRenderContext::wglQueryPbuffer (void* hPbuffer, int32 iAttribute, int32 *piValue){
		return GetData(this->m_pData)->wglQueryPbuffer ((HPBUFFER)hPbuffer, iAttribute, piValue) ? true : false;
	}

	//	WGL_pixel_format
	bool CGLRenderContext::wglGetPixelFormatAttribiv (const IDeviceContext& DC, int32 iPixelFormat, int32 iLayerPlane, uint32 nAttributes, const int32 *piAttributes, int32 *piValues){
		return GetData(this->m_pData)->wglGetPixelFormatAttribiv ((HDC)DC.Get(), iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues) ? true : false;
	}
	
	bool CGLRenderContext::wglGetPixelFormatAttribfv (const IDeviceContext& DC, int32 iPixelFormat, int32 iLayerPlane, uint32 nAttributes, const int32 *piAttributes, float32 *pfValues){
		return GetData(this->m_pData)->wglGetPixelFormatAttribfv ((HDC)DC.Get(), iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues) ? true : false;
	}
	
	bool CGLRenderContext::wglChoosePixelFormat (const IDeviceContext& DC, const int32 *piAttribIList, const float32 *pfAttribFList, uint32 nMaxFormats, int32 *piFormats, uint32 *nNumFormats) const{
		return GetData(this->m_pData)->wglChoosePixelFormat ((HDC)DC.Get(), piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats) ? true : false;
	}

	//	WGL_make_current_read
	bool CGLRenderContext::wglMakeContextCurrent (const IDeviceContext& DrawDC, const IDeviceContext& ReadDC, const IRenderContext& GLRC){
		return GetData(this->m_pData)->wglMakeContextCurrent ((HDC)DrawDC.Get(), (HDC)ReadDC.Get(), (HGLRC)GLRC.Get()) ? true : false;
	}
	
	void* CGLRenderContext::wglGetCurrentReadDC (){
		return GetData(this->m_pData)->wglGetCurrentReadDC ();
	}

	//	WGL_create_context
	void* CGLRenderContext::wglCreateContextAttribs (const IDeviceContext& DC, const IRenderContext& ShareContext, const int32 *attribList){
		return GetData(this->m_pData)->wglCreateContextAttribs ((HDC)DC.Get(), (HGLRC)ShareContext.Get(), attribList);
	}

#pragma endregion

#pragma endregion
}

namespace GL{
	GLenum	glGetError(){
		return GL::PROC::glGetError();
	}
	const bool	CheckDCRC(const CB::IDeviceContext& DC, const CB::IRenderContext& RC){
		return (HDC)DC.Get() == wglGetCurrentDC() && (HGLRC)RC.Get();
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
#endif
	}
	void	ReportGLBindMismatch(const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine){
#ifdef CR_GL_ERROR_AS_EXCEPTION
		throw Exception::CException(L"Incorrect gl or device context currently bound.", strFunction, strFile, uLine);
#else
		CB::Log::Write(CB::CString(L"Incorrect GL or Device context currently bound. ") + strFunction + L", " + strFile + L", " + CB::String::ToString(uLine), CB::Log::LogLevel::Warning);
#endif // CR_GL_ERROR_AS_EXCEPTION
	}
}