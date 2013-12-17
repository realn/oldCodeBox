#include "../Internal/Utils.h"

namespace CB{
	namespace Utils{
		const ALenum	ToChannelFormat(const Audio::ChannelFormat uFormat){
			switch (uFormat)
			{
			case Audio::ChannelFormat::Mono:	return AL_MONO_SOFT;
			case Audio::ChannelFormat::Stereo:	return AL_STEREO_SOFT;
			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Invalid audio channel format.", CR_INFO());
			}
		}

		const ALenum	ToSampleType(const Audio::SampleType uType){
			switch (uType)
			{
			case Audio::SampleType::S8Bit:	return AL_BYTE_SOFT;
			case Audio::SampleType::S16Bit:	return AL_SHORT_SOFT;
			default:
				throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
					L"Invalid audio sample type.", CR_INFO());
			}
		}

		const ALenum	ToBufferFormat(const Audio::ChannelFormat uFormat, const Audio::SampleType uType){
			switch (uFormat)
			{
			case Audio::ChannelFormat::Mono:
				switch (uType)
				{
				case Audio::SampleType::S8Bit:	return AL_MONO8_SOFT;
				case Audio::SampleType::S16Bit:	return AL_MONO16_SOFT;
				default:
					throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
						L"Invalid audio sample type for mono channel.", CR_INFO());
				};

			case Audio::ChannelFormat::Stereo:
				switch (uType)
				{
				case Audio::SampleType::S8Bit:	return AL_STEREO8_SOFT;
				case Audio::SampleType::S16Bit:	return AL_STEREO16_SOFT;
				default:
					throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
						L"Invalid audio sample type for stereo channels.", CR_INFO());
				}
			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Invalid audio channel format.", CR_INFO());
			}
		}
	}
}