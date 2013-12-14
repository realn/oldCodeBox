#include "../Include/PAAudioDriver.h"
#include "../Internal/Manager.h"

CB::Audio::IManager*	CreateAudioManager(CB::Audio::IDriver* pDriver){
	return new CB::CPAManager(pDriver);
}