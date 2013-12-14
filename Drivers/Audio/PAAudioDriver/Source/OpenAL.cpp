#include "../Internal/OpenAL.h"
#include <Exception.h>

namespace PROC{
	LPALBUFFERSAMPLESSOFT alBufferSamplesSOFT = 0;
	LPALBUFFERSUBSAMPLESSOFT alBufferSubSamplesSOFT = 0;
	LPALGETBUFFERSAMPLESSOFT alGetBufferSamplesSOFT = 0;
	LPALISBUFFERFORMATSUPPORTEDSOFT alIsBufferFormatSupportedSOFT = 0;
}

void alBufferSamplesSOFT(ALuint buffer, ALuint samplerate, ALenum internalformat, ALsizei samples, ALenum channels, ALenum type, const ALvoid *data){
	PROC::alBufferSamplesSOFT(buffer, samplerate, internalformat, samples, channels, type, data);
}

void alBufferSubSamplesSOFT(ALuint buffer, ALsizei offset, ALsizei samples, ALenum channels, ALenum type, const ALvoid *data){
	PROC::alBufferSubSamplesSOFT(buffer, offset, samples, channels, type, data);
}

void alGetBufferSamplesSOFT(ALuint buffer, ALsizei offset, ALsizei samples, ALenum channels, ALenum type, ALvoid *data){
	PROC::alGetBufferSamplesSOFT(buffer, offset, samples, channels, type, data);
}

ALboolean alIsBufferFormatSupportedSOFT(ALenum format){
	return PROC::alIsBufferFormatSupportedSOFT(format);
}

template<typename _Type>
_Type	GetExtProc(ALCdevice* pDevice, char* szProc){
	_Type pProc = reinterpret_cast<_Type>(alcGetProcAddress(pDevice, szProc));
	if(pProc == 0){
		throw CB::Exception::CNullPointerException(L"pProc", L"Could not load proc.", CR_INFO());
	}
	return pProc;
}

namespace AL{
#define AL_LOAD(A,B)	PROC::B = GetExtProc<A>(pDevice, #B)
	void	LoadExtensions(ALCdevice* pDevice){
		AL_LOAD(LPALBUFFERSAMPLESSOFT, alBufferSamplesSOFT);
		AL_LOAD(LPALBUFFERSUBSAMPLESSOFT, alBufferSubSamplesSOFT);
		AL_LOAD(LPALGETBUFFERSAMPLESSOFT, alGetBufferSamplesSOFT);
		AL_LOAD(LPALISBUFFERFORMATSUPPORTEDSOFT, alIsBufferFormatSupportedSOFT);		
	}
#undef AL_LOAD
}