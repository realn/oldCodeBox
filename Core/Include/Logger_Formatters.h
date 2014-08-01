#pragma once 

#include "Macros.h"
#include "Types.h"
#include "Logger_Interface.h"
#include "CBString_Consts.h"

namespace CB{
	class CString;
	template<typename _Type> class CRefPtr;

	namespace Exception{
		class CException;
	}

	namespace Log{
		class COMMON_API CTextFormatter :
			public IEntryFormat
		{
		protected:
			const String::Encoding	m_uEncoding;

		public:
			void	LogBegin(CRefPtr<IO::IStream> pStream) override;
			void	LogEnd(CRefPtr<IO::IStream> pStream) override;

			void	EntryBegin(CRefPtr<IO::IStream> pStream) override;
			void	EntryEnd(CRefPtr<IO::IStream> pStream) override;

			void	FormatEntry(CRefPtr<IO::IStream> pStream, const CString& strEntry, const LogLevel uLevel) override;
			void	FormatEntry(CRefPtr<IO::IStream> pStream, const Exception::CException& Exception, const LogLevel uLevel) override;

			static CRefPtr<CTextFormatter>	Create();
			static CRefPtr<CTextFormatter>	Create(const String::Encoding uEncoding);

		protected:
			CTextFormatter(const CTextFormatter&);
			CTextFormatter(const String::Encoding uEncoding);
			~CTextFormatter();
		};
	}
}