#pragma once

#include <CBString.h>
#include "OpenGL_Types.h"

#pragma comment(lib, "opengl32.lib")

#define CR_GLCHECK()	{ GLenum __uError = GL::glGetError(); if(__uError != GL::GL_NO_ERROR){ GL::ReportGLError(__uError, CR_INFO()); } }

//======================
//	OPENGL 1.0 - 1.4 CORE
//======================

namespace GL{
	//	VERSION_1_0
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

	enum VERSION_1_1_TOKENS{
		GL_DEPTH_BUFFER_BIT               = 0x00000100,
		GL_STENCIL_BUFFER_BIT             = 0x00000400,
		GL_COLOR_BUFFER_BIT               = 0x00004000,
		GL_FALSE                          = 0,
		GL_TRUE                           = 1,
		GL_POINTS                         = 0x0000,
		GL_LINES                          = 0x0001,
		GL_LINE_LOOP                      = 0x0002,
		GL_LINE_STRIP                     = 0x0003,
		GL_TRIANGLES                      = 0x0004,
		GL_TRIANGLE_STRIP                 = 0x0005,
		GL_TRIANGLE_FAN                   = 0x0006,
		GL_QUADS                          = 0x0007,
		GL_NEVER                          = 0x0200,
		GL_LESS                           = 0x0201,
		GL_EQUAL                          = 0x0202,
		GL_LEQUAL                         = 0x0203,
		GL_GREATER                        = 0x0204,
		GL_NOTEQUAL                       = 0x0205,
		GL_GEQUAL                         = 0x0206,
		GL_ALWAYS                         = 0x0207,
		GL_ZERO                           = 0,
		GL_ONE                            = 1,
		GL_SRC_COLOR                      = 0x0300,
		GL_ONE_MINUS_SRC_COLOR            = 0x0301,
		GL_SRC_ALPHA                      = 0x0302,
		GL_ONE_MINUS_SRC_ALPHA            = 0x0303,
		GL_DST_ALPHA                      = 0x0304,
		GL_ONE_MINUS_DST_ALPHA            = 0x0305,
		GL_DST_COLOR                      = 0x0306,
		GL_ONE_MINUS_DST_COLOR            = 0x0307,
		GL_SRC_ALPHA_SATURATE             = 0x0308,
		GL_NONE                           = 0,
		GL_FRONT_LEFT                     = 0x0400,
		GL_FRONT_RIGHT                    = 0x0401,
		GL_BACK_LEFT                      = 0x0402,
		GL_BACK_RIGHT                     = 0x0403,
		GL_FRONT                          = 0x0404,
		GL_BACK                           = 0x0405,
		GL_LEFT                           = 0x0406,
		GL_RIGHT                          = 0x0407,
		GL_FRONT_AND_BACK                 = 0x0408,
		GL_NO_ERROR                       = 0,
		GL_INVALID_ENUM                   = 0x0500,
		GL_INVALID_VALUE                  = 0x0501,
		GL_INVALID_OPERATION              = 0x0502,
		GL_OUT_OF_MEMORY                  = 0x0505,
		GL_CW                             = 0x0900,
		GL_CCW                            = 0x0901,
		GL_POINT_SIZE                     = 0x0B11,
		GL_POINT_SIZE_RANGE               = 0x0B12,
		GL_POINT_SIZE_GRANULARITY         = 0x0B13,
		GL_LINE_SMOOTH                    = 0x0B20,
		GL_LINE_WIDTH                     = 0x0B21,
		GL_LINE_WIDTH_RANGE               = 0x0B22,
		GL_LINE_WIDTH_GRANULARITY         = 0x0B23,
		GL_POLYGON_MODE                   = 0x0B40,
		GL_POLYGON_SMOOTH                 = 0x0B41,
		GL_CULL_FACE                      = 0x0B44,
		GL_CULL_FACE_MODE                 = 0x0B45,
		GL_FRONT_FACE                     = 0x0B46,
		GL_DEPTH_RANGE                    = 0x0B70,
		GL_DEPTH_TEST                     = 0x0B71,
		GL_DEPTH_WRITEMASK                = 0x0B72,
		GL_DEPTH_CLEAR_VALUE              = 0x0B73,
		GL_DEPTH_FUNC                     = 0x0B74,
		GL_STENCIL_TEST                   = 0x0B90,
		GL_STENCIL_CLEAR_VALUE            = 0x0B91,
		GL_STENCIL_FUNC                   = 0x0B92,
		GL_STENCIL_VALUE_MASK             = 0x0B93,
		GL_STENCIL_FAIL                   = 0x0B94,
		GL_STENCIL_PASS_DEPTH_FAIL        = 0x0B95,
		GL_STENCIL_PASS_DEPTH_PASS        = 0x0B96,
		GL_STENCIL_REF                    = 0x0B97,
		GL_STENCIL_WRITEMASK              = 0x0B98,
		GL_VIEWPORT                       = 0x0BA2,
		GL_DITHER                         = 0x0BD0,
		GL_BLEND_DST                      = 0x0BE0,
		GL_BLEND_SRC                      = 0x0BE1,
		GL_BLEND                          = 0x0BE2,
		GL_LOGIC_OP_MODE                  = 0x0BF0,
		GL_COLOR_LOGIC_OP                 = 0x0BF2,
		GL_DRAW_BUFFER                    = 0x0C01,
		GL_READ_BUFFER                    = 0x0C02,
		GL_SCISSOR_BOX                    = 0x0C10,
		GL_SCISSOR_TEST                   = 0x0C11,
		GL_COLOR_CLEAR_VALUE              = 0x0C22,
		GL_COLOR_WRITEMASK                = 0x0C23,
		GL_DOUBLEBUFFER                   = 0x0C32,
		GL_STEREO                         = 0x0C33,
		GL_LINE_SMOOTH_HINT               = 0x0C52,
		GL_POLYGON_SMOOTH_HINT            = 0x0C53,
		GL_UNPACK_SWAP_BYTES              = 0x0CF0,
		GL_UNPACK_LSB_FIRST               = 0x0CF1,
		GL_UNPACK_ROW_LENGTH              = 0x0CF2,
		GL_UNPACK_SKIP_ROWS               = 0x0CF3,
		GL_UNPACK_SKIP_PIXELS             = 0x0CF4,
		GL_UNPACK_ALIGNMENT               = 0x0CF5,
		GL_PACK_SWAP_BYTES                = 0x0D00,
		GL_PACK_LSB_FIRST                 = 0x0D01,
		GL_PACK_ROW_LENGTH                = 0x0D02,
		GL_PACK_SKIP_ROWS                 = 0x0D03,
		GL_PACK_SKIP_PIXELS               = 0x0D04,
		GL_PACK_ALIGNMENT                 = 0x0D05,
		GL_MAX_TEXTURE_SIZE               = 0x0D33,
		GL_MAX_VIEWPORT_DIMS              = 0x0D3A,
		GL_SUBPIXEL_BITS                  = 0x0D50,
		GL_TEXTURE_1D                     = 0x0DE0,
		GL_TEXTURE_2D                     = 0x0DE1,
		GL_POLYGON_OFFSET_UNITS           = 0x2A00,
		GL_POLYGON_OFFSET_POINT           = 0x2A01,
		GL_POLYGON_OFFSET_LINE            = 0x2A02,
		GL_POLYGON_OFFSET_FILL            = 0x8037,
		GL_POLYGON_OFFSET_FACTOR          = 0x8038,
		GL_TEXTURE_BINDING_1D             = 0x8068,
		GL_TEXTURE_BINDING_2D             = 0x8069,
		GL_TEXTURE_WIDTH                  = 0x1000,
		GL_TEXTURE_HEIGHT                 = 0x1001,
		GL_TEXTURE_INTERNAL_FORMAT        = 0x1003,
		GL_TEXTURE_BORDER_COLOR           = 0x1004,
		GL_TEXTURE_RED_SIZE               = 0x805C,
		GL_TEXTURE_GREEN_SIZE             = 0x805D,
		GL_TEXTURE_BLUE_SIZE              = 0x805E,
		GL_TEXTURE_ALPHA_SIZE             = 0x805F,
		GL_DONT_CARE                      = 0x1100,
		GL_FASTEST                        = 0x1101,
		GL_NICEST                         = 0x1102,
		GL_BYTE                           = 0x1400,
		GL_UNSIGNED_BYTE                  = 0x1401,
		GL_SHORT                          = 0x1402,
		GL_UNSIGNED_SHORT                 = 0x1403,
		GL_INT                            = 0x1404,
		GL_UNSIGNED_INT                   = 0x1405,
		GL_FLOAT                          = 0x1406,
		GL_DOUBLE                         = 0x140A,
		GL_STACK_OVERFLOW                 = 0x0503,
		GL_STACK_UNDERFLOW                = 0x0504,
		GL_CLEAR                          = 0x1500,
		GL_AND                            = 0x1501,
		GL_AND_REVERSE                    = 0x1502,
		GL_COPY                           = 0x1503,
		GL_AND_INVERTED                   = 0x1504,
		GL_NOOP                           = 0x1505,
		GL_XOR                            = 0x1506,
		GL_OR                             = 0x1507,
		GL_NOR                            = 0x1508,
		GL_EQUIV                          = 0x1509,
		GL_INVERT                         = 0x150A,
		GL_OR_REVERSE                     = 0x150B,
		GL_COPY_INVERTED                  = 0x150C,
		GL_OR_INVERTED                    = 0x150D,
		GL_NAND                           = 0x150E,
		GL_SET                            = 0x150F,
		GL_TEXTURE                        = 0x1702,
		GL_COLOR                          = 0x1800,
		GL_DEPTH                          = 0x1801,
		GL_STENCIL                        = 0x1802,
		GL_STENCIL_INDEX                  = 0x1901,
		GL_DEPTH_COMPONENT                = 0x1902,
		GL_RED                            = 0x1903,
		GL_GREEN                          = 0x1904,
		GL_BLUE                           = 0x1905,
		GL_ALPHA                          = 0x1906,
		GL_RGB                            = 0x1907,
		GL_RGBA                           = 0x1908,
		GL_POINT                          = 0x1B00,
		GL_LINE                           = 0x1B01,
		GL_FILL                           = 0x1B02,
		GL_KEEP                           = 0x1E00,
		GL_REPLACE                        = 0x1E01,
		GL_INCR                           = 0x1E02,
		GL_DECR                           = 0x1E03,
		GL_VENDOR                         = 0x1F00,
		GL_RENDERER                       = 0x1F01,
		GL_VERSION                        = 0x1F02,
		GL_EXTENSIONS                     = 0x1F03,
		GL_NEAREST                        = 0x2600,
		GL_LINEAR                         = 0x2601,
		GL_NEAREST_MIPMAP_NEAREST         = 0x2700,
		GL_LINEAR_MIPMAP_NEAREST          = 0x2701,
		GL_NEAREST_MIPMAP_LINEAR          = 0x2702,
		GL_LINEAR_MIPMAP_LINEAR           = 0x2703,
		GL_TEXTURE_MAG_FILTER             = 0x2800,
		GL_TEXTURE_MIN_FILTER             = 0x2801,
		GL_TEXTURE_WRAP_S                 = 0x2802,
		GL_TEXTURE_WRAP_T                 = 0x2803,
		GL_PROXY_TEXTURE_1D               = 0x8063,
		GL_PROXY_TEXTURE_2D               = 0x8064,
		GL_REPEAT                         = 0x2901,
		GL_R3_G3_B2                       = 0x2A10,
		GL_RGB4                           = 0x804F,
		GL_RGB5                           = 0x8050,
		GL_RGB8                           = 0x8051,
		GL_RGB10                          = 0x8052,
		GL_RGB12                          = 0x8053,
		GL_RGB16                          = 0x8054,
		GL_RGBA2                          = 0x8055,
		GL_RGBA4                          = 0x8056,
		GL_RGB5_A1                        = 0x8057,
		GL_RGBA8                          = 0x8058,
		GL_RGB10_A2                       = 0x8059,
		GL_RGBA12                         = 0x805A,
		GL_RGBA16                         = 0x805B,
		GL_VERTEX_ARRAY                   = 0x8074,
	};
	
	//	VERSION_1_1
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

	enum VERSION_1_2_TOKENS : GLenum{
		GL_UNSIGNED_BYTE_3_3_2            = 0x8032,
		GL_UNSIGNED_SHORT_4_4_4_4         = 0x8033,
		GL_UNSIGNED_SHORT_5_5_5_1         = 0x8034,
		GL_UNSIGNED_INT_8_8_8_8           = 0x8035,
		GL_UNSIGNED_INT_10_10_10_2        = 0x8036,
		GL_TEXTURE_BINDING_3D             = 0x806A,
		GL_PACK_SKIP_IMAGES               = 0x806B,
		GL_PACK_IMAGE_HEIGHT              = 0x806C,
		GL_UNPACK_SKIP_IMAGES             = 0x806D,
		GL_UNPACK_IMAGE_HEIGHT            = 0x806E,
		GL_TEXTURE_3D                     = 0x806F,
		GL_PROXY_TEXTURE_3D               = 0x8070,
		GL_TEXTURE_DEPTH                  = 0x8071,
		GL_TEXTURE_WRAP_R                 = 0x8072,
		GL_MAX_3D_TEXTURE_SIZE            = 0x8073,
		GL_UNSIGNED_BYTE_2_3_3_REV        = 0x8362,
		GL_UNSIGNED_SHORT_5_6_5           = 0x8363,
		GL_UNSIGNED_SHORT_5_6_5_REV       = 0x8364,
		GL_UNSIGNED_SHORT_4_4_4_4_REV     = 0x8365,
		GL_UNSIGNED_SHORT_1_5_5_5_REV     = 0x8366,
		GL_UNSIGNED_INT_8_8_8_8_REV       = 0x8367,
		GL_UNSIGNED_INT_2_10_10_10_REV    = 0x8368,
		GL_BGR                            = 0x80E0,
		GL_BGRA                           = 0x80E1,
		GL_MAX_ELEMENTS_VERTICES          = 0x80E8,
		GL_MAX_ELEMENTS_INDICES           = 0x80E9,
		GL_CLAMP_TO_EDGE                  = 0x812F,
		GL_TEXTURE_MIN_LOD                = 0x813A,
		GL_TEXTURE_MAX_LOD                = 0x813B,
		GL_TEXTURE_BASE_LEVEL             = 0x813C,
		GL_TEXTURE_MAX_LEVEL              = 0x813D,
		GL_SMOOTH_POINT_SIZE_RANGE        = 0x0B12,
		GL_SMOOTH_POINT_SIZE_GRANULARITY  = 0x0B13,
		GL_SMOOTH_LINE_WIDTH_RANGE        = 0x0B22,
		GL_SMOOTH_LINE_WIDTH_GRANULARITY  = 0x0B23,
		GL_ALIASED_LINE_WIDTH_RANGE       = 0x846E,
	};

	//	VERSION_1_2
	extern void glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
	extern void glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
	extern void glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
	extern void glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

	enum VERSION_1_3_TOKENS : GLenum{
		GL_TEXTURE0                       = 0x84C0,
		GL_TEXTURE1                       = 0x84C1,
		GL_TEXTURE2                       = 0x84C2,
		GL_TEXTURE3                       = 0x84C3,
		GL_TEXTURE4                       = 0x84C4,
		GL_TEXTURE5                       = 0x84C5,
		GL_TEXTURE6                       = 0x84C6,
		GL_TEXTURE7                       = 0x84C7,
		GL_TEXTURE8                       = 0x84C8,
		GL_TEXTURE9                       = 0x84C9,
		GL_TEXTURE10                      = 0x84CA,
		GL_TEXTURE11                      = 0x84CB,
		GL_TEXTURE12                      = 0x84CC,
		GL_TEXTURE13                      = 0x84CD,
		GL_TEXTURE14                      = 0x84CE,
		GL_TEXTURE15                      = 0x84CF,
		GL_TEXTURE16                      = 0x84D0,
		GL_TEXTURE17                      = 0x84D1,
		GL_TEXTURE18                      = 0x84D2,
		GL_TEXTURE19                      = 0x84D3,
		GL_TEXTURE20                      = 0x84D4,
		GL_TEXTURE21                      = 0x84D5,
		GL_TEXTURE22                      = 0x84D6,
		GL_TEXTURE23                      = 0x84D7,
		GL_TEXTURE24                      = 0x84D8,
		GL_TEXTURE25                      = 0x84D9,
		GL_TEXTURE26                      = 0x84DA,
		GL_TEXTURE27                      = 0x84DB,
		GL_TEXTURE28                      = 0x84DC,
		GL_TEXTURE29                      = 0x84DD,
		GL_TEXTURE30                      = 0x84DE,
		GL_TEXTURE31                      = 0x84DF,
		GL_ACTIVE_TEXTURE                 = 0x84E0,
		GL_MULTISAMPLE                    = 0x809D,
		GL_SAMPLE_ALPHA_TO_COVERAGE       = 0x809E,
		GL_SAMPLE_ALPHA_TO_ONE            = 0x809F,
		GL_SAMPLE_COVERAGE                = 0x80A0,
		GL_SAMPLE_BUFFERS                 = 0x80A8,
		GL_SAMPLES                        = 0x80A9,
		GL_SAMPLE_COVERAGE_VALUE          = 0x80AA,
		GL_SAMPLE_COVERAGE_INVERT         = 0x80AB,
		GL_TEXTURE_CUBE_MAP               = 0x8513,
		GL_TEXTURE_BINDING_CUBE_MAP       = 0x8514,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X    = 0x8515,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X    = 0x8516,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y    = 0x8517,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    = 0x8518,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z    = 0x8519,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    = 0x851A,
		GL_PROXY_TEXTURE_CUBE_MAP         = 0x851B,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE      = 0x851C,
		GL_COMPRESSED_RGB                 = 0x84ED,
		GL_COMPRESSED_RGBA                = 0x84EE,
		GL_TEXTURE_COMPRESSION_HINT       = 0x84EF,
		GL_TEXTURE_COMPRESSED_IMAGE_SIZE  = 0x86A0,
		GL_TEXTURE_COMPRESSED             = 0x86A1,
		GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2,
		GL_COMPRESSED_TEXTURE_FORMATS     = 0x86A3,
		GL_CLAMP_TO_BORDER                = 0x812D,
	};

	//	VERSION_1_3
	extern void glActiveTexture (GLenum texture);
	extern void glSampleCoverage (GLfloat value, GLboolean invert);
	extern void glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
	extern void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
	extern void glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
	extern void glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
	extern void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
	extern void glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
	extern void glGetCompressedTexImage (GLenum target, GLint level, GLvoid *img);

	enum VERSION_1_4_TOKENS : GLenum{
		GL_BLEND_DST_RGB                  = 0x80C8,
		GL_BLEND_SRC_RGB                  = 0x80C9,
		GL_BLEND_DST_ALPHA                = 0x80CA,
		GL_BLEND_SRC_ALPHA                = 0x80CB,
		GL_POINT_FADE_THRESHOLD_SIZE      = 0x8128,
		GL_DEPTH_COMPONENT16              = 0x81A5,
		GL_DEPTH_COMPONENT24              = 0x81A6,
		GL_DEPTH_COMPONENT32              = 0x81A7,
		GL_MIRRORED_REPEAT                = 0x8370,
		GL_MAX_TEXTURE_LOD_BIAS           = 0x84FD,
		GL_TEXTURE_LOD_BIAS               = 0x8501,
		GL_INCR_WRAP                      = 0x8507,
		GL_DECR_WRAP                      = 0x8508,
		GL_TEXTURE_DEPTH_SIZE             = 0x884A,
		GL_TEXTURE_COMPARE_MODE           = 0x884C,
		GL_TEXTURE_COMPARE_FUNC           = 0x884D,
		GL_FUNC_ADD                       = 0x8006,
		GL_FUNC_SUBTRACT                  = 0x800A,
		GL_FUNC_REVERSE_SUBTRACT          = 0x800B,
		GL_MIN                            = 0x8007,
		GL_MAX                            = 0x8008,
		GL_CONSTANT_COLOR                 = 0x8001,
		GL_ONE_MINUS_CONSTANT_COLOR       = 0x8002,
		GL_CONSTANT_ALPHA                 = 0x8003,
		GL_ONE_MINUS_CONSTANT_ALPHA       = 0x8004,
	};

	//	VERSION_1_4
	extern void  glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
	extern void  glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
	extern void  glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount);
	extern void  glPointParameterf (GLenum pname, GLfloat param);
	extern void  glPointParameterfv (GLenum pname, const GLfloat *params);
	extern void  glPointParameteri (GLenum pname, GLint param);
	extern void  glPointParameteriv (GLenum pname, const GLint *params);
	extern void  glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	extern void  glBlendEquation (GLenum mode);
}

//=========================================
//	OPENGL 1.5
//=========================================

namespace GL{
	enum VERSION_1_5_TOKENS : GLenum{
		GL_BUFFER_SIZE                    = 0x8764,
		GL_BUFFER_USAGE                   = 0x8765,
		GL_QUERY_COUNTER_BITS             = 0x8864,
		GL_CURRENT_QUERY                  = 0x8865,
		GL_QUERY_RESULT                   = 0x8866,
		GL_QUERY_RESULT_AVAILABLE         = 0x8867,
		GL_ARRAY_BUFFER                   = 0x8892,
		GL_ELEMENT_ARRAY_BUFFER           = 0x8893,
		GL_ARRAY_BUFFER_BINDING           = 0x8894,
		GL_ELEMENT_ARRAY_BUFFER_BINDING   = 0x8895,
		GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F,
		GL_READ_ONLY                      = 0x88B8,
		GL_WRITE_ONLY                     = 0x88B9,
		GL_READ_WRITE                     = 0x88BA,
		GL_BUFFER_ACCESS                  = 0x88BB,
		GL_BUFFER_MAPPED                  = 0x88BC,
		GL_BUFFER_MAP_POINTER             = 0x88BD,
		GL_STREAM_DRAW                    = 0x88E0,
		GL_STREAM_READ                    = 0x88E1,
		GL_STREAM_COPY                    = 0x88E2,
		GL_STATIC_DRAW                    = 0x88E4,
		GL_STATIC_READ                    = 0x88E5,
		GL_STATIC_COPY                    = 0x88E6,
		GL_DYNAMIC_DRAW                   = 0x88E8,
		GL_DYNAMIC_READ                   = 0x88E9,
		GL_DYNAMIC_COPY                   = 0x88EA,
		GL_SAMPLES_PASSED                 = 0x8914,
		GL_SRC1_ALPHA                     = 0x8589,
	};

	//	VERSION_1_5
	extern void glGenQueries (GLsizei n, GLuint *ids);
	extern void glDeleteQueries (GLsizei n, const GLuint *ids);
	extern GLboolean glIsQuery (GLuint id);
	extern void glBeginQuery (GLenum target, GLuint id);
	extern void glEndQuery (GLenum target);
	extern void glGetQueryiv (GLenum target, GLenum pname, GLint *params);
	extern void glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params);
	extern void glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
	extern void glBindBuffer (GLenum target, GLuint buffer);
	extern void glDeleteBuffers (GLsizei n, const GLuint *buffers);
	extern void glGenBuffers (GLsizei n, GLuint *buffers);
	extern GLboolean glIsBuffer (GLuint buffer);
	extern void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
	extern void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
	extern void glGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data);
	extern void *glMapBuffer (GLenum target, GLenum access);
	extern GLboolean glUnmapBuffer (GLenum target);
	extern void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
	extern void glGetBufferPointerv (GLenum target, GLenum pname, GLvoid **params);

	//	Pre 2.0 mipmap generation
	enum CORE_GEN_MIPMAP_TOKENS : GLenum{
		GL_GENERATE_MIPMAP                = 0x8191,
		GL_GENERATE_MIPMAP_HINT           = 0x8192,
	};
}

//==============================================
//	CG headers and libs
//==============================================

#define CGGL_NO_OPENGL

#include <Cg\cg.h>
#include <Cg\cgGL.h>

#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")

//===============================================
//	Loading
//===============================================
namespace GL{
	namespace Loader{
		enum class Version{
			V_1_2,
			V_1_3,
			V_1_4,
			V_1_5,
		};

		enum class Extension{
			VertexBufferObjects,
		};

		extern const bool	IsSupported(const Extension uExtension);
		extern const bool	Load(const Version uVersion);
		extern const bool	Load(const Extension uExtension);
	}

	extern void	ReportGLError(GLenum uError, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
}