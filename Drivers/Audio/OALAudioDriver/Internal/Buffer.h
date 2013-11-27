#pragma once

#include "Device.h"

namespace CB{
	class COALBuffer : 
		public Audio::IBuffer,
		public Manage::IManagedObject<COALDevice, COALBuffer>
	{
	private:
		const Audio::BufferFormat	m_uFormat;
		const uint32				m_uFrequency;
		ALuint	m_uBuffer;

	public:
		COALBuffer(CRefPtr<COALDevice> pDevice, const Audio::BufferFormat uFormat, const uint32 uSampleRate, const void* pData);
		~COALBuffer();

		const ALuint	GetBufferID() const;

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		const uint32		GetLength() const override;
		const uint32		GetNumberOfChannels() const override;
		const Audio::BufferFormat	GetFormat() const override;
		const uint32		GetSampling() const override;
		const uint32		GetFrequency() const override;

		void	LoadData(const void* pData, const uint32 uLength) override;
		void	LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength) override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}