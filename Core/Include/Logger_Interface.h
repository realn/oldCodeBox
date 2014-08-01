#pragma once

#include "Macros.h"
#include "Types.h"
#include "Logger_Consts.h"
#include "Ref.h"

namespace CB{
	class CString;
	template<typename _Type> class CRefPtr;

	namespace IO{
		class IStream;
	}

	namespace Exception{
		class CException;
	}

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