#pragma once

#include "Macros.h"
#include <AudioDriver.h>

extern "C" PAAUDIODRIVER_API CB::Audio::IManager*	CreateAudioManager(CB::Audio::IDriver* pDriver);