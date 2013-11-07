#include "../Internal/OpenGLDef.h"
#include "../../Common/Include/Exception.h"

//===========================================
//	OpenGL Core Function Pointers
//===========================================

//	VERSION_1_2
PFNGLDRAWRANGEELEMENTSPROC p_glDRAWRANGEELEMENTSPROC = 0;
PFNGLTEXIMAGE3DPROC p_glTEXIMAGE3DPROC = 0;
PFNGLTEXSUBIMAGE3DPROC p_glTEXSUBIMAGE3DPROC = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC p_glCOPYTEXSUBIMAGE3DPROC = 0;

//	VERSION_1_3
PFNGLACTIVETEXTUREPROC p_glACTIVETEXTUREPROC = 0;
PFNGLSAMPLECOVERAGEPROC p_glSAMPLECOVERAGEPROC = 0;
PFNGLCOMPRESSEDTEXIMAGE3DPROC p_glCOMPRESSEDTEXIMAGE3DPROC = 0;
PFNGLCOMPRESSEDTEXIMAGE2DPROC p_glCOMPRESSEDTEXIMAGE2DPROC = 0;
PFNGLCOMPRESSEDTEXIMAGE1DPROC p_glCOMPRESSEDTEXIMAGE1DPROC = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC p_glCOMPRESSEDTEXSUBIMAGE3DPROC = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC p_glCOMPRESSEDTEXSUBIMAGE2DPROC = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC p_glCOMPRESSEDTEXSUBIMAGE1DPROC = 0;
PFNGLGETCOMPRESSEDTEXIMAGEPROC p_glGETCOMPRESSEDTEXIMAGEPROC = 0;

//	VERSION_1_5
PFNGLGENQUERIESPROC p_glGENQUERIESPROC = 0;
PFNGLDELETEQUERIESPROC p_glDELETEQUERIESPROC = 0;
PFNGLISQUERYPROC p_glISQUERYPROC = 0;
PFNGLBEGINQUERYPROC p_glBEGINQUERYPROC = 0;
PFNGLENDQUERYPROC p_glENDQUERYPROC = 0;
PFNGLGETQUERYIVPROC p_glGETQUERYIVPROC = 0;
PFNGLGETQUERYOBJECTIVPROC p_glGETQUERYOBJECTIVPROC = 0;
PFNGLGETQUERYOBJECTUIVPROC p_glGETQUERYOBJECTUIVPROC = 0;
PFNGLBINDBUFFERPROC p_glBINDBUFFERPROC = 0;
PFNGLDELETEBUFFERSPROC p_glDELETEBUFFERSPROC = 0;
PFNGLGENBUFFERSPROC p_glGENBUFFERSPROC = 0;
PFNGLISBUFFERPROC p_glISBUFFERPROC = 0;
PFNGLBUFFERDATAPROC p_glBUFFERDATAPROC = 0;
PFNGLBUFFERSUBDATAPROC p_glBUFFERSUBDATAPROC = 0;
PFNGLGETBUFFERSUBDATAPROC p_glGETBUFFERSUBDATAPROC = 0;
PFNGLMAPBUFFERPROC p_glMAPBUFFERPROC = 0;
PFNGLUNMAPBUFFERPROC p_glUNMAPBUFFERPROC = 0;
PFNGLGETBUFFERPARAMETERIVPROC p_glGETBUFFERPARAMETERIVPROC = 0;
PFNGLGETBUFFERPOINTERVPROC p_glGETBUFFERPOINTERVPROC = 0;

//==============================
//	OpenGL WGL Extensions
//==============================

//	WGL_ARB_pbuffer
PFNWGLCREATEPBUFFERARBPROC		wglCreatePBufferARB = 0;
PFNWGLGETPBUFFERDCARBPROC		wglGetPBufferDCARB	= 0;
PFNWGLRELEASEPBUFFERDCARBPROC	wglReleasePBufferDCARB = 0;
PFNWGLDESTROYPBUFFERARBPROC		wglDestroyPBufferARB = 0;
PFNWGLQUERYPBUFFERARBPROC		wglQueryPBufferARB = 0;

//	WGL_ARB_pixel_format
PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = 0;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC	wglGetPixelFormatAttribfvARB = 0;
PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARB = 0;

//	WGL_ARB_make_current_read
PFNWGLMAKECONTEXTCURRENTARBPROC wglMakeContextCurrentARB = 0;
PFNWGLGETCURRENTREADDCARBPROC	wglGetCurrentReadDCARB = 0;

//===============================================================================================
//	FUNCTIONS
//===============================================================================================

//	VERSION_1_2
#pragma region VERSION_1_2

void glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices){
	p_glDRAWRANGEELEMENTSPROC(mode, start, end, count, type, indices);
}

void glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels){
	p_glTEXIMAGE3DPROC(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

void glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){ 
	p_glTEXSUBIMAGE3DPROC(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){ 
	p_glCOPYTEXSUBIMAGE3DPROC(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

#pragma endregion

//	VERSION_1_3
#pragma region VERSION_1_3

void glActiveTexture (GLenum texture){ 
	p_glACTIVETEXTUREPROC(texture);
}

void glSampleCoverage (GLfloat value, GLboolean invert){ 
	p_glSAMPLECOVERAGEPROC(value, invert);
}

void glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data){ 
	p_glCOMPRESSEDTEXIMAGE3DPROC(target, level, internalformat, width, height, depth, border, imageSize, data);
}

void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data){ 
	p_glCOMPRESSEDTEXIMAGE2DPROC(target, level, internalformat, width, height, border, imageSize, data);
}

void glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data){ 
	p_glCOMPRESSEDTEXIMAGE1DPROC(target, level, internalformat, width, border, imageSize, data);
}

void glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data){ 
	p_glCOMPRESSEDTEXSUBIMAGE3DPROC(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data){ 
	p_glCOMPRESSEDTEXSUBIMAGE2DPROC(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data){
	p_glCOMPRESSEDTEXSUBIMAGE1DPROC(target, level, xoffset, width, format, imageSize, data);
}

void glGetCompressedTexImage (GLenum target, GLint level, GLvoid *img){ 
	p_glGETCOMPRESSEDTEXIMAGEPROC(target, level, img);
}

#pragma endregion

//	VERSION_1_4
#pragma region VERSION_1_4

void  glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){ CR_THROWNOTIMPLEMENTED(); }
void  glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount){ CR_THROWNOTIMPLEMENTED(); }
void  glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount){ CR_THROWNOTIMPLEMENTED(); }
void  glPointParameterf (GLenum pname, GLfloat param){ CR_THROWNOTIMPLEMENTED(); }
void  glPointParameterfv (GLenum pname, const GLfloat *params){ CR_THROWNOTIMPLEMENTED(); }
void  glPointParameteri (GLenum pname, GLint param){ CR_THROWNOTIMPLEMENTED(); }
void  glPointParameteriv (GLenum pname, const GLint *params){ CR_THROWNOTIMPLEMENTED(); }
void  glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){ CR_THROWNOTIMPLEMENTED(); }
void  glBlendEquation (GLenum mode){ CR_THROWNOTIMPLEMENTED(); }

#pragma endregion

//	VERSION_1_5
#pragma region VERSION_1_5

void glGenQueries (GLsizei n, GLuint *ids){ CR_THROWNOTIMPLEMENTED(); }
void glDeleteQueries (GLsizei n, const GLuint *ids){ CR_THROWNOTIMPLEMENTED(); }
GLboolean glIsQuery (GLuint id){ CR_THROWNOTIMPLEMENTED(); }
void glBeginQuery (GLenum target, GLuint id){ CR_THROWNOTIMPLEMENTED(); }
void glEndQuery (GLenum target){ CR_THROWNOTIMPLEMENTED(); }
void glGetQueryiv (GLenum target, GLenum pname, GLint *params){ CR_THROWNOTIMPLEMENTED(); }
void glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params){ CR_THROWNOTIMPLEMENTED(); }
void glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params){ CR_THROWNOTIMPLEMENTED(); }

void glBindBuffer (GLenum target, GLuint buffer){ 
	p_glBINDBUFFERPROC(target, buffer);
}

void glDeleteBuffers (GLsizei n, const GLuint *buffers){ 
	p_glDELETEBUFFERSPROC(n, buffers);
}

void glGenBuffers (GLsizei n, GLuint *buffers){ 
	p_glGENBUFFERSPROC(n, buffers);	
}

GLboolean glIsBuffer (GLuint buffer){ 
	return p_glISBUFFERPROC(buffer);
}

void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage){ 
	p_glBUFFERDATAPROC(target, size, data, usage);
}

void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data){ 
	p_glBUFFERSUBDATAPROC(target, offset, size, data);
}

void glGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data){ 
	p_glGETBUFFERSUBDATAPROC(target, offset, size, data);
}

void *glMapBuffer (GLenum target, GLenum access){ 
	return p_glMAPBUFFERPROC(target, access);
}

GLboolean glUnmapBuffer (GLenum target){ 
	return p_glUNMAPBUFFERPROC(target);
}

void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params){ 
	p_glGETBUFFERPARAMETERIVPROC(target, pname, params);
}

void glGetBufferPointerv (GLenum target, GLenum pname, GLvoid **params){
	p_glGETBUFFERPOINTERVPROC(target, pname, params);
}

#pragma endregion

//====================================================================================================
//	LOADING FUNCTIONS
//====================================================================================================

#define GLLoad(_Type, _Var, _str)	if((_Var = (_Type)wglGetProcAddress(_str)) == 0) return false;

const bool	Load_Version_1_2_Core(){
	GLLoad(PFNGLDRAWRANGEELEMENTSPROC, p_glDRAWRANGEELEMENTSPROC, "glDrawRangeElements");
	GLLoad(PFNGLTEXIMAGE3DPROC, p_glTEXIMAGE3DPROC, "glTexImage3D");
	GLLoad(PFNGLTEXSUBIMAGE3DPROC, p_glTEXSUBIMAGE3DPROC, "glTexSubImage3D");
	GLLoad(PFNGLCOPYTEXSUBIMAGE3DPROC, p_glCOPYTEXSUBIMAGE3DPROC, "glCopyTexSubImage3D");

	return true;
}

const bool	Load_Version_1_2_ARB(){
	GLLoad(PFNGLDRAWRANGEELEMENTSPROC, p_glDRAWRANGEELEMENTSPROC, "glDrawRangeElementsARB");
	GLLoad(PFNGLTEXIMAGE3DPROC, p_glTEXIMAGE3DPROC, "glTexImage3DARB");
	GLLoad(PFNGLTEXSUBIMAGE3DPROC, p_glTEXSUBIMAGE3DPROC, "glTexSubImage3DARB");
	GLLoad(PFNGLCOPYTEXSUBIMAGE3DPROC, p_glCOPYTEXSUBIMAGE3DPROC, "glCopyTexSubImage3DARB");

	return true;
}

const bool	Load_Version_1_2_EXT(){
	GLLoad(PFNGLDRAWRANGEELEMENTSPROC, p_glDRAWRANGEELEMENTSPROC, "glDrawRangeElementsEXT");
	GLLoad(PFNGLTEXIMAGE3DPROC, p_glTEXIMAGE3DPROC, "glTexImage3DEXT");
	GLLoad(PFNGLTEXSUBIMAGE3DPROC, p_glTEXSUBIMAGE3DPROC, "glTexSubImage3DEXT");
	GLLoad(PFNGLCOPYTEXSUBIMAGE3DPROC, p_glCOPYTEXSUBIMAGE3DPROC, "glCopyTexSubImage3DEXT");

	return true;
}

const bool	Load_Version_1_2(){
	if(Load_Version_1_2_Core())
		return true;

	if(Load_Version_1_2_ARB())
		return true;

	if(Load_Version_1_2_EXT())
		return true;

	return false;
}

const bool	Load_Version_1_3_Core(){
	GLLoad(PFNGLACTIVETEXTUREPROC, p_glACTIVETEXTUREPROC, "glActiveTexture");
	GLLoad(PFNGLSAMPLECOVERAGEPROC, p_glSAMPLECOVERAGEPROC, "glSampleCoverage");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE3DPROC, p_glCOMPRESSEDTEXIMAGE3DPROC, "glCompressedTexImage3D");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE2DPROC, p_glCOMPRESSEDTEXIMAGE2DPROC, "glCompressedTexImage2D");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE1DPROC, p_glCOMPRESSEDTEXIMAGE1DPROC, "glCompressedTexImage1D");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, p_glCOMPRESSEDTEXSUBIMAGE3DPROC, "glCompressedTexSubImage3D");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, p_glCOMPRESSEDTEXSUBIMAGE2DPROC, "glCompressedTexSubImage2D");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, p_glCOMPRESSEDTEXSUBIMAGE1DPROC, "glCompressedTexSubImage1D");
	GLLoad(PFNGLGETCOMPRESSEDTEXIMAGEPROC, p_glGETCOMPRESSEDTEXIMAGEPROC, "glGetCompressedTexImage");

	return true;
}

const bool	Load_Version_1_3_ARB(){
	GLLoad(PFNGLACTIVETEXTUREPROC, p_glACTIVETEXTUREPROC, "glActiveTextureARB");
	GLLoad(PFNGLSAMPLECOVERAGEPROC, p_glSAMPLECOVERAGEPROC, "glSampleCoverageARB");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE3DPROC, p_glCOMPRESSEDTEXIMAGE3DPROC, "glCompressedTexImage3DARB");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE2DPROC, p_glCOMPRESSEDTEXIMAGE2DPROC, "glCompressedTexImage2DARB");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE1DPROC, p_glCOMPRESSEDTEXIMAGE1DPROC, "glCompressedTexImage1DARB");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, p_glCOMPRESSEDTEXSUBIMAGE3DPROC, "glCompressedTexSubImage3DARB");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, p_glCOMPRESSEDTEXSUBIMAGE2DPROC, "glCompressedTexSubImage2DARB");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, p_glCOMPRESSEDTEXSUBIMAGE1DPROC, "glCompressedTexSubImage1DARB");
	GLLoad(PFNGLGETCOMPRESSEDTEXIMAGEPROC, p_glGETCOMPRESSEDTEXIMAGEPROC, "glGetCompressedTexImageARB");

	return true;
}

const bool	Load_Version_1_3_EXT(){
	GLLoad(PFNGLACTIVETEXTUREPROC, p_glACTIVETEXTUREPROC, "glActiveTextureEXT");
	GLLoad(PFNGLSAMPLECOVERAGEPROC, p_glSAMPLECOVERAGEPROC, "glSampleCoverageEXT");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE3DPROC, p_glCOMPRESSEDTEXIMAGE3DPROC, "glCompressedTexImage3DEXT");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE2DPROC, p_glCOMPRESSEDTEXIMAGE2DPROC, "glCompressedTexImage2DEXT");
	GLLoad(PFNGLCOMPRESSEDTEXIMAGE1DPROC, p_glCOMPRESSEDTEXIMAGE1DPROC, "glCompressedTexImage1DEXT");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, p_glCOMPRESSEDTEXSUBIMAGE3DPROC, "glCompressedTexSubImage3DEXT");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, p_glCOMPRESSEDTEXSUBIMAGE2DPROC, "glCompressedTexSubImage2DEXT");
	GLLoad(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, p_glCOMPRESSEDTEXSUBIMAGE1DPROC, "glCompressedTexSubImage1DEXT");
	GLLoad(PFNGLGETCOMPRESSEDTEXIMAGEPROC, p_glGETCOMPRESSEDTEXIMAGEPROC, "glGetCompressedTexImageEXT");

	return true;
}

const bool	Load_Version_1_3(){
	if(Load_Version_1_3_Core())
		return true;

	if(Load_Version_1_3_ARB())
		return true;

	if(Load_Version_1_3_EXT())
		return true;

	return false;
}

const bool	Load_VertexBufferObjects_Core(){
	if((p_glBINDBUFFERPROC		= (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer")) == 0) return false;
	if((p_glDELETEBUFFERSPROC	= (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers")) == 0) return false;
	if((p_glGENBUFFERSPROC		= (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers")) == 0) return false;
	if((p_glISBUFFERPROC		= (PFNGLISBUFFERPROC)wglGetProcAddress("glIsBuffer")) == 0) return false;
	if((p_glBUFFERDATAPROC		= (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData")) == 0) return false;
	if((p_glBUFFERSUBDATAPROC	= (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData")) == 0) return false;
	if((p_glGETBUFFERSUBDATAPROC = (PFNGLGETBUFFERSUBDATAPROC)wglGetProcAddress("glGetBufferSubData")) == 0) return false;
	if((p_glMAPBUFFERPROC		= (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBuffer")) == 0) return false;
	if((p_glUNMAPBUFFERPROC		= (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer")) == 0) return false;
	if((p_glGETBUFFERPARAMETERIVPROC = (PFNGLGETBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetBufferParameteriv")) == 0) return false;
	if((p_glGETBUFFERPOINTERVPROC = (PFNGLGETBUFFERPOINTERVPROC)wglGetProcAddress("glGetBufferPointerv")) == 0) return false;

	return true;
}

const bool	Load_VertexBufferObjects_ARB(){
	if((p_glBINDBUFFERPROC		= (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBufferARB")) == 0) return false;
	if((p_glDELETEBUFFERSPROC	= (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffersARB")) == 0) return false;
	if((p_glGENBUFFERSPROC		= (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffersARB")) == 0) return false;
	if((p_glISBUFFERPROC		= (PFNGLISBUFFERPROC)wglGetProcAddress("glIsBufferARB")) == 0) return false;
	if((p_glBUFFERDATAPROC		= (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferDataARB")) == 0) return false;
	if((p_glBUFFERSUBDATAPROC	= (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubDataARB")) == 0) return false;
	if((p_glGETBUFFERSUBDATAPROC = (PFNGLGETBUFFERSUBDATAPROC)wglGetProcAddress("glGetBufferSubDataARB")) == 0) return false;
	if((p_glMAPBUFFERPROC		= (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBufferARB")) == 0) return false;
	if((p_glUNMAPBUFFERPROC		= (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBufferARB")) == 0) return false;
	if((p_glGETBUFFERPARAMETERIVPROC = (PFNGLGETBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetBufferParameterivARB")) == 0) return false;
	if((p_glGETBUFFERPOINTERVPROC = (PFNGLGETBUFFERPOINTERVPROC)wglGetProcAddress("glGetBufferPointervARB")) == 0) return false;

	return true;
}

const bool	Load_VertexBufferObjects_EXT(){
	if((p_glBINDBUFFERPROC		= (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBufferEXT")) == 0) return false;
	if((p_glDELETEBUFFERSPROC	= (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffersEXT")) == 0) return false;
	if((p_glGENBUFFERSPROC		= (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffersEXT")) == 0) return false;
	if((p_glISBUFFERPROC		= (PFNGLISBUFFERPROC)wglGetProcAddress("glIsBufferEXT")) == 0) return false;
	if((p_glBUFFERDATAPROC		= (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferDataEXT")) == 0) return false;
	if((p_glBUFFERSUBDATAPROC	= (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubDataEXT")) == 0) return false;
	if((p_glGETBUFFERSUBDATAPROC = (PFNGLGETBUFFERSUBDATAPROC)wglGetProcAddress("glGetBufferSubDataEXT")) == 0) return false;
	if((p_glMAPBUFFERPROC		= (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBufferEXT")) == 0) return false;
	if((p_glUNMAPBUFFERPROC		= (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBufferEXT")) == 0) return false;
	if((p_glGETBUFFERPARAMETERIVPROC = (PFNGLGETBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetBufferParameterivEXT")) == 0) return false;
	if((p_glGETBUFFERPOINTERVPROC = (PFNGLGETBUFFERPOINTERVPROC)wglGetProcAddress("glGetBufferPointervEXT")) == 0) return false;

	return true;
}

const bool	Load_VertexBufferObjects(){
	if(Load_VertexBufferObjects_Core())
		return true;

	if(Load_VertexBufferObjects_ARB())
		return true;

	if(Load_VertexBufferObjects_EXT())
		return true;

	return false;
}
