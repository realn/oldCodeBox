#pragma once


//===========================================
//	TYPES
//===========================================

typedef unsigned int	GLenum;
typedef float			GLfloat;
typedef int				GLint;
typedef int				GLsizei;
typedef void			GLvoid;
typedef unsigned int	GLbitfield;
typedef double			GLdouble;
typedef unsigned int	GLuint;
typedef unsigned char	GLboolean;
typedef unsigned char	GLubyte;

typedef float			GLclampf;
typedef double			GLclampd;

typedef _w64 int		GLsizeiptr;
typedef _w64 int		GLintptr;

typedef char			GLchar;
typedef short			GLshort;
typedef signed char		GLbyte;
typedef unsigned short	GLushort;

typedef unsigned short	GLhalf;

typedef struct __GLsync *GLsync;
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
typedef uint64_t GLuint64;
typedef int64_t GLint64;
