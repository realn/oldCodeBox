#include "../Internal/Buffer.h"
#include "../Internal/Utils.h"

namespace CB{
	COALBuffer::COALBuffer(CRefPtr<COALDevice> pDevice, const Audio::BufferFormat uFormat, const uint32 uSampleRate, const uint32 uSamples) :
		Manage::IManagedObject<COALDevice, COALBuffer>(pDevice),
		m_uFormat(uFormat),
		m_uSampleRate(uSampleRate),
		m_uSamples(uSamples),
		m_uBuffer(0)
	{
		alGenBuffers(1, &this->m_uBuffer);

		ALenum uALFormat = Utils::ToBufferFormat(this->m_uFormat);
		ALenum uALChannelConfig = Utils::ToChannelFormat(this->m_uFormat);

		alBufferSamplesSOFT(this->m_uBuffer, this->m_uSampleRate, uALFormat, this->m_uSamples, uALChannelConfig, AL_UNSIGNED_BYTE_SOFT, 0);
	}

	COALBuffer::~COALBuffer(){
		if(this->m_uBuffer != 0 && alIsBuffer(this->m_uBuffer)){
			alDeleteBuffers(1, &this->m_uBuffer);
			this->m_uBuffer = 0;
		}
	}

	const ALuint	COALBuffer::GetBufferID() const{
		return this->m_uBuffer;
	}


	const uint32	COALBuffer::GetApiId() const{
		return g_uApiId;
	}

	const uint32		COALBuffer::GetSamples() const{
		return this->m_uSamples;
	}

	const uint32		COALBuffer::GetSampleRate() const{
		return this->m_uSampleRate;
	}

	const Audio::BufferFormat	COALBuffer::GetFormat() const{
		return this->m_uFormat;
	}

	void	COALBuffer::LoadData(const Audio::SampleType uType, const uint32 uSamples, const void* pData){
		this->LoadSubData(uType, 0, uSamples, pData);
	}

	void	COALBuffer::LoadSubData(const Audio::SampleType uType, const uint32 uOffset, const uint32 uSamples, const void* pData){
		auto uChannels = Utils::ToChannelFormat(this->m_uFormat);
		auto uSampleType = Utils::ToSampleType(uType);

		alBufferSubSamplesSOFT(this->m_uBuffer, uOffset, uSamples, uChannels, uSampleType, pData);
	}

}