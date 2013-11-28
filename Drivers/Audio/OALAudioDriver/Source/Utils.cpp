#include "../Internal/Utils.h"

namespace CB{
	namespace Utils{
		const ALenum	ToBufferFormat(const Audio::BufferFormat uFormat){
			switch (uFormat)
			{
			case Audio::BufferFormat::Mono8Bit:		return AL_FORMAT_MONO8;
			case Audio::BufferFormat::Mono16Bit:	return AL_FORMAT_MONO16;
			case Audio::BufferFormat::Stereo8Bit:	return AL_FORMAT_STEREO8;
			case Audio::BufferFormat::Stereo16Bit:	return AL_FORMAT_STEREO16;
			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Invalid buffer format.", CR_INFO());
			}
		}

		const ALenum ToChannelFormat(const Audio::BufferFormat uFormat){
			switch (uFormat)
			{
			case Audio::BufferFormat::Mono8Bit:		return AL_MONO_SOFT;
			case Audio::BufferFormat::Mono16Bit:	return AL_MONO_SOFT;
			case Audio::BufferFormat::Stereo8Bit:	return AL_STEREO_SOFT;
			case Audio::BufferFormat::Stereo16Bit:	return AL_STEREO_SOFT;
			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Invalid buffer format.", CR_INFO());
			}
		}

		const ALenum	ToSampleType(const Audio::SampleType uType){
			switch (uType)
			{
			case Audio::SampleType::Byte:	return AL_BYTE_SOFT;
			case Audio::SampleType::Short:	return AL_SHORT_SOFT;
			default:
				throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
					L"Invalid sample type.", CR_INFO());
			}
		}
	}
}