#pragma once

#include "Device.h"

namespace CB{
	class COALBuffer : 
		public Audio::IBuffer,
		public Manage::IManagedObject<COALDevice, COALBuffer>
	{
	private:
		const Audio::BufferFormat	m_uFormat;
		const uint32				m_uSampleRate;
		const uint32				m_uSamples;
		ALuint	m_uBuffer;

	public:
		COALBuffer(CRefPtr<COALDevice> pDevice, const Audio::BufferFormat uFormat, const uint32 uSampleRate, const uint32 uSamples);
		~COALBuffer();

		const ALuint	GetBufferID() const;

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		const uint32				GetSamples() const override;
		const uint32				GetSampleRate() const override;
		const Audio::BufferFormat	GetFormat() const override;

		void	LoadData(const Audio::SampleType uType, const uint32 uSamples, const void* pData) override;
		void	LoadSubData(const Audio::SampleType uType, const uint32 uOffset, const uint32 uSamples, const void* pData) override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}