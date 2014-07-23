#pragma once

#include "Exception.h"

namespace CB{
	namespace Exception{
		class COMMON_API CStreamException : 
			public CException
		{
		public:
			CStreamException(const CStreamException& Exception);
			CStreamException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CStreamException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, CException& InnerException);

			virtual CException*	CreateCopy() const;
		};
	}
}