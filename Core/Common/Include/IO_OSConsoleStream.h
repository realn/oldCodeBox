#pragma once

#include "../../Common/Include/IO_Stream.h"
#include "Macros.h"

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