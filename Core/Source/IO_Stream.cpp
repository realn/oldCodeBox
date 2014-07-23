#include "stdafx.h"
#include "../Include/IO_Stream.h"
#include "../Include/SmartPointers_RefPtr.h"

namespace CB{
	namespace IO{
		const bool	IStream::CanRead() const{
			return true;
		}

		const bool	IStream::CanWrite() const{
			return true;
		}

		void	IStream::Read(void* pData, const uint32 uSizeInBytes){
			this->Read(pData, uSizeInBytes, 1);
		}

		void	IStream::Write(const void* pData, const uint32 uSizeInBytes){
			this->Write(pData, uSizeInBytes, 1);
		}

		const uint32	IStream::GetLengthLeft() const {
			return this->GetLength() - this->GetPos();
		}

		const bool	IStream::IsEmpty() const{
			return IsBeginingOfStream() && IsEndOfStream();
		}

		void	IStream::SetPos(const uint32 uPos){
			this->SetPos(uPos, IO::Direction::Forward, CB::IO::StreamPos::Begin);
		}

		void	IStream::Read(CRefPtr<IStream> pStream){
			this->Read(pStream, pStream->GetLength());
		}

		void	IStream::Write(CRefPtr<IStream> pStream){
			this->Write(pStream, pStream->GetLength());
		}
	}

	namespace String{
		const CString	ToString(const IO::StreamPos uType){
			switch (uType){
			case IO::StreamPos::Begin:		return L"Begin";
			case IO::StreamPos::Current:	return L"Current";
			case IO::StreamPos::End:		return L"End";
			default:
				return FromUInt32((uint32)uType);
			}
		}

		const CString	ToString(const IO::Direction uDirection){
			switch (uDirection)
			{
			case IO::Direction::Forward:	return L"Forward";
			case IO::Direction::Back:		return L"Back";

			default:
				return FromUInt32((uint32)uDirection);
			}
		}
	}
}