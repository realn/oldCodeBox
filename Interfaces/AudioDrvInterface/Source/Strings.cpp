#include "../Include/AudioDriver.h"

namespace CB{
	namespace String{
		const CString	ToString(const Audio::BufferFormat uFormat){
			switch (uFormat)
			{
			case Audio::BufferFormat::Mono8Bit:		return L"Mono 8 Bit";
			case Audio::BufferFormat::Mono16Bit:	return L"Mono 16 Bit";
			case Audio::BufferFormat::Stereo8Bit:	return L"Stereo 8 Bit";
			case Audio::BufferFormat::Stereo16Bit:	return L"Stereo 16 Bit";
			default:
				return String::ToString((uint32)uFormat);
			}
		}
		const CString	ToString(const Audio::ChannelConfig uConfig){
			switch (uConfig)
			{
			case Audio::ChannelConfig::Mono:	return L"Mono";
			case Audio::ChannelConfig::Stereo:	return L"Stereo";
			default:
				return String::ToString((uint32)uConfig);
			}
		}

		const CString	ToString(const Audio::SampleType uType){
			switch (uType)
			{
			case Audio::SampleType::Byte:	return L"Byte";
			case Audio::SampleType::Short:	return L"Short";
			default:
				return String::ToString((uint32)uType);
			}
		}

		const CString	ToString(const Audio::SourceType uType){
			switch (uType)
			{
			case Audio::SourceType::None:		return L"None";
			case Audio::SourceType::Static:		return L"Static";
			case Audio::SourceType::Streaming:	return L"Streaming";
			default:
				return String::ToString((uint32)uType);
			}
		}
	}
}