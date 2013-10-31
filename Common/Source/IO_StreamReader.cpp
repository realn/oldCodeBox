#include "../Include/IO_Stream.h"

namespace CB{
	namespace IO{
		CStreamReader::CStreamReader(const CRefPtr<IStream> pStream) : IStreamWrapper(pStream){
		}

		CStreamReader::CStreamReader(const IStreamWrapper& Wrapper) : IStreamWrapper(Wrapper){
		}

		void	CStreamReader::Read(char& chValue){
			this->m_pStream->Read<char>(chValue);
		}

		void	CStreamReader::Read(short& sValue){
			this->m_pStream->Read<short>(sValue);
		}

		void	CStreamReader::Read(int& iValue){
			this->m_pStream->Read<int>(iValue);
		}
		
		void	CStreamReader::Read(__int64& iValue){
			this->m_pStream->Read<__int64>(iValue);
		}

		void	CStreamReader::Read(unsigned char& uchValue){
			this->m_pStream->Read<unsigned char>(uchValue);
		}

		void	CStreamReader::Read(unsigned short& ushValue){
			this->m_pStream->Read<unsigned short>(ushValue);
		}

		void	CStreamReader::Read(unsigned int& uValue){
			this->m_pStream->Read<unsigned int>(uValue);
		}

		void	CStreamReader::Read(unsigned __int64& uValue){
			this->m_pStream->Read<unsigned __int64>(uValue);
		}

		void	CStreamReader::Read(float& fValue){
			this->m_pStream->Read<float>(fValue);
		}

		void	CStreamReader::Read(double& dValue){
			this->m_pStream->Read<double>(dValue);
		}

		void	CStreamReader::Read(CString& strValue){
			unsigned uLen = this->ReadUInt32();
			strValue.Resize(uLen);
			this->m_pStream->Read<wchar_t>(&strValue[0], uLen);
		}

		const char	CStreamReader::ReadInt8(){
			char chValue = 0;
			this->Read(chValue);
			return chValue;
		}

		const short	CStreamReader::ReadInt16(){
			short sValue = 0;
			this->Read(sValue);
			return sValue;
		}

		const int	CStreamReader::ReadInt32(){
			int iValue = 0;
			this->Read(iValue);
			return iValue;
		}

		const __int64	CStreamReader::ReadInt64(){
			__int64 iValue = 0;
			this->Read(iValue);
			return iValue;
		}

		const float	CStreamReader::ReadFloat32(){
			float fValue = 0.0f;
			this->Read(fValue);
			return fValue;
		}

		const double	CStreamReader::ReadFloat64(){
			double dValue = 0.0f;
			this->Read(dValue);
			return dValue;
		}

		const CString CStreamReader::ReadString(){
			CB::CString	strValue;
			this->Read(strValue);
			return strValue;
		}

		const unsigned char	CStreamReader::ReadUInt8(){
			unsigned char uchValue = 0;
			this->Read(uchValue);
			return uchValue;
		}

		const unsigned short CStreamReader::ReadUInt16(){
			unsigned short usValue = 0;
			this->Read(usValue);
			return usValue;
		}

		const unsigned int	CStreamReader::ReadUInt32(){
			unsigned int uValue = 0;
			this->Read(uValue);
			return uValue;
		}

		const unsigned __int64	CStreamReader::ReadUInt64(){
			unsigned __int64 uValue = 0;
			this->Read(uValue);
			return uValue;
		}

		const CStreamReader&	CStreamReader::operator=(const CStreamReader& Reader){
			throw CB::Exception::CException(L"Not implemented.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}
}