#include "../Internal/Utils.h"

namespace CB{
	const ALenum	ToBufferFormat(const Audio::BufferFormat uFormat){
		switch (uFormat)
		{
		case Audio::BufferFormat::Mono8Bit:		return AL_FORMAT_MONO8;
		case Audio::BufferFormat::Mono16Bit:	return AL_FORMAT_MONO16;
		case Audio::BufferFormat::Stereo8Bit:	return AL_FORMAT_STEREO8;
		case Audio::BufferFormat::Stereo16Bit:	return AL_FORMAT_STEREO16;
		default:
			break;
		}
	}
}