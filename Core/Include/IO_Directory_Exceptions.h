#pragma once

#include "Exception.h"

namespace CB {
	namespace Exception{
		class COMMON_API CDirectoryException : 
			public CException
		{
		protected:
			CString	m_strPath;

		public:
			CDirectoryException(const CDirectoryException& Exception);
			CDirectoryException(const CString& strPath, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CDirectoryException(const CString& strPath, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};
	}
}