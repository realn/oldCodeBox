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

			virtual void	SetPos(const int iPos);	// default - from begining
			virtual	void	SetPos(const int iPos, const StreamPos uType) = 0;

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


		class COMMON_API CTextWriter : public CStreamWriter{
		public:
			CTextWriter(const CRefPtr<IStream> pStream);
			CTextWriter(const IStreamWrapper& Wrapper);

			void	WriteText(const CString& strValue);	// string without 0
			void	WriteTextANSI(const CString& strValue);
			void	WriteTextUTF8(const CString& strValue);
			void	WriteLine(const CString& strValue); // string with new line int8 (windows: return and new line), without 0
			void	WriteLineANSI(const CString& strValue);
			void	WriteLineUTF8(const CString& strValue);

		private:
			const CTextWriter&	operator=(const CTextWriter& Writer);
		};

		class COMMON_API CStreamReader : public IStreamWrapper{
		public:
			CStreamReader(const CRefPtr<IStream> pStream);
			CStreamReader(const IStreamWrapper& Wrapper);

			void	Read(int8& chValue);
			void	Read(int16& sValue);
			void	Read(int32& iValue);
			void	Read(int64& iValue);
			void	Read(float32& fValue);
			void	Read(float64& dValue);
			void	Read(CString& strValue);	// first 4 byte length, then string without 0
			void	Read(uint8& uchValue);
			void	Read(uint16& usValue);
			void	Read(uint32& uValue);
			void	Read(uint64& uValue);

			const int8				ReadInt8();
			const int16				ReadInt16();
			const int32				ReadInt32();
			const int64			ReadInt64();
			const float32				Readfloat3232();
			const float64			Readfloat3264();
			const CString		ReadString();	// reads 4 bytes of len without 0, then rest of string
			const uint8		ReadUInt8();
			const uint16	ReadUInt16();
			const uint32		ReadUInt32();
			const uint64	ReadUInt64();

		private:
			const CStreamReader&	operator=(const CStreamReader& Reader);
		};

		class COMMON_API CTextReader : public CStreamReader{
		public:
			CTextReader(const CRefPtr<IStream> pStream);
			CTextReader(const IStreamWrapper& Wrapper);

			const CString		ReadText();	// reads text until int8 0 or end of stream
			const CString		ReadTextANSI();
			const CString		ReadTextUTF8();
			const CString		ReadLine();	// reads text until int8 new line (windows: return and new line) or end of stream
			const CString		ReadLineANSI();
			const CString		ReadLineUTF8();

		private:
			const CTextReader&	operator=(const CTextReader& Reader);
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
		extern COMMON_API	CString	ToString(const IO::StreamPos uType);
	}
}
