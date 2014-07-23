#pragma once

#include "IO_StreamWrapper.h"

namespace CB{
	namespace IO{
		class COMMON_API CStreamReader : 
			public IStreamWrapper
		{
		public:
			CStreamReader(const CRefPtr<IStream> pStream);
			CStreamReader(const IStreamWrapper& Wrapper);

			void	Process(int8& Value) override;
			void	Process(int16& Value) override;
			void	Process(int32& Value) override;
			void	Process(int64& Value) override;
			void	Process(float32& Value) override;
			void	Process(float64& Value) override;
			void	Process(uint8& Value) override;
			void	Process(uint16& Value) override;
			void	Process(uint32& Value) override;
			void	Process(uint64& Value) override;
			void	Process(CString& Value) override;

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

			const int8		ReadInt8();
			const int16		ReadInt16();
			const int32		ReadInt32();
			const int64		ReadInt64();
			const float32	ReadFloat32();
			const float64	ReadFloat64();
			const CString	ReadString();	// reads 4 bytes of len without 0, then rest of string
			const uint8		ReadUInt8();
			const uint16	ReadUInt16();
			const uint32	ReadUInt32();
			const uint64	ReadUInt64();

		private:
			const CStreamReader&	operator=(const CStreamReader& Reader);
		};
	}
}