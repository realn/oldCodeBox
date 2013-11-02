#pragma once

#include "Macros.h"
#include "Types.h"
#include "IO_Stream.h"

namespace CB{
	namespace IO{
		namespace File{
			enum class AccessType{
				ReadOnly,
				WriteOnly,
				ReadAndWrite,
			};
			enum class OpenAction{
				Open,			// Open, throw if not exists
				Create,			// Create empty, throw if exists
				AlwaysOpen,		// Open, if not exists - create empty
				AlwaysCreate	// Create, if exists - wipe and overwrite
			};
			enum class ShareType{
				None,
				ReadOnly,
				WriteOnly,
				ReadAndWrite
			};

			class IFileStream : 
				public IStream
			{
			public:
				virtual const CString&		GetFilename() const = 0;
				virtual const AccessType	GetAccessType() const = 0;
				virtual const OpenAction	GetOpenAction() const = 0;
				virtual const ShareType		GetShareType() const = 0;

				virtual const bool	IsOpen() const = 0;

				virtual void	Close() = 0;
			};

			extern COMMON_API CRefPtr<IFileStream>	Open(const CString& strFilename);	//	default: ReadOnly, Open, ReadOnly
			extern COMMON_API CRefPtr<IFileStream>	Open(const CString& strFilename, const AccessType uAccess);	// default: AlwaysOpen, None
			extern COMMON_API CRefPtr<IFileStream>	Open(const CString& strFilename, const AccessType uAccess, const OpenAction uAction); //default: None
			extern COMMON_API CRefPtr<IFileStream>	Open(const CString& strFilename, const AccessType uAccess, const OpenAction uAction, const ShareType uShare);
			extern COMMON_API const bool			Exists(const CString& strFilename);
		}
	}

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

	namespace String{
		extern COMMON_API const CString	ToString(const IO::File::AccessType uType);
		extern COMMON_API const CString	ToString(const IO::File::OpenAction uAction);
		extern COMMON_API const CString	ToString(const IO::File::ShareType uShare);
	}
}