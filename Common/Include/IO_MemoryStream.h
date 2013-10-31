#pragma once

#include "IO_Stream.h"

namespace CB{
	namespace IO{
		class COMMON_API IMemoryStream : public IStream{
		protected:
			unsigned char*	m_pData;
			unsigned		m_uPosition;
			unsigned		m_uLength;
			bool			m_bCanWrite;
			bool			m_bCanRead;

			IMemoryStream();
			IMemoryStream(const IMemoryStream& Stream);
		public:
			virtual const bool	CanWrite() const;
			virtual const bool	CanRead() const;

			virtual void	Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements);
			virtual void	Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements);

			virtual void	Read(CRefPtr<IStream> pOutStream, const unsigned uSizeInBytes);
			virtual void	Write(CRefPtr<IStream> pInStream, const unsigned uSizeInBytes);

			virtual const bool	IsEndOfStream() const;		// can be slow
			virtual const bool	IsBeginingOfStream() const;	// can be slow

			virtual const unsigned	GetLength() const;	// it may be slow
			virtual	void			SetPos(const int uPos, const StreamPos uType);
			virtual const unsigned	GetPos() const;
			virtual void	Flush();
		};
	}

	namespace Memory{
		extern CRefPtr<IO::IMemoryStream>	CreateStream(const unsigned uLength);
	}
}