#pragma once

#include <Types.h>
#include <AudioDriver.h>
#include <als\al.h>
#include <als\alext.h>

namespace CB{
	namespace Utils{
		extern const ALenum	ToBufferFormat(const Audio::BufferFormat uFormat);
		
	}
}