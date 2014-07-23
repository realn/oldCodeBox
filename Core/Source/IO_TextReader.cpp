#include "stdafx.h"
#include "../Include/IO_TextReader.h"
#include "../Include/IO_Stream.h"
#include "../Include/CBStringEx.h"
#include "../Include/Collection_Funcs.h"

namespace CB{
	namespace IO{
		const String::Encoding	g_uDefaultEncoding = String::Encoding::UTF16;
		const uint32			g_uDefaultBufferLength = 1024;

		CTextReader::CTextReader(const CRefPtr<IStream> pStream) : 
			CStreamReader(pStream),
			m_uEncoding(g_uDefaultEncoding),
			m_uReadBufferLength(g_uDefaultBufferLength)
		{
		}

		CTextReader::CTextReader(const CRefPtr<IStream> pStream, const String::Encoding uSourceEncoding) : 
			CStreamReader(pStream),
			m_uEncoding(uSourceEncoding),
			m_uReadBufferLength(g_uDefaultBufferLength)
		{
		}

		CTextReader::CTextReader(const IStreamWrapper& Wrapper) : 
			CStreamReader(Wrapper),
			m_uEncoding(g_uDefaultEncoding),
			m_uReadBufferLength(g_uDefaultBufferLength)
		{
		}

		CTextReader::CTextReader(const IStreamWrapper& Wrapper, const String::Encoding uSourceEncoding) : 
			CStreamReader(Wrapper),
			m_uEncoding(uSourceEncoding),
			m_uReadBufferLength(g_uDefaultBufferLength)
		{
		}

		const CString	CTextReader::ReadText(){
			switch (this->m_uEncoding){
			case String::Encoding::ANSI:	return this->ReadTextANSI();
			case String::Encoding::UTF8:	return this->ReadTextUTF8();
			case String::Encoding::UTF16:	return this->ReadTextUTF16();
			default:
				throw Exception::CInvalidVarValueException(L"m_uEncoding", String::ToString(m_uEncoding),
					L"Unknown encoding.", CR_INFO());
			}
		}

		const CString	CTextReader::ReadLine(){
			switch (this->m_uEncoding){
			case String::Encoding::ANSI:	return this->ReadLineANSI();
			case String::Encoding::UTF8:	return this->ReadLineUTF8();
			case String::Encoding::UTF16:	return this->ReadLineUTF16();
			default:
				throw Exception::CInvalidVarValueException(L"m_uEncoding", String::ToString(m_uEncoding),
					L"Unknown encoding.", CR_INFO());
			}
		}

		void	CTextReader::SetEncoding(const String::Encoding uEncoding){
			this->m_uEncoding = uEncoding;
		}

		const String::Encoding	CTextReader::GetEncoding() const{
			return this->m_uEncoding;
		}

		void	CTextReader::SetReadBufferLength(const uint32 uLength){
			this->m_uReadBufferLength = uLength;
		}

		const uint32	CTextReader::GetReadBufferLength() const{
			return this->m_uReadBufferLength;
		}

		const CString	CTextReader::ReadTextUTF16(){
			uint32 uStreamPos = this->m_pStream->GetPos();
			uint32 uStreamLen = this->m_pStream->GetLength();
			uint32 uBufferLen = (uStreamLen - uStreamPos) / sizeof(wchar);
			if(uBufferLen == 0){
				return L"";
			}

			Collection::CList<wchar> Buffer(uBufferLen);

			this->m_pStream->Read<wchar>(Buffer);
			if(Buffer[0] == 0){
				return L"";
			}

			return String::ToString(Buffer);
		}

		const CString	CTextReader::ReadTextANSI(){
			uint32 uStreamPos = this->m_pStream->GetPos();
			uint32 uStreamLen = this->m_pStream->GetLength();
			uint32 uBufferLen = (uStreamLen - uStreamPos) / sizeof(int8);
			if(uBufferLen == 0){
				return L"";
			}

			Collection::CList<int8> Buffer(uBufferLen);

			this->m_pStream->Read<int8>(Buffer);
			if(Buffer[0] == 0){
				return L"";
			}

			return String::FromANSI(Buffer);
		}

		const CString	CTextReader::ReadTextUTF8(){
			uint32 uStreamPos = this->m_pStream->GetPos();
			uint32 uStreamLen = this->m_pStream->GetLength();
			uint32 uBufferLen = (uStreamLen - uStreamPos) / sizeof(int8);
			if(uBufferLen == 0){
				return L"";
			}

			Collection::CList<int8> Buffer(uBufferLen);

			this->m_pStream->Read<int8>(Buffer);
			if(Buffer[0] == 0){
				return L"";
			}

			return String::FromUTF8(Buffer);
		}

		const CString	CTextReader::ReadLineUTF16(){
			CString strReturn;
			
			uint32 uBufferStreamLen = this->m_uReadBufferLength;
			uint32 uStreamLen = this->m_pStream->GetLength();
			uint32 uStreamPos = this->m_pStream->GetPos();
			uint32 uBufferLen = 0;

			Collection::CList<wchar> Buffer;

			while(uStreamPos < uStreamLen){
				if(uStreamPos + uBufferStreamLen > uStreamLen){
					uBufferStreamLen = uStreamLen - uStreamPos;
				}
				uBufferLen = uBufferStreamLen / sizeof(wchar);
				if(uBufferLen == 0){
					break;
				}

				Buffer.Resize(uBufferLen);
				Memory::SetZeroArray(Buffer);
				this->m_pStream->Read(Buffer);

				uint32 uNewLinePos = 0;
				if(Collection::TryFind(Buffer, L'\n', uNewLinePos)){
					if(uNewLinePos > 0){
						strReturn += String::ToString(Buffer.Sub(0, uNewLinePos));
					}
					uStreamPos += (uNewLinePos + 1) * sizeof(wchar);
					break;
				}
				else{
					strReturn	+= CB::String::ToString(Buffer);
					uStreamPos	+= Buffer.GetLength() * sizeof(wchar);
				}
			}

			this->m_pStream->SetPos(uStreamPos);
			return strReturn;
		}

		const CString	CTextReader::ReadLineANSI(){
			CString	strReturn;

			unsigned uBufferStreamLen = this->m_uReadBufferLength;
			unsigned uStreamLen = this->m_pStream->GetLength();
			unsigned uStreamPos = this->m_pStream->GetPos();
			unsigned uBufferLen = 0;

			CB::Collection::CList<int8> Buffer;

			while(uStreamPos < uStreamLen){
				if(uStreamPos + uBufferStreamLen > uStreamLen){
					uBufferStreamLen = uStreamLen - uStreamPos;
				}
				uBufferLen = uBufferStreamLen / sizeof(int8);
				if(uBufferLen == 0){
					break;
				}

				Buffer.Resize(uBufferLen);
				Memory::SetZeroArray(Buffer);
				this->m_pStream->Read(Buffer);

				uint32 uNewLinePos = 0;
				if(Collection::TryFind(Buffer, (int8)'\n', uNewLinePos)){
					if(uNewLinePos > 0){
						strReturn += String::FromANSI(Buffer.Sub(0, uNewLinePos));
					}
					uStreamPos += (uNewLinePos + 1) * sizeof(int8);
					break;
				}
				else{
					strReturn	+= String::FromANSI(Buffer);
					uStreamPos	+= Buffer.GetLength() * sizeof(int8);
				}
			}

			this->m_pStream->SetPos(uStreamPos);
			return strReturn;
		}

		const CString	CTextReader::ReadLineUTF8(){
			CString strReturn;

			uint32 uBufferStreamLen = this->m_uReadBufferLength;
			uint32 uStreamLen = this->m_pStream->GetLength();
			uint32 uStreamPos = this->m_pStream->GetPos();
			uint32 uBufferLen = 0;

			CB::Collection::CList<int8> Buffer;

			while(uStreamPos < uStreamLen){
				if(uStreamPos + uBufferStreamLen > uStreamLen){
					uBufferStreamLen = uStreamLen - uStreamPos;
				}
				uBufferLen = uBufferStreamLen / sizeof(int8);
				if(uBufferLen == 0){
					break;
				}

				Buffer.Resize(uBufferLen);
				Memory::SetZeroArray(Buffer);
				this->m_pStream->Read(Buffer);

				uint32 uNewLinePos = 0;
				if(Collection::TryFind(Buffer, (int8)'\n', uNewLinePos)){
					if(uNewLinePos > 0){
						strReturn += String::FromUTF8(Buffer.Sub(0, uNewLinePos));
					}
					uStreamPos += (uNewLinePos + 1) * sizeof(int8);
					break;
				}
				else{
					strReturn	+= String::FromUTF8(Buffer);
					uStreamPos	+= Buffer.GetLength() * sizeof(int8);
				}
			}

			this->m_pStream->SetPos(uStreamPos);
			return strReturn;
		}

		const CTextReader&	CTextReader::operator=(const CTextReader& reader){
			return *this;
		}
	}
}