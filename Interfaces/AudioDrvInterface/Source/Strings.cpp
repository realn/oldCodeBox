#include "../Include/AudioDriver.h"

namespace CB{
	namespace String{
		const CString	ToString(const Audio::ChannelFormat uFormat){
			switch (uFormat)
			{
			case Audio::ChannelFormat::Mono:		return L"Mono";
			case Audio::ChannelFormat::Stereo:		return L"Stereo";
			default:
				return String::ToString((uint32)uFormat);
			}
		}
		const CString	ToString(const Audio::SourceState uState){
			switch (uState)
			{
			case Audio::SourceState::None:		return L"None";
			case Audio::SourceState::Paused:	return L"Paused";
			case Audio::SourceState::Playing:	return L"Playing";
			case Audio::SourceState::Stopped:	return L"Stopped";
			default:
				return String::ToString((uint32)uState);
			}
		}

		const CString	ToString(const Audio::SampleType uType){
			switch (uType)
			{
			case Audio::SampleType::S8Bit:	return L"Signed 8 Bit";
			case Audio::SampleType::S16Bit:	return L"Signed 16 Bit";
			default:
				return String::ToString((uint32)uType);
			}
		}

		const CString	ToString(const Audio::SourceType uType){
			switch (uType)
			{
			case Audio::SourceType::Static:		return L"Static";
			case Audio::SourceType::Streaming:	return L"Streaming";
			default:
				return String::ToString((uint32)uType);
			}
		}

		const CString	ToString(const Audio::DistanceModel uModel){
			switch (uModel)
			{
			case Audio::DistanceModel::None:			return L"None";
			case Audio::DistanceModel::Linear:			return L"Linear";
			case Audio::DistanceModel::LinearClamped:	return L"Linear Clamped";
			case Audio::DistanceModel::InverseLinear:	return L"Inverse Linear";
			case Audio::DistanceModel::InverseLinearClamped:	return L"Inverse Linear Clamped";
			case Audio::DistanceModel::Exponent:		return L"Exponent";
			case Audio::DistanceModel::ExponentClamped:	return L"Exponent Clamped";
			default:
				return String::ToString((uint32)uModel);
			}
		}
	}
}