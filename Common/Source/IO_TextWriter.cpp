#include "../Include/IO_Stream.h"
#include "../Include/CBStringEx.h"

namespace CB{
	namespace IO{
		CTextWriter::CTextWriter(const CRefPtr<IStream> pStream) : CStreamWriter(pStream){
		}

		CTextWriter::CTextWriter(const IStreamWrapper& Wrapper) : CStreamWriter(Wrapper){
		}

		void	CTextWriter::WriteText(const CString& strValue){
			Collection::CList<wchar_t> buffer;

			String::ToArray(strValue, buffer);

			this->m_pStream->Write<wchar_t>(buffer);
		}

		void	CTextWriter::WriteTextANSI(const CString& strValue){
			Collection::CList<char> buffer;

			String::ToANSI(strValue, buffer);

			this->m_pStream->Write<char>(buffer);
		}

		void	CTextWriter::WriteTextUTF8(const CString& strValue){
			Collection::CList<char> buffer;

			String::ToUTF8(strValue, buffer);

			this->m_pStream->Write<char>(buffer);
		}

		void	CTextWriter::WriteLine(const CString& strValue){
			this->WriteText(strValue + L"\n");
		}

		void	CTextWriter::WriteLineANSI(const CString& strValue){
			this->WriteTextANSI(strValue + L"\n");
		}

		void	CTextWriter::WriteLineUTF8(const CString& strValue){
			this->WriteTextUTF8(strValue + L"\n");
		}

		const CTextWriter&	CTextWriter::operator=(const CTextWriter& Writer){
			throw CB::Exception::CException(L"Not Implemented.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}
}