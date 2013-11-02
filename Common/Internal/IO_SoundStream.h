#pragma once

#include "../Include/IO_SoundStream.h"
#include "../Include/IO_Sound.h"

namespace CB{
	class CSoundStream : 
		public IO::ISoundStream{
	private:
		CB::IO::CSound	m_Sound;

	public:
		CSoundStream(CB::CRefPtr<CB::IO::IStream> pFileSoundStream);
		~CSoundStream();

		const bool	CanWrite() const override;
		const bool	CanRead() const override;

		void	Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;
		void	Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;

		void	Read(CB::CRefPtr<IO::IStream> pOutStream, const uint32 uSizeInBytes) override;
		void	Write(CB::CRefPtr<IO::IStream> pInStream, const uint32 uSizeInBytes) override;

		const bool	IsEndOfStream() const override;
		const bool	IsBeginingOfStream() const override;

		const uint32	GetLength() const override;

		void	SetPos(const uint32 uPos, const IO::Direction uDirection, const IO::StreamPos uType) override;

		const uint32	GetPos() const override;

		void	Flush() override;

		const uint32	GetNumberOfChannels() const override;
		const uint32	GetNumberOfFrames() const override;
		const uint32	GetFrequency() const override;
		const uint32	GetSampleSize() const override;
		const uint32	GetFrameSize() const override;
	};
}