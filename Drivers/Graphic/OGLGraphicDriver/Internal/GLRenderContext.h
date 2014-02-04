#pragma once

#include <Collection_Interface.h>
#include <CBString.h>

#include "RenderContextInterface.h"
#include "DeviceContextInterface.h"
#include "GLTypes.h"

namespace CB{
	enum class GLVersion{
		V_1_2 = 2,
		V_1_3 = 3,
		V_1_4 = 4,
		V_1_5 = 5,
		V_2_0 = 6,
		V_2_1 = 7,
		V_3_0 = 8,
		V_3_1 = 9,
		V_3_2 = 10,
		V_3_3 = 11,
	};
	
	enum class GLExtension{
		//	GL Extensions
		VertexBufferObjects,
		MipMapGeneration,
		AnisotropicFiltering,
		StencilTwoSide,
	};

	enum class WGLExtension{
		ExtensionsString,
		PixelBuffer,
		PixelFormat,
		MakeCurrentRead,
		CreateContext,
		CreateContextProfile,
		Multisample,
	};

	class CGLRenderContext :
		public IRenderContext
	{
	private:
		mutable void*	m_pData;
		mutable CB::CString		m_strExtensions;
		mutable CB::CString		m_strWGLExtensions;
		uint32	m_uVMaj;
		uint32	m_uVMin;

	public:
		CGLRenderContext(const IDeviceContext& DC);
		CGLRenderContext(const IDeviceContext& DC, const IRenderContext& ShaderRC);
		CGLRenderContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs);
		CGLRenderContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs, const IRenderContext& ShaderRC);
		~CGLRenderContext();

		const bool	Bind(const IDeviceContext& DC) override;
		void		Unbind() override;
		const bool	IsBinded() const override;

		void*	Get() const override;

		const bool	IsSupported(const GLVersion uVersion) const;
		const bool	IsSupported(const GLExtension uExtension) const;
		const bool	IsSupported(const WGLExtension uExtension) const;
		const bool	Load(const GLVersion uVersion);
		const bool	Load(const GLExtension uExtension);
		const bool	Load(const WGLExtension uExtension);

		const int32	ChoosePixelFormat(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs) const;

	private:
		CR_NOCOPY(CGLRenderContext);
		CR_NOASSIGN(CGLRenderContext);

		void		CheckVersion();
		void		LoadExtensionInfo(const IDeviceContext& DC);
		const bool	LoadGLExtensionInfo();
		const bool	LoadWGLExtensionInfo(const IDeviceContext& DC);
		void		CreateContext(const IDeviceContext& DC);
		void		CreateContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs, void* hShareRC);

		const bool	IsGLExtensionSupported(const CB::CString& strPrefix, const CB::CString& strName) const;
		const bool	IsGLExtensionSupported(const CB::CString& strName) const;
		const bool	IsWGLExtSupported(const CB::CString& strPrefix, const CB::CString& strName) const;
		const bool	IsWGLExtSupported(const CB::CString& strName) const;

	public:
		//	VERSION_1_0
		void glCullFace (GLenum mode);
		void glFrontFace (GLenum mode);
		void glHint (GLenum target, GLenum mode);
		void glLineWidth (GLfloat width);
		void glPointSize (GLfloat size);
		void glPolygonMode (GLenum face, GLenum mode);
		void glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
		void glTexParameterf (GLenum target, GLenum pname, GLfloat param);
		void glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
		void glTexParameteri (GLenum target, GLenum pname, GLint param);
		void glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
		void glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
		void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
		void glDrawBuffer (GLenum mode);
		void glClear (GLbitfield mask);
		void glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		void glClearStencil (GLint s);
		void glClearDepth (GLdouble depth);
		void glStencilMask (GLuint mask);
		void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
		void glDepthMask (GLboolean flag);
		void glDisable (GLenum cap);
		void glEnable (GLenum cap);
		void glFinish (void);
		void glFlush (void);
		void glBlendFunc (GLenum sfactor, GLenum dfactor);
		void glLogicOp (GLenum opcode);
		void glStencilFunc (GLenum func, GLint ref, GLuint mask);
		void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
		void glDepthFunc (GLenum func);
		void glPixelStoref (GLenum pname, GLfloat param);
		void glPixelStorei (GLenum pname, GLint param);
		void glReadBuffer (GLenum mode);
		void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
		void glGetBooleanv (GLenum pname, GLboolean *params);
		void glGetDoublev (GLenum pname, GLdouble *params);
		GLenum glGetError (void);
		void glGetFloatv (GLenum pname, GLfloat *params);
		void glGetIntegerv (GLenum pname, GLint *params);
		const GLubyte *glGetString (GLenum name) const;
		void glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
		void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
		void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
		void glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
		void glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
		GLboolean glIsEnabled (GLenum cap);
		void glDepthRange (GLdouble near, GLdouble far);
		void glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
	
		//	VERSION_1_1
		void glDrawArrays (GLenum mode, GLint first, GLsizei count);
		void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
		void glGetPointerv (GLenum pname, GLvoid **params);
		void glPolygonOffset (GLfloat factor, GLfloat units);
		void glCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
		void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
		void glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
		void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		void glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
		void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
		void glBindTexture (GLenum target, GLuint texture);
		void glDeleteTextures (GLsizei n, const GLuint *textures);
		void glGenTextures (GLsizei n, GLuint *textures);
		GLboolean glIsTexture (GLuint texture);

		//	VERSION_1_2
		void glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
		void glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
		void glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
		void glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

		//	VERSION_1_3
		void glActiveTexture (GLenum texture);
		void glSampleCoverage (GLfloat value, GLboolean invert);
		void glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
		void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
		void glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
		void glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
		void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
		void glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
		void glGetCompressedTexImage (GLenum target, GLint level, GLvoid *img);

		//	VERSION_1_4
		void  glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
		void  glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
		void  glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount);
		void  glPointParameterf (GLenum pname, GLfloat param);
		void  glPointParameterfv (GLenum pname, const GLfloat *params);
		void  glPointParameteri (GLenum pname, GLint param);
		void  glPointParameteriv (GLenum pname, const GLint *params);
		void  glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		void  glBlendEquation (GLenum mode);

		//	VERSION_1_5
		void glGenQueries (GLsizei n, GLuint *ids);
		void glDeleteQueries (GLsizei n, const GLuint *ids);
		GLboolean glIsQuery (GLuint id);
		void glBeginQuery (GLenum target, GLuint id);
		void glEndQuery (GLenum target);
		void glGetQueryiv (GLenum target, GLenum pname, GLint *params);
		void glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params);
		void glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
		void glBindBuffer (GLenum target, GLuint buffer);
		void glDeleteBuffers (GLsizei n, const GLuint *buffers);
		void glGenBuffers (GLsizei n, GLuint *buffers);
		GLboolean glIsBuffer (GLuint buffer);
		void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
		void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
		void glGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data);
		void *glMapBuffer (GLenum target, GLenum access);
		GLboolean glUnmapBuffer (GLenum target);
		void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
		void glGetBufferPointerv (GLenum target, GLenum pname, GLvoid **params);

		//========================================
		//	GL Extensions
		//========================================

		void glActiveStencilFace (GLenum face);

		//========================================
		//	WGL
		//========================================
		typedef int32	(__stdcall *PROC)();

		//Standard
		PROC		wglGetProcAddress(const int8* szName);
		bool		wglShareLists(const IRenderContext& shereTo, const IRenderContext& shareFrom);

		//	WGL_extensions_string
		const int8* wglGetExtensionsString (const IDeviceContext& DC);

		//	WGL_pbuffer
		void*	wglCreatePbuffer (const IDeviceContext& DC, int32 iPixelFormat, int32 iWidth, int32 iHeight, const int32 *piAttribList);
		void*	wglGetPbufferDC (void* hPbuffer);
		int		wglReleasePbufferDC (void* hPbuffer, const IDeviceContext& DC);
		bool	wglDestroyPbuffer (void* hPbuffer);
		bool	wglQueryPbuffer (void* hPbuffer, int32 iAttribute, int32 *piValue);

		//	WGL_pixel_format
		bool	wglGetPixelFormatAttribiv (const IDeviceContext& DC, int32 iPixelFormat, int32 iLayerPlane, uint32 nAttributes, const int32 *piAttributes, int32 *piValues);
		bool	wglGetPixelFormatAttribfv (const IDeviceContext& DC, int32 iPixelFormat, int32 iLayerPlane, uint32 nAttributes, const int32 *piAttributes, float32 *pfValues);
		bool	wglChoosePixelFormat (const IDeviceContext& DC, const int32 *piAttribIList, const float32 *pfAttribFList, uint32 nMaxFormats, int32 *piFormats, uint32 *nNumFormats) const;

		//	WGL_make_current_read
		bool	wglMakeContextCurrent (const IDeviceContext& DrawDC, const IDeviceContext& ReadDC, const IRenderContext& glRC);
		void*	wglGetCurrentReadDC ();

		//	WGL_create_context
		void*	wglCreateContextAttribs (const IDeviceContext& DC, const IRenderContext& hShareContext, const int32 *attribList);
	};
}

#define CR_GLCHECK()	{ GLenum __uError = GL::glGetError(); if(__uError != GL::GL_NO_ERROR){ GL::ReportGLError(__uError, CR_INFO()); } }
#define CR_GLBINDCHECK(DC,RC)	{ if(!GL::CheckDCRC(DC, RC)){ GL::ReportGLBindMismatch(CR_INFO()); } } 

namespace GL{
	extern void	ReportGLError(GLenum uError, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
	extern void	ReportGLBindMismatch(const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
	extern GLenum glGetError();
	extern const bool CheckDCRC(const CB::IDeviceContext& DC, const CB::IRenderContext& RC);
}