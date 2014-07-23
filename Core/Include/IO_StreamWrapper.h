#pragma once

#include "IO_Stream.h"
#pragma warning(disable : 4251)

namespace CB{
	namespace IO{
		class COMMON_API IStreamWrapper{
		protected:
			CRefPtr<IStream>	m_pStream;

		public:
			virtual ~IStreamWrapper();
			const CRefPtr<IStream>	GetStream() const;
			CRefPtr<IStream>		GetStream();

			virtual void	Process(int8& Value) = 0;
			virtual void	Process(int16& Value) = 0;
			virtual void	Process(int32& Value) = 0;
			virtual void	Process(int64& Value) = 0;
			virtual void	Process(float32& Value) = 0;
			virtual void	Process(float64& Value) = 0;
			virtual void	Process(uint8& Value) = 0;
			virtual void	Process(uint16& Value) = 0;
			virtual void	Process(uint32& Value) = 0;
			virtual void	Process(uint64& Value) = 0;
			virtual void	Process(CString& Value) = 0;

		protected:
			IStreamWrapper(const CRefPtr<IStream> pStream);
			IStreamWrapper(const IStreamWrapper& Wrapper);
		};
	}
}