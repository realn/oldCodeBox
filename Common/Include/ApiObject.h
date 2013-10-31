#pragma once

#include "Macros.h"
#include "Ref.h"
#include "Exception.h"

#define CR_APICHECK(A, B)	if((A)->GetApiId() != (B)->GetApiId()){ throw Exception::CApiMismatchException((A)->GetApiId(), (B)->GetApiId(), CR_INFO()); }

namespace CB{
	class IApiObject : public virtual IRef{
	public:
		virtual const unsigned GetApiId() const = 0;
	};

	namespace Exception{
		class COMMON_API CApiMismatchException : public CException{
		protected:
			CString	m_strTargetApi;
			CString m_strMismatchApi;

		public:
			CApiMismatchException(const CApiMismatchException& Exception);
			CApiMismatchException(const unsigned uTargetApi, const unsigned uMismatchApi, const CString& strFunction, const CString& strFile, const unsigned uLine);
			CApiMismatchException(const unsigned uTargetApi, const unsigned uMismatchApi, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};
	}
}