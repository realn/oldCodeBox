#pragma once

#include "IO_StreamWrapper.h"

namespace CB{
	namespace IO{
		class COMMON_API CStreamWriter : 
			public IStreamWrapper
		{
		public:
			CStreamWriter(const CRefPtr<IStream> pStream);
			CStreamWriter(const IStreamWrapper& Wrapper);

			void	Write(const int8 chValue);
			void	Write(const int16 sValue);
			void	Write(const int32 iValue);
			void	Write(const int64 iValue);
			void	Write(const float32 fValue);
			void	Write(const float64 dValue);
			void	Write(const CString& strValue);	// first 4 byte length, then string without 0
			void	Write(const uint8 uchValue);
			void	Write(const uint16 usValue);
			void	Write(const uint32 uValue);
			void	Write(const uint64 uValue);
			void	Write(const void* pData, const uint32 uSizeInBytes);

			template<typename _Type>
			void	Write(const Collection::IPacked<_Type>& Data){
				this->Write(Data.GetPointer(), Data.GetSizeInBytes());
			}
			
		private:
			const CStreamWriter&	operator=(const CStreamWriter& Writer);
		};
	}
}