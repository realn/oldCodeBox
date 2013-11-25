#include "../Include/IO_StreamWriter.h"

namespace CB{
	namespace IO{
		CStreamWriter::CStreamWriter(const CRefPtr<IStream> pStream) : IStreamWrapper(pStream){
		}

		CStreamWriter::CStreamWriter(const IStreamWrapper& Wrapper) : IStreamWrapper(Wrapper){
		}

		void	CStreamWriter::Write(const int8 chValue){
			this->m_pStream->WriteValue<int8>(chValue);
		}

		void	CStreamWriter::Write(const int16 sValue){
			this->m_pStream->WriteValue<int16>(sValue);
		}

		void	CStreamWriter::Write(const int32 iValue){
			this->m_pStream->WriteValue<int32>(iValue);
		}

		void	CStreamWriter::Write(const int64 iValue){
			this->m_pStream->WriteValue<int64>(iValue);
		}

		void	CStreamWriter::Write(const float32 fValue){
			this->m_pStream->WriteValue<float32>(fValue);
		}

		void	CStreamWriter::Write(const float64 dValue){
			this->m_pStream->WriteValue<float64>(dValue);
		}

		void	CStreamWriter::Write(const CB::CString& strValue){
			uint32 uLen = strValue.GetLength();
			this->m_pStream->WriteValue<uint32>(uLen);
			this->m_pStream->Write(strValue);
		}

		void	CStreamWriter::Write(const uint8 uchValue){
			this->m_pStream->WriteValue<uint8>(uchValue);
		}

		void	CStreamWriter::Write(const uint16 usValue){
			this->m_pStream->WriteValue<uint16>(usValue);
		}

		void	CStreamWriter::Write(const uint32 uValue){
			this->m_pStream->WriteValue<uint32>(uValue);
		}

		void	CStreamWriter::Write(const uint64 uValue){
			this->m_pStream->WriteValue<uint64>(uValue);
		}

		void	CStreamWriter::Write(const void* pData, const uint32 uSizeInBytes){
			this->m_pStream->Write(pData, uSizeInBytes, 1);
		}

		const CStreamWriter&	CStreamWriter::operator=(const CStreamWriter& Writer){
			CR_THROW(L"NOT INVOKABLE");
		}
	}
}