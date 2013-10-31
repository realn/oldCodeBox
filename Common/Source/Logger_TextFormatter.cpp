#include "../Include/Logger_Formatters.h"

namespace CB{
	namespace Log{
		CTextFormatter::CTextFormatter(){
		}

		CTextFormatter::~CTextFormatter(){
		}

		void	CTextFormatter::LogBegin(CRefPtr<IO::IStream> pStream){
			IO::CTextWriter writer(pStream);

			
		}

		void	CTextFormatter::LogEnd(CRefPtr<IO::IStream> pStream) override;

		void	CTextFormatter::EntryBegin(CRefPtr<IO::IStream> pStream) override;
		void	CTextFormatter::EntryEnd(CRefPtr<IO::IStream> pStream) override;

		void	CTextFormatter::FormatEntry(CRefPtr<IO::IStream> pStream, const CString& strEntry, const LogLevel uLevel) override;
		void	CTextFormatter::FormatEntry(CRefPtr<IO::IStream> pStream, const Exception::CException& Exception, const LogLevel uLevel) override;

		static CRefPtr<CTextFormatter>	CTextFormatter::Create();
	}
}