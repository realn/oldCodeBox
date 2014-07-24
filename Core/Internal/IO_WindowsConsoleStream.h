#pragma once

#include "../Include/IO_OSConsoleStream.h"
#include "../Include/Manage_Singleton.h"

#include <Windows.h>

namespace CB{
	class CWindowsConsoleStream : 
		public IO::IOSConsoleStream, 
		public Manage::CRefSingleton<CWindowsConsoleStream>
	{
	private:
		HANDLE	m_hConsole;

	public:
		CWindowsConsoleStream();
		~CWindowsConsoleStream();

		const bool	CanRead() const override;
		const bool	CanWrite() const override;

		void	Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;
		void	Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;

		void	Read(CRefPtr<IStream> pOutStream, const uint32 uSizeInBytes) override;
		void	Write(CRefPtr<IStream> pInStream, const uint32 uSizeInBytes) override;

		const bool	IsEndOfStream() const override;			// can be slow
		const bool	IsBeginingOfStream() const override;	// can be slow
		const bool	IsEmpty() const override;

		const uint32	GetLength() const override;	// it may be slow

		void	SetPos(const uint32 uPos, const IO::Direction uDirection, const IO::StreamPos uType) override;

		const uint32	GetPos() const override;

		void	Flush() override;
	};
}