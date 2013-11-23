#include "../Include/IO_MemoryStream.h"
#include "../Include/IO_Stream.h"
#include "../Include/Memory.h"
#include "../Include/Collection_List.h"

namespace CB{
	namespace IO{
		IMemoryStream::IMemoryStream() : 
			m_bCanRead(true),
			m_bCanWrite(true),
			m_pData(0),
			m_uLength(0),
			m_uPosition(0)
		{
		}

		IMemoryStream::IMemoryStream(const IMemoryStream& Stream){
		}

		const bool	IMemoryStream::CanRead() const{
			return this->m_bCanRead;
		}

		const bool	IMemoryStream::CanWrite() const{
			return this->m_bCanWrite;
		}

		void	IMemoryStream::Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
			if(!this->m_bCanRead){
				throw Exception::CStreamException(
					L"Stream locked from reading.", CR_INFO());
			}
			if(this->IsEndOfStream()){
				throw Exception::CStreamException(
					L"Reached end of stram.", CR_INFO());
			}
			if(pData == 0){
				throw Exception::CNullArgumentException(L"pData",
					L"Invalid destination pointer.", CR_INFO());
			}

			uint32 uSize = uSizeInBytes * uNumberOfElements;
			if(this->m_uPosition + uSize > this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes * uNumberOfElements", String::FromUInt32(uSize),
					L"Tring to read too large chunk of data.", CR_INFO());
			}

			Memory::CopyArray(this->m_pData + this->m_uPosition, pData, uSizeInBytes, uNumberOfElements);
			this->m_uPosition += uSize;
		}

		void	IMemoryStream::Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
			if(!this->m_bCanWrite){
				throw Exception::CStreamException(
					L"Stream locked from writing.", CR_INFO());
			}
			if(this->IsEndOfStream()){
				throw Exception::CStreamException(
					L"Reached end of stream.", CR_INFO());
			}

			uint32 uSize = uSizeInBytes * uNumberOfElements;
			if(this->m_uPosition + uSize > this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes * uNumberOfElements", String::FromUInt32(uSize),
					L"Tring to write too large chunk of data.", CR_INFO());
			}

			Memory::CopyArray(pData, this->m_pData + this->m_uPosition, uSizeInBytes, uNumberOfElements);
			this->m_uPosition += uSize;
		}

		void	IMemoryStream::Read(CRefPtr<IStream> pStream, const uint32 uSize){
			if(pStream.IsNull()){
				throw Exception::CNullArgumentException(L"pStream",
					L"Passed not set reference pointer for out stream.", CR_INFO());
			}
			if(this->m_uPosition + uSize >= this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes", String::FromUInt32(uSize),
					L"Size to read exceeds stream size.", CR_INFO());
			}


			pStream->Write(this->m_pData + this->m_uPosition, uSize);
			this->m_uPosition += uSize;
		}

		void	IMemoryStream::Write(CRefPtr<IStream> pStream, const uint32 uSize){
			if(pStream.IsNull()){
				throw Exception::CNullArgumentException(L"pStream",
					L"Passet not set reference pointer for in stream.", CR_INFO());
			}
			if(this->m_uPosition + uSize >= this->m_uLength){
				throw Exception::CInvalidArgumentException(L"uSizeInBytes", String::FromUInt32(uSize),
					L"Size to write exceeds stream size.", CR_INFO());
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

		const uint32	IMemoryStream::GetLength() const{
			return this->m_uLength;
		}

		const uint32	IMemoryStream::GetPos() const{
			return this->m_uPosition;
		}

		void	IMemoryStream::SetPos(const uint32 uPos, const Direction uDirection, const StreamPos uType){
			switch (uType)
			{
			case StreamPos::Begin:		this->m_uPosition = uPos;	break;
			
			case StreamPos::Current:
				if(uDirection == Direction::Forward){
					this->m_uPosition += uPos;
				}
				else {
					this->m_uPosition -= uPos;
				}
				break;

			case StreamPos::End:		
				if(uDirection == Direction::Back){
					this->m_uPosition = this->m_uLength - 1 - uPos;
				}
				break;

			default:
				break;
			}
		}

		void	IMemoryStream::Flush(){
		}

		//==================

		class CMemoryStream : 
			public IMemoryStream
		{
		private:
			Collection::CList<byte>	m_Data;

		public:
			CMemoryStream(const uint32 uLength);

			void	Create(const uint32 uLength);
		};

		CMemoryStream::CMemoryStream(const uint32 uLength) : 
			IMemoryStream()
		{
			this->Create(uLength);
		}

		void	CMemoryStream::Create(const uint32 uLength){
			this->m_Data.Resize(uLength);
			this->m_uLength		= this->m_Data.GetLength();
			this->m_pData		= m_Data.GetPointer();
			this->m_bCanRead	= true;
			this->m_bCanWrite	= true;
		}
	}

	namespace Memory{
		CRefPtr<IO::IMemoryStream>	CreateStream(const uint32 uLength){
			return new IO::CMemoryStream(uLength);
		}
	}
}