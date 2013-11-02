#include "../Include/IO_StreamReader.h"

namespace CB{
	namespace IO{
		CStreamReader::CStreamReader(const CRefPtr<IStream> pStream) : 
			IStreamWrapper(pStream)
		{
		}

		CStreamReader::CStreamReader(const IStreamWrapper& Wrapper) : 
			IStreamWrapper(Wrapper)
		{
		}

		void	CStreamReader::Read(int8& chValue){
			this->m_pStream->ReadValue<int8>(chValue);
		}

		void	CStreamReader::Read(int16& sValue){
			this->m_pStream->ReadValue<int16>(sValue);
		}

		void	CStreamReader::Read(int32& iValue){
			this->m_pStream->ReadValue<int32>(iValue);
		}
		
		void	CStreamReader::Read(int64& iValue){
			this->m_pStream->ReadValue<int64>(iValue);
		}

		void	CStreamReader::Read(uint8& uchValue){
			this->m_pStream->ReadValue<uint8>(uchValue);
		}

		void	CStreamReader::Read(uint16& ushValue){
			this->m_pStream->ReadValue<uint16>(ushValue);
		}

		void	CStreamReader::Read(uint32& uValue){
			this->m_pStream->ReadValue<uint32>(uValue);
		}

		void	CStreamReader::Read(uint64& uValue){
			this->m_pStream->ReadValue<uint64>(uValue);
		}

		void	CStreamReader::Read(float32& fValue){
			this->m_pStream->ReadValue<float32>(fValue);
		}

		void	CStreamReader::Read(float64& dValue){
			this->m_pStream->ReadValue<float64>(dValue);
		}

		void	CStreamReader::Read(CString& strValue){
			unsigned uLen = this->ReadUInt32();
			strValue.Resize(uLen);
			this->m_pStream->Read(strValue);
		}

		const int8	CStreamReader::ReadInt8(){
			int8 chValue = 0;
			this->Read(chValue);
			return chValue;
		}

		const int16	CStreamReader::ReadInt16(){
			int16 sValue = 0;
			this->Read(sValue);
			return sValue;
		}

		const int32	CStreamReader::ReadInt32(){
			int32 iValue = 0;
			this->Read(iValue);
			return iValue;
		}

		const int64	CStreamReader::ReadInt64(){
			int64 iValue = 0;
			this->Read(iValue);
			return iValue;
		}

		const float32	CStreamReader::ReadFloat32(){
			float32 fValue = 0.0f;
			this->Read(fValue);
			return fValue;
		}

		const float64	CStreamReader::ReadFloat64(){
			float64 dValue = 0.0f;
			this->Read(dValue);
			return dValue;
		}

		const CString CStreamReader::ReadString(){
			CB::CString	strValue;
			this->Read(strValue);
			return strValue;
		}

		const uint8	CStreamReader::ReadUInt8(){
			uint8 uchValue = 0;
			this->Read(uchValue);
			return uchValue;
		}

		const uint16 CStreamReader::ReadUInt16(){
			uint16 usValue = 0;
			this->Read(usValue);
			return usValue;
		}

		const uint32	CStreamReader::ReadUInt32(){
			uint32 uValue = 0;
			this->Read(uValue);
			return uValue;
		}

		const uint64	CStreamReader::ReadUInt64(){
			uint64 uValue = 0;
			this->Read(uValue);
			return uValue;
		}

		const CStreamReader&	CStreamReader::operator=(const CStreamReader& Reader){
			CR_THROWNOTIMPLEMENTED();
		}
	}
}