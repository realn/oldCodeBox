#include "stdafx.h"
#include "../Include/IO_TextWriter.h"
#include "../Include/IO_Stream.h"
#include "../Include/CBStringEx.h"

namespace CB{
	namespace IO{
		const String::Encoding g_uDefaultEncoding = String::Encoding::UTF16;

		CTextWriter::CTextWriter(const CRefPtr<IStream> pStream) : 
			CStreamWriter(pStream),
			m_uEncoding(g_uDefaultEncoding)
		{
		}

		CTextWriter::CTextWriter(const CRefPtr<IStream> pStream, const String::Encoding uDestEncoding) : 
			CStreamWriter(pStream),
			m_uEncoding(uDestEncoding)
		{
		}

		CTextWriter::CTextWriter(const IStreamWrapper& Wrapper) : 
			CStreamWriter(Wrapper),
			m_uEncoding(g_uDefaultEncoding)
		{
		}

		CTextWriter::CTextWriter(const IStreamWrapper& Wrapper, const String::Encoding uDestEncoding) : 
			CStreamWriter(Wrapper),
			m_uEncoding(uDestEncoding)
		{
		}

		void	CTextWriter::WriteText(const CString& strValue){
			switch (this->m_uEncoding){
			case String::Encoding::UTF16:	this->WriteTextUTF16(strValue);	break;
			case String::Encoding::UTF8:	this->WriteTextUTF8(strValue);	break;
			case String::Encoding::ANSI:	this->WriteTextANSI(strValue);	break;
			default:
				throw Exception::CInvalidVarValueException(L"m_uEncoding", String::ToString(this->m_uEncoding),
					L"Unknown encoding type.", CR_INFO());
			}
		}

		void	CTextWriter::WriteLine(const CString& strValue){
			switch (this->m_uEncoding){
			case String::Encoding::UTF16:	this->WriteLineUTF16(strValue);	break;
			case String::Encoding::UTF8:	this->WriteLineUTF8(strValue);	break;
			case String::Encoding::ANSI:	this->WriteLineANSI(strValue);	break;
			default:
				throw Exception::CInvalidVarValueException(L"m_uEncoding", String::ToString(this->m_uEncoding),
					L"Unknown encoding type.", CR_INFO());
			}
		}

		void	CTextWriter::WriteTextUTF16(const CString& strValue){
			this->m_pStream->Write<wchar>(strValue);
		}

		void	CTextWriter::WriteTextANSI(const CString& strValue){
			Collection::CList<int8> buffer;

			String::ToANSI(strValue, buffer);

			this->m_pStream->Write<int8>(buffer);
		}

		void	CTextWriter::WriteTextUTF8(const CString& strValue){
			Collection::CList<int8> buffer;

			String::ToUTF8(strValue, buffer);

			this->m_pStream->Write<int8>(buffer);
		}

		void	CTextWriter::WriteLineUTF16(const CString& strValue){
			this->WriteText(strValue + L"\n");
		}

		void	CTextWriter::WriteLineANSI(const CString& strValue){
			this->WriteTextANSI(strValue + L"\n");
		}

		void	CTextWriter::WriteLineUTF8(const CString& strValue){
			this->WriteTextUTF8(strValue + L"\n");
		}

		void	CTextWriter::SetEncoding(const String::Encoding uEncoding){
			this->m_uEncoding = uEncoding;
		}

		const String::Encoding	CTextWriter::GetEncoding() const{
			return this->m_uEncoding;
		}

		const CTextWriter&	CTextWriter::operator=(const CTextWriter& Writer){
			throw CB::Exception::CException(L"Not Implemented.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}
}