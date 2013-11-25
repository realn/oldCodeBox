#pragma once

#include "Macros.h"
#include <AudioDriver.h>

extern "C" OALAUDIODRIVER_API CB::Audio::IManager*	CreateAudioManager(CB::Audio::IDriver* pDriver);