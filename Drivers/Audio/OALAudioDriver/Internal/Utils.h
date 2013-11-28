#pragma once

#include <Types.h>
#include <AudioDriver.h>
#include "OpenAL.h"

namespace CB{
	namespace Utils{
		extern const ALenum	ToBufferFormat(const Audio::BufferFormat uFormat);
		extern const ALenum ToChannelFormat(const Audio::BufferFormat uFormat);
		extern const ALenum	ToSampleType(const Audio::SampleType uType);
	}
}