#include "../Internal/OpenGLDef_Core.h"

namespace GL{
	namespace PROC{
#define GL_PROC(A,B)	A B = 0

#include "../Internal/OpenGL_CoreExt.h"
		
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
		PROC::glMapBuffer (target, access);
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
}