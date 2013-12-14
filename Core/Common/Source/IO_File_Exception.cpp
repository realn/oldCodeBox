#include "../Include/IO_File.h"
#include "../../Common/Include/CBStringEx.h"

namespace CB{
	namespace Exception{
		//	File stream exception
		CFileStreamException::CFileStreamException(const CFileStreamException& Exception) : 
			CStreamException(Exception), 
			m_strFilename(Exception.m_strFilename)
		{
		}

		CFileStreamException::CFileStreamException(const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CStreamException(strMessage, strFunction, strFile, uLine), 
			m_strFilename(strFilename)
		{
		}

		CFileStreamException::CFileStreamException(const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException) : 
			CStreamException(strMessage, strFunction, strFile, uLine, InnerException), 
			m_strFilename(strFilename)
		{
		}

		const CB::CString CFileStreamException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strFilename);

			return String::VarReplace(L"Error while handling file stream of file {0}.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CFileStreamException::CreateCopy() const{
			return new CFileStreamException(*this);
		}

		//	File already exists Exception

		CFileAlreadyExistsException::CFileAlreadyExistsException(const CFileAlreadyExistsException& Exception) : 
			CFileStreamException(Exception)
		{
		}

		CFileAlreadyExistsException::CFileAlreadyExistsException(const CB::CString& strFilename, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CFileStreamException(strFilename, L"", strFunction, strFile, uLine)
		{
		}

		CFileAlreadyExistsException::CFileAlreadyExistsException(const CB::CString& strFilename, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException) : 
			CFileStreamException(strFilename, L"", strFunction, strFile, uLine, InnerException)
		{
		}

		const CB::CString CFileAlreadyExistsException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strFilename);

			return CB::String::VarReplace(L"File {0} already exists.", VarList, true);
		}

		CException*	CFileAlreadyExistsException::CreateCopy() const{
			return new CFileAlreadyExistsException(*this);
		}

		//	File not exists exception

		CFileNotExistsException::CFileNotExistsException(const CFileNotExistsException& Exception) : 
			CFileStreamException(Exception)
		{
		}

		CFileNotExistsException::CFileNotExistsException(const CB::CString& strFilename, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CFileStreamException(strFilename, L"", strFunction, strFile, uLine)
		{
		}

		CFileNotExistsException::CFileNotExistsException(const CB::CString& strFilename, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException) : 
			CFileStreamException(strFilename, L"", strFunction, strFile, uLine, InnerException)
		{
		}

		const CB::CString CFileNotExistsException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strFilename);

			return CB::String::VarReplace(L"File {0} doesn't exist.", VarList, true);
		}

		CException*	CFileNotExistsException::CreateCopy() const{
			return new CFileNotExistsException(*this);
		}

		//	File access exception

		CFileAccessException::CFileAccessException(const CFileAccessException& Exception) : 
			CFileStreamException(Exception), 
			m_uType(Exception.m_uType)
		{
		}

		CFileAccessException::CFileAccessException(const IO::File::AccessType uType, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CFileStreamException(strFilename, strMessage, strFunction, strFile, uLine)
			, m_uType(uType)
		{
		}

		CFileAccessException::CFileAccessException(const IO::File::AccessType uType, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException) : 
			CFileStreamException(strFilename, strMessage, strFunction, strFile, uLine, InnerException), 
			m_uType(uType)
		{
		}

		const CB::CString CFileAccessException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strFilename);
			VarList.Add(String::ToString(this->m_uType));

			return String::VarReplace(L"Access {1} denied for file stream {0}.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CFileAccessException::CreateCopy() const{
			return new CFileAccessException(*this);
		}

		//	File open exception

		CFileOpenException::CFileOpenException(const CFileOpenException& Exception) : 
			CFileAccessException(Exception)
		{
		}

		CFileOpenException::CFileOpenException(const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CFileAccessException(uType, strFilename, strMessage, strFunction, strFile, uLine), 
			m_uAction(uAction)
		{
		}

		CFileOpenException::CFileOpenException(const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException) : 
			CFileAccessException(uType, strFilename, strMessage, strFunction, strFile, uLine, InnerException), 
			m_uAction(uAction)
		{
		}

		const CB::CString CFileOpenException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strFilename);
			VarList.Add(String::ToString(this->m_uType));
			VarList.Add(String::ToString(this->m_uAction));

			return String::VarReplace(L"Opening of file {0} failed with access {1} for action {2}.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CFileOpenException::CreateCopy() const{
			return new CFileOpenException(*this);
		}

		//	File sharing exception

		CFileSharingException::CFileSharingException(const CFileSharingException& Exception) : 
			CFileOpenException(Exception), 
			m_uShare(Exception.m_uShare)
		{
		}

		CFileSharingException::CFileSharingException(const IO::File::ShareType uShare, const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CFileOpenException(uAction, uType, strFilename, strMessage, strFunction, strFile, uLine), 
			m_uShare(uShare)
		{
		}

		CFileSharingException::CFileSharingException(const IO::File::ShareType uShare, const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException) : 
			CFileOpenException(uAction, uType, strFilename, strMessage, strFunction, strFile, uLine, InnerException), 
			m_uShare(uShare)
		{
		}

		const CB::CString CFileSharingException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strFilename);
			VarList.Add(String::ToString(this->m_uType));
			VarList.Add(String::ToString(this->m_uAction));
			VarList.Add(String::ToString(this->m_uShare));

			return CB::String::VarReplace(L"File {0} encountered sharing exception for {3} - cannot access with {1} and action {2}.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CFileSharingException::CreateCopy() const{
			return new CFileSharingException(*this);
		}

		//	Invalid file operation exception

		CInvalidFileOperationException::CInvalidFileOperationException(const CInvalidFileOperationException& Exception) : 
			CFileStreamException(Exception), 
			m_strOperation(Exception.m_strOperation), 
			m_strValue(Exception.m_strValue)
		{
		}

		CInvalidFileOperationException::CInvalidFileOperationException(const CB::CString& strOperation, const CB::CString& strValue, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CFileStreamException(strFilename, strMessage, strFunction, strFile, uLine), 
			m_strOperation(strOperation), 
			m_strValue(strValue)
		{
		}

		CInvalidFileOperationException::CInvalidFileOperationException(const CB::CString& strOperation, const CB::CString& strValue, const CB::CString& strFilename, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException) : 
			CFileStreamException(strFilename, strMessage, strFunction, strFile, uLine, InnerException), 
			m_strOperation(strOperation), 
			m_strValue(strValue)
		{
		}

		const CB::CString CInvalidFileOperationException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strFilename);
			VarList.Add(this->m_strOperation);
			VarList.Add(this->m_strValue);

			return CB::String::VarReplace(L"Operation {1} on file {0} failed with invalid value {2}.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CInvalidFileOperationException::CreateCopy() const{
			return new CInvalidFileOperationException(*this);
		}
	}
}