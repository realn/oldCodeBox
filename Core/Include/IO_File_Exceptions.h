#pragma once

#include "IO_Stream_Exceptions.h"
#include "IO_File_Defs.h"

namespace CB{
	namespace Exception{
		class COMMON_API CFileStreamException : 
			public CStreamException
		{
		protected:
			CString	m_strFilename;

		public:
			CFileStreamException(const CFileStreamException& Exception);
			CFileStreamException(const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CFileStreamException(const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CFileNotExistsException : 
			public CFileStreamException
		{
		public:
			CFileNotExistsException(const CFileNotExistsException& Exception);
			CFileNotExistsException(const CString& strFilename, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CFileNotExistsException(const CString& strFilename, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CFileAlreadyExistsException : 
			public CFileStreamException
		{
		public:
			CFileAlreadyExistsException(const CFileAlreadyExistsException& Exception);
			CFileAlreadyExistsException(const CString& strFilename, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CFileAlreadyExistsException(const CString& strFilename, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CFileAccessException : 
			public CFileStreamException
		{
		protected:
			IO::File::AccessType	m_uType;

		public:
			CFileAccessException(const CFileAccessException& Exception);
			CFileAccessException(const IO::File::AccessType uType, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CFileAccessException(const IO::File::AccessType uType, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CFileOpenException : 
			public CFileAccessException
		{
		protected:
			IO::File::OpenAction	m_uAction;

		public:
			CFileOpenException(const CFileOpenException& Exception);
			CFileOpenException(const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CFileOpenException(const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CFileSharingException : 
			public CFileOpenException
		{
		protected:
			IO::File::ShareType	m_uShare;

		public:
			CFileSharingException(const CFileSharingException& Exception);
			CFileSharingException(const IO::File::ShareType uShare, const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CFileSharingException(const IO::File::ShareType uShare, const IO::File::OpenAction uAction, const IO::File::AccessType uType, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CInvalidFileOperationException : 
			public CFileStreamException
		{
		protected:
			CString	m_strOperation;
			CString m_strValue;

		public:
			CInvalidFileOperationException(const CInvalidFileOperationException& Exception);
			CInvalidFileOperationException(const CString& strOperation, const CString& strValue, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CInvalidFileOperationException(const CString& strOperation, const CString& strValue, const CString& strFilename, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};
	}
}