#pragma once

#include "IO_Stream.h"

namespace CB{
	namespace IO{
		class COMMON_API IStreamWrapper{
		protected:
			CRefPtr<IStream>	m_pStream;

		public:
			virtual ~IStreamWrapper();
			const CRefPtr<IStream>	GetStream() const;
			CRefPtr<IStream>		GetStream();

		protected:
			IStreamWrapper(const CRefPtr<IStream> pStream);
			IStreamWrapper(const IStreamWrapper& Wrapper);
		};
	}
}