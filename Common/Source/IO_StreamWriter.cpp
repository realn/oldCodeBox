#include "../Include/IO_StreamWriter.h"

namespace CB{
	namespace IO{
		CStreamWriter::CStreamWriter(const CRefPtr<IStream> pStream) : IStreamWrapper(pStream){
		}

		CStreamWriter::CStreamWriter(const IStreamWrapper& Wrapper) : IStreamWrapper(Wrapper){
		}

		void	CStreamWriter::Write(const int8 chValue){
			this->m_pStream->Write<int8>(chValue);
		}

		void	CStreamWriter::Write(const int16 sValue){
			this->m_pStream->Write<int16>(sValue);
		}

		void	CStreamWriter::Write(const int32 iValue){
			this->m_pStream->Write<int>(iValue);
		}

		void	CStreamWriter::Write(const int64 iValue){
			this->m_pStream->Write<int64>(iValue);
		}

		void	CStreamWriter::Write(const float32 fValue){
			this->m_pStream->Write<float32>(fValue);
		}

		void	CStreamWriter::Write(const float64 dValue){
			this->m_pStream->Write<float64>(dValue);
		}

		void	CStreamWriter::Write(const CB::CString& strValue){
			uint32 uLen = strValue.GetLength();
			this->m_pStream->Write<uint32>(uLen);
			this->m_pStream->Write<wchar>(strValue.ToConst(), strValue.GetLength());
		}

		void	CStreamWriter::Write(const uint8 uchValue){
			this->m_pStream->Write<uint8>(uchValue);
		}

		void	CStreamWriter::Write(const uint16 usValue){
			this->m_pStream->Write<uint16>(usValue);
		}

		void	CStreamWriter::Write(const uint32 uValue){
			this->m_pStream->Write<uint32>(uValue);
		}

		void	CStreamWriter::Write(const uint64 uValue){
			this->m_pStream->Write<uint64>(uValue);
		}

		const CStreamWriter&	CStreamWriter::operator=(const CStreamWriter& Writer){
			throw CB::Exception::CException(L"Not Implemented.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}
}