#pragma once

#include <Types.h>
#include <AudioDriver.h>

#include "OpenAL.h"

namespace CB{
	namespace Utils{
		extern const ALenum	ToChannelFormat(const Audio::ChannelFormat uFormat);
		extern const ALenum	ToSampleType(const Audio::SampleType uType);		
		extern const ALenum	ToBufferFormat(const Audio::ChannelFormat uFormat, const Audio::SampleType uType);
	}
}