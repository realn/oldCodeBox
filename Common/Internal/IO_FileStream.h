#pragma once

#include "../Include/IO_File.h"
#include "WinPlatform.h"

namespace CB{
	class CFileStream : public IO::File::IFileStream{
	private:
		HANDLE		m_pHandle;
		CString		m_strFilename;

		IO::File::AccessType	m_uAccess;
		IO::File::OpenAction	m_uAction;
		IO::File::ShareType		m_uShare;

	public:
		CFileStream(const CString& strFilename, const IO::File::AccessType uAccess, const IO::File::OpenAction uAction, const IO::File::ShareType uShare);
		~CFileStream();

		const CString&	GetFilename() const override;

		const IO::File::AccessType	GetAccessType() const override;
		const IO::File::OpenAction	GetOpenAction() const override;
		const IO::File::ShareType	GetShareType() const override;

		const bool	IsOpen() const override;

		void	Close() override;

		const bool	CanRead() const override;
		const bool	CanWrite() const override;

		void	Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements) override;
		void	Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements) override;

		void	Read(CRefPtr<IO::IStream> pOutStream, const unsigned uSizeInBytes) override;
		void	Write(CRefPtr<IO::IStream> pInStream, const unsigned uSizeInBytes) override;

		const bool	IsEndOfStream() const override;
		const bool	IsBeginingOfStream() const override;

		const unsigned	GetLength() const override;

		void	SetPos(const int uPos, const CB::IO::StreamPos uType) override;

		const unsigned GetPos() const override;

		void	Flush() override;
	};
}