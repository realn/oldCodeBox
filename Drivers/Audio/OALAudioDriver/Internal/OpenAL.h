#pragma once

#include <CBString.h>

#ifndef AL_ALEXT_PROTOTYPES
#define AL_ALEXT_PROTOTYPES
#endif

#include <als\al.h>
#include <als\alc.h>
#include <als\alext.h>

#pragma comment(lib, "OpenAL32.lib")

//extern void alBufferSamplesSOFT(ALuint buffer, ALuint samplerate, ALenum internalformat, ALsizei samples, ALenum channels, ALenum type, const ALvoid *data);
//extern void alBufferSubSamplesSOFT(ALuint buffer, ALsizei offset, ALsizei samples, ALenum channels, ALenum type, const ALvoid *data);
//extern void alGetBufferSamplesSOFT(ALuint buffer, ALsizei offset, ALsizei samples, ALenum channels, ALenum type, ALvoid *data);
//extern ALboolean alIsBufferFormatSupportedSOFT(ALenum format);
//
namespace AL{
//	extern void LoadExtensions(ALCdevice* pDevice);
	extern void ReportALBindMismatch(const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
	extern void ReportALError(const ALenum uError, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
}

#define CR_ALCHECK()		{auto ___ALError = alGetError(); if(___ALError != AL_NO_ERROR){ AL::ReportALError(___ALError, CR_INFO()); }}
#define CR_ALBINDCHECK(CTX)	if(alcGetCurrentContext() != CTX){ AL::ReportALBindMismatch(CR_INFO()); }