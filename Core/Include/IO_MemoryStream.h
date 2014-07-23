#pragma once

#include "IO_Stream.h"

namespace CB{
	namespace IO{
		class COMMON_API IMemoryStream : 
			public IStream{
		protected:
			byte*	m_pData;
			uint32	m_uPosition;
			uint32	m_uLength;
			bool	m_bCanWrite;
			bool	m_bCanRead;

			IMemoryStream();
			IMemoryStream(const IMemoryStream& Stream);
		public:
			virtual const bool	CanWrite() const override;
			virtual const bool	CanRead() const override;

			virtual void	Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;
			virtual void	Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;

			virtual void	Read(CRefPtr<IStream> pOutStream, const uint32 uSizeInBytes) override;
			virtual void	Write(CRefPtr<IStream> pInStream, const uint32 uSizeInBytes) override;

			virtual const bool	IsEndOfStream() const override;		// can be slow
			virtual const bool	IsBeginingOfStream() const override;	// can be slow

			virtual const uint32	GetLength() const override;	// it may be slow
			virtual	void			SetPos(const uint32 uPos, const Direction uDirection, const StreamPos uType) override;
			virtual const uint32	GetPos() const override;

			virtual void	Flush() override;
		};
	}

	namespace Memory{
		extern CRefPtr<IO::IMemoryStream>	CreateStream(const uint32 uLength);
	}
}