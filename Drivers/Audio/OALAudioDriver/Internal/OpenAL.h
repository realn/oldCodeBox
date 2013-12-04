#pragma once

#ifndef AL_ALEXT_PROTOTYPES
//#define AL_ALEXT_PROTOTYPES
#endif

#include <als\al.h>
#include <als\alc.h>
#include <als\alext.h>

#pragma comment(lib, "OpenAL32.lib")

extern void alBufferSamplesSOFT(ALuint buffer, ALuint samplerate, ALenum internalformat, ALsizei samples, ALenum channels, ALenum type, const ALvoid *data);
extern void alBufferSubSamplesSOFT(ALuint buffer, ALsizei offset, ALsizei samples, ALenum channels, ALenum type, const ALvoid *data);
extern void alGetBufferSamplesSOFT(ALuint buffer, ALsizei offset, ALsizei samples, ALenum channels, ALenum type, ALvoid *data);
extern ALboolean alIsBufferFormatSupportedSOFT(ALenum format);

namespace AL{
	extern void LoadExtensions(ALCdevice* pDevice);
}