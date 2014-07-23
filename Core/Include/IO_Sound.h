#pragma once

#include "SmartPointers_Hidden.h"

namespace CB{
	namespace IO{
		class IStream;
		template<typename _Type> class CRefPtr;
		template<typename _Type> class Collection::IPacked;
		enum class Direction;
		enum class StreamPos;

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