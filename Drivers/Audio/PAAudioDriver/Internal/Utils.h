#pragma once

#include <Types.h>
#include <AudioDriver.h>

#include <portaudio\portaudio.h>

namespace CB{
	namespace Utils{
		extern const CString	ToErrorString(const PaError uError);
	}
}