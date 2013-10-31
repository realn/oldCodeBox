#pragma once

#include "IO_Stream.h"

namespace CB{
	namespace IO{
		class COMMON_API CSound{
		private:
			CHiddenPtr	m_pData;

		public:
			CSound(CRefPtr<IStream> pStream);
			~CSound();

			const unsigned	GetNumberOfChannels() const;
			const unsigned	GetNumberOfFrames() const;
			const unsigned	GetFrequency() const;

			CRefPtr<IStream>	GetStream() const;

			void	ReadFrames(short* pData, const unsigned uFrames);
			void	ReadFrames(Collection::CList<short>& Data);
			void	ReadFrames(Collection::CList<short>& Data, const unsigned uFrames);

			void	WriteFrames(const short* pData, const unsigned uFrames);
			void	WriteFrames(const Collection::CList<short>& Data);
			void	WriteFrames(const Collection::CList<short>& Data, const unsigned uFrames);

			void	SetFrame(const unsigned uFrame);
			void	SetFrame(const int iFrame, StreamPos uType);

			const unsigned	GetFrame() const;
		};
	}
}