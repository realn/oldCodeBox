#pragma once

#include "../Include/IO_File.h"
#include "WinPlatform.h"

namespace CB{
	class CFileStreamWIN : 
		public IO::File::IFileStream
	{
	private:
		HANDLE			m_pHandle;
		const CString	m_strFilename;

		const IO::File::AccessType	m_uAccess;
		const IO::File::OpenAction	m_uAction;
		const IO::File::ShareType	m_uShare;

	public:
		CFileStreamWIN(const CString& strFilename, const IO::File::AccessType uAccess, const IO::File::OpenAction uAction, const IO::File::ShareType uShare);
		~CFileStreamWIN();

		const CString&	GetFilename() const override;

		const IO::File::AccessType	GetAccessType() const override;
		const IO::File::OpenAction	GetOpenAction() const override;
		const IO::File::ShareType	GetShareType() const override;

		const bool	IsOpen() const override;

		void	Close() override;

		const bool	CanRead() const override;
		const bool	CanWrite() const override;

		void	Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;
		void	Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements) override;

		void	Read(CRefPtr<IO::IStream> pOutStream, const uint32 uSizeInBytes) override;
		void	Write(CRefPtr<IO::IStream> pInStream, const uint32 uSizeInBytes) override;

		const bool	IsEndOfStream() const override;
		const bool	IsBeginingOfStream() const override;

		const uint32	GetLength() const override;

		void	SetPos(const uint32 uPos, const IO::Direction uDirection, const IO::StreamPos uType) override;

		const uint32	GetPos() const override;

		void	Flush() override;
	};
}