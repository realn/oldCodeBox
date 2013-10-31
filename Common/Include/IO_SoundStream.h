#pragma once

#include "IO_Stream.h"

namespace CB{
	namespace IO{
		class ISoundStream : public IStream{
		public:
			virtual const unsigned	GetNumberOfChannels() const = 0;
			virtual const unsigned	GetNumberOfFrames() const = 0;
			virtual const unsigned	GetFrequency() const = 0;
			virtual const unsigned	GetSampleSize() const = 0;
			virtual const unsigned	GetFrameSize() const = 0; // = Sample Size * Num of channels
		};

		namespace Audio{
			extern COMMON_API CRefPtr<IO::ISoundStream>	CreateStream(CRefPtr<IO::IStream> pSoundFileStream);		
		}
	}
}