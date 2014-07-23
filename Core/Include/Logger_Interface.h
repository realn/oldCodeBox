#pragma once

#include "IO_Stream.h"
#include "SmartPointers_RefPtr.h"
#include "Logger_Consts.h"

namespace CB{
	namespace Log{
		class COMMON_API IEntryFormat :
			public virtual IRef
		{
		public:
			virtual void	LogBegin(CRefPtr<IO::IStream> pStream) = 0;
			virtual void	LogEnd(CRefPtr<IO::IStream> pStream) = 0;

			virtual void	EntryBegin(CRefPtr<IO::IStream> pStream) = 0;
			virtual void	EntryEnd(CRefPtr<IO::IStream> pStream) = 0;

			virtual void	FormatEntry(CRefPtr<IO::IStream> pStream, const CString& strEntry, const LogLevel uLevel) = 0;
			virtual void	FormatEntry(CRefPtr<IO::IStream> pStream, const Exception::CException& Exception, const LogLevel uLevel) = 0;
		};
	}
}