#include "../Internal/Buffer.h"
#include "../Internal/Utils.h"
#include "../Internal/OpenAL.h"

namespace CB{
	COALBuffer::COALBuffer(CRefPtr<COALDevice> pDevice, const Audio::ChannelFormat uFormat, const Audio::SampleType uType, const uint32 uSampleRate, const uint32 uSamples) :
		Manage::IManagedObject<COALDevice, COALBuffer>(pDevice),
		m_uFormat(uFormat),
		m_uType(uType),
		m_uSampleRate(uSampleRate),
		m_uSamples(uSamples),
		m_uBuffer(0)
	{
		alGenBuffers(1, &this->m_uBuffer);	CR_ALCHECK();

		ALenum uALFormat = Utils::ToBufferFormat(this->m_uFormat, this->m_uType);
		ALenum uALChannelFormat = Utils::ToChannelFormat(this->m_uFormat);
		ALenum uALSampleType = Utils::ToSampleType(this->m_uType);

		//alBufferData(this->m_uBuffer, uALFormat, 0, uSamples, uSampleRate);
		alBufferSamplesSOFT(this->m_uBuffer, this->m_uSampleRate, uALFormat, this->m_uSamples, uALChannelFormat, uALSampleType, 0);	CR_ALCHECK();
	}

	COALBuffer::~COALBuffer(){
		if(this->m_uBuffer != 0 && alIsBuffer(this->m_uBuffer)){
			CR_ALBINDCHECK(this->m_pParent->GetContext());
			alDeleteBuffers(1, &this->m_uBuffer);	CR_ALCHECK();
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

	const Audio::ChannelFormat	COALBuffer::GetFormat() const{
		return this->m_uFormat;
	}

	const Audio::SampleType	COALBuffer::GetSampleType() const{
		return this->m_uType;
	}

	void	COALBuffer::LoadData(const uint32 uSamples, const void* pData){
		this->LoadSubData(0, uSamples, pData);
	}

	void	COALBuffer::LoadSubData(const uint32 uOffset, const uint32 uSamples, const void* pData){
		CR_ALBINDCHECK(this->m_pParent->GetContext());

		auto uChannels = Utils::ToChannelFormat(this->m_uFormat);
		auto uSampleType = Utils::ToSampleType(this->m_uType);

		//alBufferData(this->m_uBuffer, uFormat, pData, this->m_uSamples, this->m_uSampleRate);
		alBufferSubSamplesSOFT(this->m_uBuffer, uOffset, uSamples, uChannels, uSampleType, pData);	CR_ALCHECK();
	}
}