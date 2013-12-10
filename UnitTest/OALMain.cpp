#include <dsound.h>

#pragma comment(lib, "Lib\\x86\\dsound.lib")

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* szCmdLine, int nShowCmd){
	CoInitializeEx(0, COINIT_MULTITHREADED);

	IDirectSound8* pSound = 0;
	auto hResult = DirectSoundCreate8(0, &pSound, 0);
	if(hResult != S_OK){
		return -1;
	}

	pSound->Release();

	CoUninitialize();
	return 0;
}