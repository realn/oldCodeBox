#include "stdafx.h"
#include "../Internal/IO_FileStreamWIN.h"
#include "../Include/WindowsErrors.h"
#include "../Include/Collection_List.h"
#include "../Include/IO_File_Exceptions.h"
#include "../Include/SmartPointers_RefPtr.h"

namespace CB{
	CFileStreamWIN::CFileStreamWIN(const CString& strFilename, const IO::File::AccessType uAccess, const IO::File::OpenAction uAction, const IO::File::ShareType uShare) :
		m_pHandle(0), 
		m_strFilename(strFilename), 
		m_uAccess(uAccess), 
		m_uAction(uAction), 
		m_uShare(uShare){

		if(this->m_strFilename.IsEmpty()){
			throw CB::Exception::CZeroLengthArgumentException(L"strFilename", L"Cannot open file with no filename.", CR_INFO());
		}

		DWORD dwAccess	= 0;
		DWORD dwCreate	= 0;
		DWORD dwShare	= 0;

		switch (uAccess){
		case CB::IO::File::AccessType::ReadOnly:		dwAccess = GENERIC_READ;	break;
		case CB::IO::File::AccessType::WriteOnly:		dwAccess = GENERIC_WRITE;	break;
		case CB::IO::File::AccessType::ReadAndWrite:	dwAccess = GENERIC_READ | GENERIC_WRITE;	break;

		default:
			throw CB::Exception::CInvalidArgumentException(L"uAccess", String::ToString(uAccess),
				L"Invalid file access value.", CR_INFO());
		}

		switch (uAction)
		{
		case IO::File::OpenAction::Open:			dwCreate = OPEN_EXISTING;	break;
		case IO::File::OpenAction::Create:			dwCreate = CREATE_NEW;		break;
		case IO::File::OpenAction::AlwaysOpen:		dwCreate = OPEN_ALWAYS;		break;
		case IO::File::OpenAction::AlwaysCreate:	dwCreate = CREATE_ALWAYS;	break;
		default:
			throw CB::Exception::CInvalidArgumentException(L"uAction", String::ToString(uAction),
				L"Invalid file open action value.", CR_INFO());
		}

		switch (uShare)
		{
		case IO::File::ShareType::None:			dwShare = 0;	break;
		case IO::File::ShareType::WriteOnly:	dwShare = FILE_SHARE_WRITE;	break;
		case IO::File::ShareType::ReadOnly:		dwShare = FILE_SHARE_READ;	break;
		case IO::File::ShareType::ReadAndWrite:	dwShare = FILE_SHARE_READ | FILE_SHARE_WRITE;	break;
		default:
			throw Exception::CInvalidArgumentException(L"uShare", String::ToString(uShare),
				L"Invalid file share type value.", CR_INFO());
		}

		this->m_pHandle = CreateFileW(this->m_strFilename.GetPointer(), dwAccess, dwShare, NULL, dwCreate, FILE_ATTRIBUTE_NORMAL, NULL);
		if(this->m_pHandle == 0 || this->m_pHandle == INVALID_HANDLE_VALUE){
			DWORD uError = GetLastError();
			switch (uError)
			{
			case ERROR_SHARING_VIOLATION:
				throw Exception::CFileSharingException(uShare, uAction, uAccess, strFilename,
					L"Cannot open file because it's shared by another stream.", CR_INFO());

			case ERROR_FILE_EXISTS:
				throw Exception::CFileAlreadyExistsException(strFilename, CR_INFO());

			case ERROR_FILE_NOT_FOUND:
				throw Exception::CFileNotExistsException(strFilename, CR_INFO());

			case ERROR_FILE_READ_ONLY:
				throw Exception::CFileAccessException(uAccess, strFilename,
					L"File is read only.", CR_INFO());

			default:
				throw Exception::CFileStreamException(strFilename,
					CWindowsError(uError).GetMessage(), CR_INFO());
			}
		}
	}

	CFileStreamWIN::~CFileStreamWIN(){
		try{
			this->Close();
		}
		catch(Exception::CException&){}
	}

	const CString&	CFileStreamWIN::GetFilename() const{
		return this->m_strFilename;
	}

	const IO::File::AccessType	CFileStreamWIN::GetAccessType() const{
		return this->m_uAccess;
	}

	const IO::File::OpenAction	CFileStreamWIN::GetOpenAction() const{
		return this->m_uAction;
	}

	const IO::File::ShareType	CFileStreamWIN::GetShareType() const{
		return this->m_uShare;
	}

	const bool CFileStreamWIN::IsOpen() const{
		return this->m_pHandle != NULL;
	}

	void	CFileStreamWIN::Close(){
		if(this->m_pHandle){
			if(!CloseHandle(this->m_pHandle)){
				throw CB::Exception::CFileStreamException(this->m_strFilename,
					L"Error while closing file stream.", CR_INFO());
			}
			this->m_pHandle = 0;
		}
	}

	const bool	CFileStreamWIN::CanRead() const{
		return this->m_uAccess == IO::File::AccessType::ReadOnly || this->m_uAccess == IO::File::AccessType::ReadAndWrite;
	}

	const bool	CFileStreamWIN::CanWrite() const{
		return this->m_uAccess == IO::File::AccessType::WriteOnly || this->m_uAccess == IO::File::AccessType::ReadAndWrite;
	}

	void	CFileStreamWIN::Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", CR_INFO());
		}

		DWORD dwToRead = uSizeInBytes * uNumberOfElements;
		DWORD dwReaded = 0;

		if(!ReadFile(this->m_pHandle, pData, dwToRead, &dwReaded, NULL)){
			DWORD uError = GetLastError();
			switch (uError){
			case ERROR_INSUFFICIENT_BUFFER:
				throw Exception::CFileStreamException(this->m_strFilename,
					L"Insufficient buffer to read data.", CR_INFO());

			default:
				throw CB::Exception::CInvalidFileOperationException(L"Read", CWindowsError(uError).GetMessage(), this->m_strFilename,
					L"Unknown error while reading data from file stream.", CR_INFO());
			}
		}
	}

	void	CFileStreamWIN::Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", CR_INFO());
		}

		DWORD dwToWrite	= uSizeInBytes * uNumberOfElements;
		DWORD dwWriten	= 0;

		if(!WriteFile(this->m_pHandle, pData, dwToWrite, &dwWriten, NULL)){
			DWORD uError = GetLastError();
			switch (uError){
			case ERROR_INSUFFICIENT_BUFFER:
				throw CB::Exception::CFileStreamException(this->m_strFilename,
					L"Insufficient buffer to write data.", CR_INFO());

			default:
				throw CB::Exception::CInvalidFileOperationException(L"Write", CWindowsError(uError).GetMessage(), this->m_strFilename,
					L"Unknown error while writing data to file stream.", CR_INFO());
			}
		}

		if(dwToWrite != dwWriten){
			throw CB::Exception::CInvalidFileOperationException(L"Write", L"Bytes written: " + CB::String::FromUInt32(dwWriten), this->m_strFilename,
				L"Invalid number of bytes writen to file stream.", CR_INFO());
		}
	}

	const bool	CFileStreamWIN::IsEndOfStream() const{
		try{
			return this->GetPos() >= this->GetLength();
		}
		catch(CB::Exception::CException& Exception){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"Error while determining end of stream.", CR_INFO(), Exception);
		}
	}

	const bool	CFileStreamWIN::IsBeginingOfStream() const{
		try{
			return this->GetPos() == 0;
		}
		catch(CB::Exception::CException& Exception){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"Error while determining begining of stream.", CR_INFO(), Exception);
		}
	}

	const uint32	CFileStreamWIN::GetLength() const{
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", CR_INFO());
		}

		DWORD dwSize = GetFileSize(this->m_pHandle, 0);
		if(dwSize == INVALID_FILE_SIZE){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidFileOperationException(L"File Size", CWindowsError(dwError).GetMessage(), this->m_strFilename,
				L"Cannot get file stream size.", CR_INFO());
		}

		return dwSize;
	}

	void	CFileStreamWIN::SetPos(const uint32 uPos, const IO::Direction uDirection, const IO::StreamPos uType){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", CR_INFO());
		}
		DWORD dwType = 0;

		switch (uType)
		{
		case IO::StreamPos::Begin:		dwType	= FILE_BEGIN;	break;
		case IO::StreamPos::Current:	dwType	= FILE_CURRENT;	break;
		case IO::StreamPos::End:		dwType	= FILE_END;		break;
		default:
			throw CB::Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Unknown position type for file stream.", CR_INFO());
		}

		LONG iPosition = (LONG)uPos * (uDirection == IO::Direction::Forward ? 1 : -1);

		DWORD dwPos = SetFilePointer(this->m_pHandle, iPosition, NULL, dwType);
		if(dwPos == INVALID_SET_FILE_POINTER){
			DWORD dwError = GetLastError();
			throw Exception::CInvalidFileOperationException(L"File Position", CWindowsError(dwError).GetMessage(), this->m_strFilename,
				L"Cannot set file stream position.", CR_INFO());
		}
	}

	const uint32	CFileStreamWIN::GetPos() const{
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", CR_INFO());
		}

		DWORD dwPos = SetFilePointer(this->m_pHandle, 0, NULL, FILE_CURRENT);
		if(dwPos == INVALID_SET_FILE_POINTER){
			DWORD dwError = GetLastError();
			throw Exception::CInvalidFileOperationException(L"File Position", CWindowsError(dwError).GetMessage(), this->m_strFilename,
				L"Cannot get file stream position.", CR_INFO());
		}

		return dwPos;
	}

	void	CFileStreamWIN::Flush(){
		if(this->m_pHandle && (this->m_uAccess == IO::File::AccessType::WriteOnly || this->m_uAccess == IO::File::AccessType::ReadAndWrite)){
			FlushFileBuffers(this->m_pHandle);
		}
	}

	void	CFileStreamWIN::Read(CRefPtr<IO::IStream> pOutStream, const uint32 uSizeInBytes){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", CR_INFO());
		}

		try{
			Collection::CList<byte> Buffer(uSizeInBytes);
			Memory::SetZeroArray(Buffer);

			dynamic_cast<IO::IStream*>(this)->Read(Buffer);
			pOutStream->Write(Buffer);
		}
		catch(Exception::CException& Exception){
			throw Exception::CFileStreamException(this->m_strFilename,
				L"Error while reading to stream.", CR_INFO(), Exception);
		}
	}

	void	CFileStreamWIN::Write(CRefPtr<IO::IStream> pInStream, const uint32 uSizeInBytes){
		if(!this->IsOpen()){
			throw CB::Exception::CFileStreamException(this->m_strFilename,
				L"File stream already closed.", CR_INFO());
		}

		try{
			Collection::CList<byte> Buffer(uSizeInBytes);
			Memory::SetZeroArray(Buffer);

			pInStream->Read(Buffer);
			dynamic_cast<IO::IStream*>(this)->Write(Buffer);
		}
		catch(Exception::CException& Exception){
			throw Exception::CFileStreamException(this->m_strFilename,
				L"Error while writing stream from stream.", CR_INFO(), Exception);
		}
	}
}