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

		const ALenum	ToDistanceModel(const Audio::DistanceModel uModel){
			switch (uModel){
			case Audio::DistanceModel::None:			return AL_NONE;
			case Audio::DistanceModel::Linear:			return AL_LINEAR_DISTANCE;
			case Audio::DistanceModel::LinearClamped:	return AL_LINEAR_DISTANCE_CLAMPED;
			case Audio::DistanceModel::InverseLinear:	return AL_INVERSE_DISTANCE;
			case Audio::DistanceModel::InverseLinearClamped:	return AL_INVERSE_DISTANCE_CLAMPED;
			case Audio::DistanceModel::Exponent:		return AL_EXPONENT_DISTANCE;
			case Audio::DistanceModel::ExponentClamped:	return AL_EXPONENT_DISTANCE_CLAMPED;
			default:
				throw Exception::CInvalidArgumentException(L"uModel", String::ToString(uModel),
					L"Invalid audio distance model.", CR_INFO());
			}
		}

		const Audio::DistanceModel	ToDistanceModel(const ALenum uModel){
			switch (uModel){
			case AL_NONE:						return Audio::DistanceModel::None;
			case AL_LINEAR_DISTANCE:			return Audio::DistanceModel::Linear;
			case AL_LINEAR_DISTANCE_CLAMPED:	return Audio::DistanceModel::LinearClamped;
			case AL_INVERSE_DISTANCE:			return Audio::DistanceModel::InverseLinear;
			case AL_INVERSE_DISTANCE_CLAMPED:	return Audio::DistanceModel::InverseLinearClamped;
			case AL_EXPONENT_DISTANCE:			return Audio::DistanceModel::Exponent;
			case AL_EXPONENT_DISTANCE_CLAMPED:	return Audio::DistanceModel::ExponentClamped;
			default:
				throw Exception::CInvalidArgumentException(L"uModel", String::ToHexString(uModel),
					L"Invalid audio distance model (OpenAL).", CR_INFO());
			}
		}
	}
}