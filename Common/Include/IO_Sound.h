#pragma once

#include "IO_Stream.h"
#include "SmartPointers_Hidden.h"
#pragma warning(disable : 4251)

namespace CB{
	namespace IO{
		class COMMON_API CSound{
		private:
			CHiddenPtr	m_pData;

		public:
			CSound(CRefPtr<IStream> pStream);
			~CSound();

			const uint32	GetNumberOfChannels() const;
			const uint32	GetNumberOfFrames() const;
			const uint32	GetFrequency() const;

			CRefPtr<IStream>	GetStream() const;

			void	ReadFrames(int16* pData, const uint32 uFrames);
			void	ReadFrames(Collection::IPacked<int16>& Data);
			void	ReadFrames(Collection::IPacked<int16>& Data, const uint32 uFrames);

			void	WriteFrames(const int16* pData, const uint32 uFrames);
			void	WriteFrames(const Collection::IPacked<int16>& Data);
			void	WriteFrames(const Collection::IPacked<int16>& Data, const uint32 uFrames);

			void	SetFrame(const uint32 uFrame);
			void	SetFrame(const uint32 iFrame, const Direction uDirection, StreamPos uType);

			const uint32	GetFrame() const;
		};
	}
}