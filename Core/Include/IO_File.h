#pragma once

#include "Macros.h"
#include "Types.h"
#include "IO_File_Defs.h"
#include "IO_Stream.h"

namespace CB{
	namespace IO{
		namespace File{
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
			extern COMMON_API const bool			Delete(const CString& strFilename);
		}
	}

	namespace String{
		extern COMMON_API const CString	ToString(const IO::File::AccessType uType);
		extern COMMON_API const CString	ToString(const IO::File::OpenAction uAction);
		extern COMMON_API const CString	ToString(const IO::File::ShareType uShare);
	}
}