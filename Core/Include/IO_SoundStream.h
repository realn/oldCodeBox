#pragma once

#include "IO_Stream.h"

namespace CB{
	namespace IO{
		class ISoundStream : 
			public IStream{
		public:
			virtual const uint32	GetNumberOfChannels() const = 0;
			virtual const uint32	GetNumberOfFrames() const = 0;
			virtual const uint32	GetFrequency() const = 0;
			virtual const uint32	GetSampleSize() const = 0;
			virtual const uint32	GetFrameSize() const = 0; // = Sample Size * Num of channels
		};

		namespace Audio{
			extern COMMON_API CRefPtr<IO::ISoundStream>	CreateStream(CRefPtr<IO::IStream> pSoundFileStream);		
		}
	}
}