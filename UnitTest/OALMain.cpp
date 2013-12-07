#include "../Ext/include/als/al.h"
#include "../Ext/include/als/alc.h"

#pragma comment(lib, "../Ext/lib/OpenAL32.lib")

int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* szCmdLine, int nShowCmd){

	auto szTemp = alcGetString(0, ALC_DEVICE_SPECIFIER);

	ALCdevice* pDevice = alcOpenDevice(szTemp);

	alcCloseDevice(pDevice);

	return 0;
}