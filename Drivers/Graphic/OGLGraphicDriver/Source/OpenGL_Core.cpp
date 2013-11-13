#include "../Internal/OpenGL_Core.h"
#include "../Internal/OpenGL_WGL.h"

#include <CBString.h>
#include <CBStringEx.h>
#include <Logger.h>

#define APIENTRYP	__stdcall*

namespace GL{
	namespace PROC{
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
	}

	namespace PROC{
#define GL_PROC(A,B)	A B = 0

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
		
#undef GL_PROC
	}

#pragma region Version 1.2
	//	VERSION 1.2
	void glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices){
		PROC::glDrawRangeElements (mode, start, end, count, type, indices);
	}

	void glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels){
		PROC::glTexImage3D (target, level, internalformat, width, height, depth, border, format, type, pixels);
	}

	void glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){
		PROC::glTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	void glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){
		PROC::glCopyTexSubImage3D (target, level, xoffset, yoffset, zoffset, x, y, width, height);
	}
#pragma endregion

#pragma region Version 1.3
	//	VERSION 1.3
	void glActiveTexture (GLenum texture){
		PROC::glActiveTexture (texture);
	}

	void glSampleCoverage (GLfloat value, GLboolean invert){
		PROC::glSampleCoverage (value, invert);
	}

	void glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data){
		PROC::glCompressedTexImage3D (target, level, internalformat, width, height, depth, border, imageSize, data);
	}

	void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data){
		PROC::glCompressedTexImage2D (target, level, internalformat, width, height, border, imageSize, data);
	}

	void glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data){
		PROC::glCompressedTexImage1D (target, level, internalformat, width, border, imageSize, data);
	}

	void glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data){
		PROC::glCompressedTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data){
		PROC::glCompressedTexSubImage2D (target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	void glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data){
		PROC::glCompressedTexSubImage1D (target, level, xoffset, width, format, imageSize, data);
	}

	void glGetCompressedTexImage (GLenum target, GLint level, GLvoid *img){
		PROC::glGetCompressedTexImage (target, level, img);
	}
#pragma endregion

#pragma region Version 1.4
	//	VERSION 1.4
	void  glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){
		PROC::glBlendFuncSeparate (sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	}

	void  glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount){
		PROC::glMultiDrawArrays (mode, first, count, drawcount);
	}
	
	void  glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount){
		PROC::glMultiDrawElements (mode, count, type, indices, drawcount);
	}
	
	void  glPointParameterf (GLenum pname, GLfloat param){
		PROC::glPointParameterf (pname, param);
	}
	
	void  glPointParameterfv (GLenum pname, const GLfloat *params){
		PROC::glPointParameterfv (pname, params);
	}
	
	void  glPointParameteri (GLenum pname, GLint param){
		PROC::glPointParameteri (pname, param);
	}
	
	void  glPointParameteriv (GLenum pname, const GLint *params){
		PROC::glPointParameteriv (pname, params);
	}
	
	void  glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
		PROC::glBlendColor (red, green, blue, alpha);
	}
	
	void  glBlendEquation (GLenum mode){
		PROC::glBlendEquation (mode);
	}
#pragma endregion

#pragma region Version 1.5

	void glGenQueries (GLsizei n, GLuint *ids){
		PROC::glGenQueries (n, ids);
	}
	
	void glDeleteQueries (GLsizei n, const GLuint *ids){
		PROC::glDeleteQueries (n, ids);
	}
	
	GLboolean glIsQuery (GLuint id){
		return PROC::glIsQuery (id);
	}
	
	void glBeginQuery (GLenum target, GLuint id){
		PROC::glBeginQuery (target, id);
	}
	
	void glEndQuery (GLenum target){
		PROC::glEndQuery (target);
	}
	
	void glGetQueryiv (GLenum target, GLenum pname, GLint *params){
		PROC::glGetQueryiv (target, pname, params);
	}
	
	void glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params){
		PROC::glGetQueryObjectiv (id, pname, params);
	}
	
	void glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params){
		PROC::glGetQueryObjectuiv (id, pname, params);
	}
	
	void glBindBuffer (GLenum target, GLuint buffer){
		PROC::glBindBuffer (target, buffer);
	}
	
	void glDeleteBuffers (GLsizei n, const GLuint *buffers){
		PROC::glDeleteBuffers (n, buffers);
	}
	
	void glGenBuffers (GLsizei n, GLuint *buffers){
		PROC::glGenBuffers (n, buffers);
	}
	
	GLboolean glIsBuffer (GLuint buffer){
		return PROC::glIsBuffer (buffer);
	}
	
	void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage){
		PROC::glBufferData (target, size, data, usage);
	}
	
	void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data){
		PROC::glBufferSubData (target, offset, size, data);
	}
	
	void glGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data){
		PROC::glGetBufferSubData (target, offset, size, data);
	}
	
	void *glMapBuffer (GLenum target, GLenum access){
		return PROC::glMapBuffer (target, access);
	}
	
	GLboolean glUnmapBuffer (GLenum target){
		return PROC::glUnmapBuffer (target);
	}
	
	void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params){
		PROC::glGetBufferParameteriv (target, pname, params);
	}
	
	void glGetBufferPointerv (GLenum target, GLenum pname, GLvoid **params){
		PROC::glGetBufferPointerv (target, pname, params);
	}

#pragma endregion

	//============================================================
	//	Proc loading namespace
	//============================================================
	namespace Loader{

		//========================================================
		//	GLOBALS
		//========================================================
		CB::CString	g_strExtensionString;

		//========================================================
		//	Raw proc loading funcs
		//========================================================

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

#pragma region Core Loading

		const bool	LoadProcVersion12(const CB::CString& strSufix){
			GL_PROC(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
			GL_PROC(PFNGLTEXIMAGE3DPROC, glTexImage3D);
			GL_PROC(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
			GL_PROC(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

			return true;
		}

		const bool	LoadProcVersion13(const CB::CString& strSufix){
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

		const bool	LoadProcVersion14(const CB::CString& strSufix){
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

		const bool	LoadProcVersion15(const CB::CString& strSufix){
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

		const bool LoadProcVBO(const CB::CString& strSufix){
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

#undef GL_PROC

		//========================================================
		//	Proc loading abstract funcs
		//========================================================

		typedef const bool (*load_proc)(const CB::CString&);

		template<load_proc _Func>
		const bool LoadProcs(){

			if(_Func(L""))
				return true;

			if(_Func(L"ARB"))
				return true;

			if(_Func(L"EXT"))
				return true;

			return false;
		}

		const bool LoadVersion12(){
			CB::Log::Write(L"Loading GL Version 1.2", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcVersion12>();
		}

		const bool LoadVersion13(){
			CB::Log::Write(L"Loading GL Version 1.3", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcVersion13>();
		}

		const bool LoadVersion14(){
			CB::Log::Write(L"Loading GL Version 1.4", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcVersion14>();
		}

		const bool LoadVersion15(){
			CB::Log::Write(L"Loading GL Version 1.5", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcVersion15>();
		}
		
		const bool LoadVBO(){
			CB::Log::Write(L"Loading GL Vertex Buffer Objects Extension.", CB::Log::LogLevel::Debug);
			return LoadProcs<LoadProcVBO>();
		}

		//========================================================
		//	Extension checking funcs
		//========================================================

		const bool	IsGLExtensionSupported(const CB::CString& strPrefix, const CB::CString& strName){
			if(g_strExtensionString.IsEmptyOrWhiteSpace()){
				auto szExtString = reinterpret_cast<const int8*>(glGetString(GL_EXTENSIONS));
				if(szExtString == 0){
					CR_THROW(L"Failed to load extensions string.");
				}

				g_strExtensionString = CB::String::FromANSI(szExtString);
				if(g_strExtensionString.IsEmptyOrWhiteSpace()){
					CR_THROW(L"Extensions string is empty.");
				}
			}

			auto strExt = L"GL_" + strPrefix + L"_" + strName;
			if(g_strExtensionString.Find(strExt)){
				CB::Log::Write(strExt + L" found on GL extension string.", CB::Log::LogLevel::Debug);
				return true;
			}
			else{
				CB::Log::Write(strExt + L" NOT found on GL extension string.", CB::Log::LogLevel::Debug);
				return false;
			}
		}

		const bool	IsGLExtensionSupported(const CB::CString& strName){
			if(IsGLExtensionSupported(L"ARB", strName))
				return true;

			if(IsGLExtensionSupported(L"EXT", strName))
				return true;

			return false;
		}

		//========================================================
		//	External loading funcs
		//========================================================

		const bool	IsSupported(const Extension uExtension){
			switch (uExtension)
			{
			case Extension::VertexBufferObjects:
				return IsGLExtensionSupported(L"vertex_buffer_object");

			default:
				return false;
			}
		}

		const bool	Load(const Version uVersion){
			switch (uVersion)
			{
			case Version::V_1_2:
				return LoadVersion12();

			case Version::V_1_3:
				return LoadVersion13();

			case Version::V_1_4:
				return LoadVersion14();

			case Version::V_1_5:
				return LoadVersion15();

			default:
				return false;
			}
		}

		const bool	Load(const Extension uExtension){
			switch (uExtension)
			{
			case Extension::VertexBufferObjects:
				return LoadVBO();

			default:
				return false;
			}
		}
	}

	void	ReportGLError(GLenum uError, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine){
		CB::CString strError = L"GL Error: " + CB::String::FromUInt32(uError);
#ifdef CR_GL_ERROR_AS_EXCEPTION
		throw Exception::CException(strError, strFunction, strFile, uLine);
#else
		CB::Log::Write(strError + L", " + strFunction + L", " + strFile + L", " + CB::String::ToString(uLine), CB::Log::LogLevel::Error);
#endif
	}

}