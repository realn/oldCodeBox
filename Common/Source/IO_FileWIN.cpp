#include "../Internal/IO_FileStream.h"
#include "../Include/WindowsErrors.h"

namespace CB{
	CFileStream::CFileStream(const CString& strFilename, const IO::File::AccessType uAccess, const IO::File::OpenAction uAction, const IO::File::ShareType uShare) :
		m_pHandle(0), m_strFilename(strFilename), m_uAccess(uAccess), m_uAction(uAction), m_uShare(uShare){

		if(this->m_strFilename.IsEmpty()){
			throw CB::Exception::CZeroLengthArgumentException(L"strFilename",
				L"Cannot open file with no filename.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		DWORD dwAccess	= 0;
		DWORD dwCreate	= 0;
		DWORD dwShare	= 0;

		switch (uAccess){
		case CB::IO::File::AccessType::ReadOnly:	dwAccess = GENERIC_READ;	break;
		case CB::IO::File::AccessType::WriteOnly:	dwAccess = GENERIC_WRITE;	break;
		case CB::IO::File::AccessType::ReadAndWrite:	dwAccess = GENERIC_READ | GENERIC_WRITE;	break;

		default:
			throw CB::Exception::CInvalidArgumentException(L"uAccess", String::ToString(uAccess),
				L"Invalid file access value.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		switch (uAction)
		{
		case IO::File::OpenAction::Open:			dwCreate	= OPEN_EXISTING;	break;
		case IO::File::OpenAction::Create:			dwCreate	= CREATE_NEW;		break;
		case IO::File::OpenAction::AlwaysOpen:		dwCreate	= OPEN_ALWAYS;		break;
		case IO::File::OpenAction::AlwaysCreate:	dwCreate	= CREATE_ALWAYS;	break;
		default:
			throw CB::Exception::CInvalidArgumentException(L"uAction", String::ToString(uAction),
				L"Invalid file open action value.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		switch (uShare)
		{
		case IO::File::ShareType::None:		dwShare = 0;	break;
		case IO::File::ShareType::WriteOnly:	dwShare = FILE_SHARE_WRITE;	break;
		case IO::File::ShareType::ReadOnly:		dwShare = FILE_SHARE_READ;	break;
		case IO::File::ShareType::ReadAndWrite:	dwShare = FILE_SHARE_READ | FILE_SHARE_WRITE;	break;
		default:
			throw Exception::CInvalidArgumentException(L"uShare", String::ToString(uShare),
				L"Invalid file share type value.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		this->m_pHandle = CreateFileW(this->m_strFilename.ToConst(), dwAccess, dwShare, NULL, dwCreate, FILE_ATTRIBUTE_NORMAL, NULL);
		if(this->m_pHandle == 0 || this->m_pHandle == INVALID_HANDLE_VALUE){
			DWORD uError = GetLastError();
			switch (uError)
			{
			case ERROR_SHARING_VIOLATION:
				throw Exception::CFileSharingException(uShare, uAction, uAccess, strFilename,
					L"Cannot open file because it's shared by another stream.", __FUNCTIONW__, __FILEW__, __LINE__);

			case ERROR_FILE_EXISTS:
				throw Exception::CFileAlreadyExistsException(strFilename, __FUNCTIONW__, __FILEW__, __LINE__);

			case ERROR_FILE_NOT_FOUND:
				throw Exception::CFileNotExistsException(strFilename, __FUNCTIONW__, __FILEW__, __LINE__);

			case ERROR_FILE_READ_ONLY:
				throw Exception::CFileAccessException(uAccess, strFilename,
					L"File is read only.", __FUNCTIONW__, __FILEW__, __LINE__);

			default:
				throw Exception::CFileStreamException(strFilename,
					CWindowsError(uError).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}

	CFileStream::~CFileStream(){
		this->Close();
	}

	const CString&	CFileStream::GetFilename() const{
		return this->m_strFilename;
	}

	const IO::File::AccessType	CFileStream::GetAccessType() const{
		return this->m_uAccess;
	}

	const IO::File::OpenAction	CFileStream::GetOpenAction() const{
		return this->m_uAction;
	}

	const IO::File::ShareType	CFileStream::GetShareType() const{
		return this->m_uShare;
	}

	const bool CFileStream::IsOpen() const{
		return this->m_pHandle != NULL;
	}

	void	CFileStream::Close(){
		if(this->m_pHandle){
			if(!CloseHandle(this->m_pHandle)){
				throw CB::Exception::CFileStreamException(this->m_strFilename,
					L"Error while closing file stream.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			this->m_pHandle = 0;
		}
	}

	const bool	CFileStream::CanRead() const{
		return this->m_uAccess == IO::File::AccessType::ReadOnly || this->m_uAccess == IO::File::AccessType::ReadAndWrite;
	}

	const bool	CFileStream::CanWrite() const{
		return this->m_uAccess == IO::File::AccessType::WriteOnly || this->m_uAccess == IO::File::AccessType::ReadAndWrite;
	}

	void	CFileStream::Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		DWORD dwToRead = uSizeInBytes * uNumberOfElements;
		DWORD dwReaded = 0;

		if(!ReadFile(this->m_pHandle, pData, dwToRead, &dwReaded, NULL)){
			DWORD uError = GetLastError();
			switch (uError){
			case ERROR_INSUFFICIENT_BUFFER:
				throw Exception::CFileStreamException(this->m_strFilename,
					L"Insufficient buffer to read data.", __FUNCTIONW__, __FILEW__, __LINE__);

			default:
				throw CB::Exception::CInvalidFileOperationException(L"Read", CWindowsError(uError).GetMessage(), this->m_strFilename,
					L"Unknown error while reading data from file stream.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}

	void	CFileStream::Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		DWORD dwToWrite	= uSizeInBytes * uNumberOfElements;
		DWORD dwWriten	= 0;

		if(!WriteFile(this->m_pHandle, pData, dwToWrite, &dwWriten, NULL)){
			DWORD uError = GetLastError();
			switch (uError){
			case ERROR_INSUFFICIENT_BUFFER:
				throw CB::Exception::CFileStreamException(this->m_strFilename,
					L"Insufficient buffer to write data.", __FUNCTIONW__, __FILEW__, __LINE__);

			default:
				throw CB::Exception::CInvalidFileOperationException(L"Write", CWindowsError(uError).GetMessage(), this->m_strFilename,
					L"Unknown error while writing data to file stream.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		if(dwToWrite != dwWriten){
			throw CB::Exception::CInvalidFileOperationException(L"Write", L"Bytes written: " + CB::String::FromUInt32(dwWriten), this->m_strFilename,
				L"Invalid number of bytes writen to file stream.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	const bool	CFileStream::IsEndOfStream() const{
		try{
			return this->GetPos() >= this->GetLength();
		}
		catch(CB::Exception::CException& Exception){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"Error while determining end of stream.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}

	const bool	CFileStream::IsBeginingOfStream() const{
		try{
			return this->GetPos() == 0;
		}
		catch(CB::Exception::CException& Exception){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"Error while determining begining of stream.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}

	const unsigned	CFileStream::GetLength() const{
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		DWORD dwSize = GetFileSize(this->m_pHandle, 0);
		if(dwSize == INVALID_FILE_SIZE){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidFileOperationException(L"File Size", CWindowsError(dwError).GetMessage(), this->m_strFilename,
				L"Cannot get file stream size.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		return dwSize;
	}

	void	CFileStream::SetPos(const int uPos, const IO::StreamPos uType){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
		DWORD dwType = 0;

		switch (uType)
		{
		case IO::StreamPos::Begin:		dwType	= FILE_BEGIN;	break;
		case IO::StreamPos::Current:	dwType	= FILE_CURRENT;	break;
		case IO::StreamPos::End:		dwType	= FILE_END;		break;
		default:
			throw CB::Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Unknown position type for file stream.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		DWORD dwPos = SetFilePointer(this->m_pHandle, uPos, NULL, dwType);
		if(dwPos == INVALID_SET_FILE_POINTER){
			DWORD dwError = GetLastError();
			throw Exception::CInvalidFileOperationException(L"File Position", CWindowsError(dwError).GetMessage(), this->m_strFilename,
				L"Cannot set file stream position.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	const unsigned	CFileStream::GetPos() const{
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		DWORD dwPos = SetFilePointer(this->m_pHandle, 0, NULL, FILE_CURRENT);
		if(dwPos == INVALID_SET_FILE_POINTER){
			DWORD dwError = GetLastError();
			throw Exception::CInvalidFileOperationException(L"File Position", CWindowsError(dwError).GetMessage(), this->m_strFilename,
				L"Cannot get file stream position.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		return dwPos;
	}

	void	CFileStream::Flush(){
		if(this->m_pHandle && (this->m_uAccess == IO::File::AccessType::WriteOnly || this->m_uAccess == IO::File::AccessType::ReadAndWrite)){
			FlushFileBuffers(this->m_pHandle);
		}
	}

	void	CFileStream::Read(CRefPtr<IO::IStream> pOutStream, const unsigned uSizeInBytes){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		try{
			Collection::CList<unsigned char> Buffer(uSizeInBytes);
			Memory::SetZeroArray(Buffer);

			this->Read(&Buffer[0], uSizeInBytes, 1);
			pOutStream->Write(Buffer);
		}
		catch(Exception::CException& Exception){
			throw Exception::CFileStreamException(this->m_strFilename,
				L"Error while reading to stream.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}

	void	CFileStream::Write(CRefPtr<IO::IStream> pInStream, const unsigned uSizeInBytes){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		try{
			Collection::CList<unsigned char> Buffer(uSizeInBytes);
			Memory::SetZeroArray(Buffer);

			this->Write(&Buffer[0], uSizeInBytes, 1);
			pInStream->Read(Buffer);
		}
		catch(Exception::CException& Exception){
			throw Exception::CFileStreamException(this->m_strFilename,
				L"Error while writing stream from stream.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}
}