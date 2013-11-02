#include "../Include/Logger_Formatters.h"
#include "../Include/IO_TextWriter.h"

namespace CB{
	namespace Log{
		CTextFormatter::CTextFormatter(const CTextFormatter&) : 
			m_uEncoding(String::Encoding::UTF16)
		{
			CR_THROWNOTIMPLEMENTED();
		}

		CTextFormatter::CTextFormatter(const String::Encoding uEncoding) :
			m_uEncoding(uEncoding)
		{
		}

		CTextFormatter::~CTextFormatter(){
		}

		void	CTextFormatter::LogBegin(CRefPtr<IO::IStream> pStream){
			IO::CTextWriter writer(pStream, this->m_uEncoding);

			writer.WriteLine(L"Log Begin.");
		}

		void	CTextFormatter::LogEnd(CRefPtr<IO::IStream> pStream){
			IO::CTextWriter writer(pStream, this->m_uEncoding);

			writer.WriteLine(L"Log End.");
		}

		void	CTextFormatter::EntryBegin(CRefPtr<IO::IStream> pStream){
		}

		void	CTextFormatter::EntryEnd(CRefPtr<IO::IStream> pStream){
		}

		void	CTextFormatter::FormatEntry(CRefPtr<IO::IStream> pStream, const CString& strEntry, const LogLevel uLevel){
			IO::CTextWriter writer(pStream, this->m_uEncoding);

			writer.WriteLine(String::ToString(uLevel) + L": " + strEntry);
		}

		void	CTextFormatter::FormatEntry(CRefPtr<IO::IStream> pStream, const Exception::CException& Exception, const LogLevel uLevel){
			IO::CTextWriter writer(pStream, this->m_uEncoding);

			writer.WriteLine(String::ToString(uLevel) + L": EXCEPTION:");
			writer.WriteLine(L"\tFile:\t" + Exception.GetFile());
			writer.WriteLine(L"\tLine:\t" + String::FromUInt32(Exception.GetLine()));
			writer.WriteLine(L"\tFunction:\t" + Exception.GetFunction());
			writer.WriteLine(L"\tMessage:\t" + Exception.GetMessage());

			const Exception::CException* pException = &Exception;
			while(pException->HasInnerException()){
				pException = &pException->GetInnerException();

				writer.WriteLine(L"\tInner exception:");
				writer.WriteLine(L"\t\tFile:\t" + pException->GetFile());
				writer.WriteLine(L"\t\tLine:\t" + String::FromUInt32(pException->GetLine()));
				writer.WriteLine(L"\t\tFunction:\t" + pException->GetFunction());
				writer.WriteLine(L"\t\tMessage:\t" + pException->GetMessage());
			}
		}

		CRefPtr<CTextFormatter>	CTextFormatter::Create(){
			return Create(String::Encoding::UTF16);
		}

		CRefPtr<CTextFormatter> CTextFormatter::Create(const String::Encoding uEncoding){
			return new CTextFormatter(uEncoding);
		}
	}
}