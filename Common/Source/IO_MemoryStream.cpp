#include "../Include/IO_MemoryStream.h"
#include "../Include/IO_Stream.h"

namespace CB{
	namespace IO{
		IMemoryStream::IMemoryStream() : 
		m_bCanRead(true),
		m_bCanWrite(true),
		m_pData(0),
		m_uLength(0),
		m_uPosition(0){
		}

		IMemoryStream::IMemoryStream(const IMemoryStream& Stream){
		}

		const bool	IMemoryStream::CanRead() const{
			return this->m_bCanRead;
		}

		const bool	IMemoryStream::CanWrite() const{
			return this->m_bCanWrite;
		}

		void	IMemoryStream::Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
			if(!this->m_bCanRead){
				throw Exception::CStreamException(
					L"Stream locked from reading.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(this->IsEndOfStream()){
				throw Exception::CStreamException(
					L"Reached end of stram.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(pData == 0){
				throw Exception::CNullArgumentException(L"pData",
					L"Invalid destination pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			unsigned uSize = uSizeInBytes * uNumberOfElements;
			if(this->m_uPosition + uSize > this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes * uNumberOfElements", String::FromUInt32(uSize),
					L"Tring to read too large chunk of data.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			Memory::CopyArray(this->m_pData + this->m_uPosition, pData, uSizeInBytes, uNumberOfElements);
			this->m_uPosition += uSize;
		}

		void	IMemoryStream::Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
			if(!this->m_bCanWrite){
				throw Exception::CStreamException(
					L"Stream locked from writing.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(this->IsEndOfStream()){
				throw Exception::CStreamException(
					L"Reached end of stream.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			unsigned uSize = uSizeInBytes * uNumberOfElements;
			if(this->m_uPosition + uSize > this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes * uNumberOfElements", String::FromUInt32(uSize),
					L"Tring to write too large chunk of data.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			Memory::CopyArray(pData, this->m_pData + this->m_uPosition, uSizeInBytes, uNumberOfElements);
			this->m_uPosition += uSize;
		}

		void	IMemoryStream::Read(CRefPtr<IStream> pStream, const unsigned uSize){
			if(pStream.IsNull()){
				throw Exception::CNullArgumentException(L"pStream",
					L"Passed not set reference pointer for out stream.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(this->m_uPosition + uSize >= this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes", String::FromUInt32(uSize),
					L"Size to read exceeds stream size.", __FUNCTIONW__, __FILEW__, __LINE__);
			}


			pStream->Write(this->m_pData + this->m_uPosition, uSize);
			this->m_uPosition += uSize;
		}

		void	IMemoryStream::Write(CRefPtr<IStream> pStream, const unsigned uSize){
			if(pStream.IsNull()){
				throw Exception::CNullArgumentException(L"pStream",
					L"Passet not set reference pointer for in stream.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(this->m_uPosition + uSize >= this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes", String::FromUInt32(uSize),
					L"Size to write exceeds stream size.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			pStream->Read(this->m_pData + this->m_uPosition, uSize);
			this->m_uPosition += uSize;
		}

		const bool	IMemoryStream::IsBeginingOfStream() const{
			return this->m_uPosition == 0;
		}

		const bool	IMemoryStream::IsEndOfStream() const{
			return this->m_uPosition >= this->m_uLength;
		}

		const unsigned	IMemoryStream::GetLength() const{
			return this->m_uLength;
		}

		const unsigned	IMemoryStream::GetPos() const{
			return this->m_uPosition;
		}

		void	IMemoryStream::SetPos(const int uPos, const StreamPos uType){
			switch (uType)
			{
			case StreamPos::Begin:	this->m_uPosition = uPos;	break;
			case StreamPos::Current:	this->m_uPosition += uPos;	break;
			case StreamPos::End:		this->m_uPosition = this->m_uLength - 1 - uPos;	break;
			default:
				break;
			}
		}

		void	IMemoryStream::Flush(){
		}

		//==================

		class CMemoryStream : public IMemoryStream{
		private:
			Collection::CList<unsigned char>	m_Data;

		public:
			CMemoryStream(const unsigned uLength);

			void	Create(const unsigned uLength);
		};

		CMemoryStream::CMemoryStream(const unsigned uLength) : IMemoryStream(){
			this->Create(uLength);
		}

		void	CMemoryStream::Create(const unsigned uLength){
			this->m_Data.Resize(uLength);
			this->m_uLength		= this->m_Data.GetLength();
			this->m_pData		= &m_Data[0];
			this->m_bCanRead	= true;
			this->m_bCanWrite	= true;
		}
	}

	namespace Memory{
		CRefPtr<IO::IMemoryStream>	CreateStream(const unsigned uLength){
			return new IO::CMemoryStream(uLength);
		}
	}
}