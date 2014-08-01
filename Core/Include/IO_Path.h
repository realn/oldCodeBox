#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class CString;

	namespace IO{
		namespace Path{
			extern COMMON_API const CString	RepairDirectorySlashes(const CB::CString& strPath);
			extern COMMON_API const CString	Combine(const CB::CString& strPath1, const CB::CString& strPath2);
			extern COMMON_API const CString	CombineFilename(const CB::CString& strName, const CB::CString& strExt);
			extern COMMON_API const CString	GetFilename(const CB::CString& strPath);
			extern COMMON_API const CString	GetDirectory(const CB::CString& strPath);
			extern COMMON_API const CString	GetFilenameBase(const CB::CString& strFilename);
			extern COMMON_API const CString	GetFilenameExt(const CB::CString& strFilename);
			extern COMMON_API const CString	GetDirectoryBase(const CB::CString& strPath);
		}
	}
}