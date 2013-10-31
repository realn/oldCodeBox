#include "../Include/IO_Stream.h"
#include "../Include/CBStringEx.h"

namespace CB{
	namespace IO{
		CTextReader::CTextReader(const CRefPtr<IStream> pStream) : CStreamReader(pStream){
		}

		CTextReader::CTextReader(const IStreamWrapper& Wrapper) : CStreamReader(Wrapper){
		}

		const CString	CTextReader::ReadText(){
			unsigned uStreamLen = this->m_pStream->GetLength();
			unsigned uBufferLen = uStreamLen / sizeof(wchar_t);
			if(uBufferLen == 0){
				return L"";
			}

			Collection::CList<wchar_t> Buffer(uBufferLen);

			this->m_pStream->Read<wchar_t>(Buffer);
			if(Buffer[0] == 0){
				return L"";
			}

			return String::ToString(Buffer);
		}

		const CString	CTextReader::ReadTextANSI(){
			unsigned uStreamLen = this->m_pStream->GetLength();
			unsigned uBufferLen = uStreamLen / sizeof(char);
			if(uBufferLen == 0){
				return L"";
			}

			Collection::CList<char> Buffer(uBufferLen);

			this->m_pStream->Read<char>(Buffer);
			if(Buffer[0] == 0){
				return L"";
			}

			return String::FromANSI(Buffer);
		}

		const CString	CTextReader::ReadTextUTF8(){
			unsigned uStreamLen = this->m_pStream->GetLength();
			unsigned uBufferLen = uStreamLen / sizeof(char);
			if(uBufferLen == 0){
				return L"";
			}

			Collection::CList<char> Buffer(uBufferLen);

			this->m_pStream->Read<char>(Buffer);
			if(Buffer[0] == 0){
				return L"";
			}

			return String::FromUTF8(Buffer);
		}

		const CString	CTextReader::ReadLine(){
			CString strReturn;
			
			unsigned uBufferStreamLen = 1024;
			unsigned uStreamLen = this->m_pStream->GetLength();
			unsigned uStreamPos = this->m_pStream->GetPos();
			unsigned uBufferLen = 0;

			Collection::CList<wchar_t> Buffer;

			while(uStreamPos < uStreamLen){
				if(uStreamPos + uBufferStreamLen > uStreamLen){
					uBufferStreamLen = uStreamLen - uStreamPos;
				}
				uBufferLen = uBufferStreamLen / sizeof(wchar_t);
				if(uBufferLen == 0){
					break;
				}

				Buffer.Resize(uBufferLen);
				Memory::SetZeroArray(Buffer);
				this->m_pStream->Read(Buffer);

				unsigned uNewLinePos = 0;
				if(Collection::TryFind(Buffer, L'\n', uNewLinePos)){
					if(uNewLinePos > 0){
						strReturn += String::ToString(Buffer.Sub(0, uNewLinePos));
					}
					uStreamPos += (uNewLinePos + 1) * sizeof(wchar_t);
					break;
				}
				else{
					strReturn	+= CB::String::ToString(Buffer);
					uStreamPos	+= Buffer.GetLength() * sizeof(wchar_t);
				}
			}

			this->m_pStream->SetPos(uStreamPos);
			return strReturn;
		}

		const CString	CTextReader::ReadLineANSI(){
			CString	strReturn;

			unsigned uBufferStreamLen = 1024;
			unsigned uStreamLen = this->m_pStream->GetLength();
			unsigned uStreamPos = this->m_pStream->GetPos();
			unsigned uBufferLen = 0;

			CB::Collection::CList<char> Buffer;

			while(uStreamPos < uStreamLen){
				if(uStreamPos + uBufferStreamLen > uStreamLen){
					uBufferStreamLen = uStreamLen - uStreamPos;
				}
				uBufferLen = uBufferStreamLen / sizeof(char);
				if(uBufferLen == 0){
					break;
				}

				Buffer.Resize(uBufferLen);
				Memory::SetZeroArray(Buffer);
				this->m_pStream->Read(Buffer);

				unsigned uNewLinePos = 0;
				if(Collection::TryFind(Buffer, '\n', uNewLinePos)){
					if(uNewLinePos > 0){
						strReturn += String::FromANSI(Buffer.Sub(0, uNewLinePos));
					}
					uStreamPos += (uNewLinePos + 1) * sizeof(char);
					break;
				}
				else{
					strReturn	+= String::FromANSI(Buffer);
					uStreamPos	+= Buffer.GetLength() * sizeof(char);
				}
			}

			this->m_pStream->SetPos(uStreamPos);
			return strReturn;
		}

		const CString	CTextReader::ReadLineUTF8(){
			CString strReturn;

			unsigned uBufferStreamLen = 1024;
			unsigned uStreamLen = this->m_pStream->GetLength();
			unsigned uStreamPos = this->m_pStream->GetPos();
			unsigned uBufferLen = 0;

			CB::Collection::CList<char> Buffer;

			while(uStreamPos < uStreamLen){
				if(uStreamPos + uBufferStreamLen > uStreamLen){
					uBufferStreamLen = uStreamLen - uStreamPos;
				}
				uBufferLen = uBufferStreamLen / sizeof(char);
				if(uBufferLen == 0){
					break;
				}

				Buffer.Resize(uBufferLen);
				Memory::SetZeroArray(Buffer);
				this->m_pStream->Read(Buffer);

				unsigned uNewLinePos = 0;
				if(Collection::TryFind(Buffer, '\n', uNewLinePos)){
					if(uNewLinePos > 0){
						strReturn += String::FromUTF8(Buffer.Sub(0, uNewLinePos));
					}
					uStreamPos += (uNewLinePos + 1) * sizeof(char);
					break;
				}
				else{
					strReturn	+= String::FromUTF8(Buffer);
					uStreamPos	+= Buffer.GetLength() * sizeof(char);
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