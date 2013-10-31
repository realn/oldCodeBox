#include "../Include/IO_Stream.h"

namespace CB{
	namespace IO{
		const bool	IStream::CanRead() const{
			return true;
		}

		const bool	IStream::CanWrite() const{
			return true;
		}

		void	IStream::Read(void* pData, const unsigned uSizeInBytes){
			this->Read(pData, uSizeInBytes, 1);
		}

		void	IStream::Write(const void* pData, const unsigned uSizeInBytes){
			this->Write(pData, uSizeInBytes, 1);
		}

		const bool	IStream::IsEmpty() const{
			return IsBeginingOfStream() && IsEndOfStream();
		}

		void	IStream::SetPos(const int iPos){
			this->SetPos(iPos, CB::IO::StreamPos::Begin);
		}

		void	IStream::Read(CRefPtr<IStream> pStream){
			this->Read(pStream, pStream->GetLength());
		}

		void	IStream::Write(CRefPtr<IStream> pStream){
			this->Write(pStream, pStream->GetLength());
		}
	}

	namespace String{
		CString	ToString(const IO::StreamPos uType){
			switch (uType)
			{
			case IO::StreamPos::Begin:	return L"Begin";
			case IO::StreamPos::Current:	return L"Current";
			case IO::StreamPos::End:	return L"End";
			default:
				return FromUInt32((unsigned)uType);
			}
		}
	}
}