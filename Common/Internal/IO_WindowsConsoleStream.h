#pragma once

#include "../Include/IO_OSConsoleStream.h"
#include "../../Common/Include/Manage_Singleton.h"
#include "WinPlatform.h"

namespace CB{
	class CWindowsConsoleStream : public IO::IOSConsoleStream, public Manage::CRefSingleton<CWindowsConsoleStream>{
	private:
		HANDLE	m_hConsole;

	public:
		CWindowsConsoleStream();
		~CWindowsConsoleStream();

		const bool	CanRead() const override;
		const bool	CanWrite() const override;

		void	Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements) override;
		void	Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements) override;

		void	Read(CRefPtr<IStream> pOutStream, const unsigned uSizeInBytes) override;
		void	Write(CRefPtr<IStream> pInStream, const unsigned uSizeInBytes) override;

		const bool	IsEndOfStream() const override;			// can be slow
		const bool	IsBeginingOfStream() const override;	// can be slow
		const bool	IsEmpty() const override;

		const unsigned	GetLength() const override;	// it may be slow

		void	SetPos(const int uPos, const IO::StreamPos uType) override;

		const unsigned	GetPos() const override;

		void	Flush() override;
	};
}