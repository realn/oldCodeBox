#pragma once

#include "Macros.h"
#include "Ref.h"
#include "Exception.h"

#define CR_APICHECK(A, B)	if((A)->GetApiId() != (B)->GetApiId()){ throw Exception::CApiMismatchException((A)->GetApiId(), (B)->GetApiId(), CR_INFO()); }

namespace CB{
	class IApiObject : 
		public virtual IRef
	{
	public:
		virtual const uint32 GetApiId() const = 0;
	};

	namespace Exception{
		class COMMON_API CApiMismatchException : 
			public CException
		{
		protected:
			CString	m_strTargetApi;
			CString m_strMismatchApi;

		public:
			CApiMismatchException(const CApiMismatchException& Exception);
			CApiMismatchException(const uint32 uTargetApi, const uint32 uMismatchApi, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CApiMismatchException(const uint32 uTargetApi, const uint32 uMismatchApi, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};
	}
}