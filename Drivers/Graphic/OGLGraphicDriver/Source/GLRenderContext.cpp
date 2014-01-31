#include "../Internal/GLRenderContext.h"
#include "../Internal/WinPlatform.h"
#include "../Internal/ContextBindGuard.h"
#include "../Internal/Utils.h"

#include <Exception.h>
#include <Collection_List.h>
#include <Logger.h>

#define APIENTRYP	__stdcall*
#define WINAPI		__stdcall
DECLARE_HANDLE(HPBUFFER);

namespace GL{
	//extern "C" __declspec(dllimport) void* __stdcall wglGetProcAddress(const char*);

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


#define GL_PROC(A,B)	this->B = 0

	CGLContextData(HGLRC hRC) :
		m_hRC(hRC)
	{
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
	}

#undef GL_PROC
};

namespace CB{
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

	void	CGLRenderContext::CheckVersion(){
		auto szVersion = this->glGetString(GL::GL_VERSION);	CR_GLCHECK();
		if(szVersion){
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

		WGL::PROC::PFNWGLCREATECONTEXTATTRIBSPROC wglCreate = (WGL::PROC::PFNWGLCREATECONTEXTATTRIBSPROC)this->wglGetProcAddress("wglCreateContextAttribs");
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
		if(!this->LoadExtensionsString())
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

		return false;
	}

	const bool	CGLRenderContext::IsWGLExtSupported(const CB::CString& strPrefix, const CB::CString& strName) const{
		auto strExt = L"WGL_" + strPrefix + L"_" + strName;
		if(this->m_strWGLExtensions.Find(strExt)){
			CB::Log::Write(strExt + L" found on WGL extension string.", CB::Log::LogLevel::Debug);
			return true;
		}
		else{
			CB::Log::Write(strExt + L" NOT found on WGL extension string.", CB::Log::LogLevel::Debug) const;
			return false;
		}
	}

	const bool	CGLRenderContext::IsWGLExtSupported(const CB::CString& strName) const{
		if(IsWGLExtSupported(L"ARB", strName))
			return true;

		if(IsWGLExtSupported(L"EXT", strName))
			return true;

		return false;
	}
}