#pragma once

#include "Macros.h"
#include "IO_Stream.h"

namespace CB{
	namespace IO{
		class IOSConsoleStream : 
			public IO::IStream
		{
		};

		namespace Console{
			extern COMMON_API CRefPtr<IOSConsoleStream>	Create();
		}
	}
}