#pragma once

#include "Macros.h"
#include "Ref.h"
#include "Collection_Interface.h"
#include "SmartPointers_RefPtr.h"

namespace CB{
	namespace IO{
		enum class StreamPos : uint32{
			Current = 0,
			Begin,
			End,
		};

		enum class Direction{
			Forward,
			Back
		};

		class COMMON_API IStream : 
			public virtual IRef
		{
		public:
			virtual const bool	CanWrite() const;
			virtual const bool	CanRead() const;

			virtual void	Read(void* pOutData, const uint32 uSizeInBytes);
			virtual void	Read(void* pOutData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) = 0;
			virtual void	Write(const void* pInData, const uint32 uSizeInBytes);
			virtual void	Write(const void* pInData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) = 0;

			virtual const bool	IsEndOfStream() const = 0;		// can be slow
			virtual const bool	IsBeginingOfStream() const = 0;	// can be slow
			virtual const bool	IsEmpty() const;

			virtual const uint32	GetLength() const = 0;	// it may be slow

			virtual void	SetPos(const uint32 uPos);	// default - from begining
			virtual	void	SetPos(const uint32 uPos, const Direction uDirection, const StreamPos uType) = 0;

			virtual const uint32	GetPos() const = 0; // from stream begining

			virtual void	Flush() = 0;

			virtual void	Read(CRefPtr<IStream> pOutStream);
			virtual void	Read(CRefPtr<IStream> pOutStream, const uint32 uSizeInBytes) = 0;
			virtual void	Write(CRefPtr<IStream> pInStream);
			virtual void	Write(CRefPtr<IStream> pInStream, const uint32 uSizeInBytes) = 0;

			template<typename _Type>
			void	Read(Collection::IPacked<_Type>& Array){
				this->Read(Array.GetPointer(), sizeof(_Type), Array.GetLength());
			}
			template<typename _Type>
			void	Read(_Type& Value){
				this->Read(&Value, sizeof(_Type), 1);
			}
			template<typename _Type>
			void	Read(_Type* pValue, const uint32 uNumberOfItems){
				this->Read(pValue, sizeof(_Type), uNumberOfItems);
			}

			template<typename _Type>
			void	Write(const Collection::IPacked<_Type>& Array){
				this->Write(Array.GetPointer(), sizeof(_Type), Array.GetLength());
			}
			template<typename _Type>
			void	Write(const _Type& Value){
				this->Write(&Value, sizeof(_Type), 1);
			}
			template<typename _Type>
			void	Write(const _Type* pValue, const uint32 uNumberOfItems){
				this->Write(pValue, sizeof(_Type), uNumberOfItems);
			}
		};
	}

	namespace Exception{
		class COMMON_API CStreamException : public CException{
		public:
			CStreamException(const CStreamException& Exception);
			CStreamException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CStreamException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException);

			virtual CException*	CreateCopy() const;
		};
	}

	namespace String{
		extern COMMON_API	const CString	ToString(const IO::StreamPos uType);
		extern COMMON_API	const CString	ToString(const IO::Direction uDir);
	}
}
