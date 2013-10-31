#pragma once

#include "CBString.h"
#include "Exception.h"

namespace CB{
	class COMMON_API IRef{
	private:
		unsigned	m_uRefCount;

	protected:
		IRef();
		virtual ~IRef();

	public:
		const unsigned	AddRef();
		const unsigned	Release();

		const unsigned	GetRefCount() const;
	};

	namespace Exception{
		class COMMON_API CNotZeroReferenceException : public CException{
		public:
			CNotZeroReferenceException(const CNotZeroReferenceException& Exception);
			CNotZeroReferenceException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const unsigned uLine);
			CNotZeroReferenceException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const unsigned uLine, const CException& InnerException);

			virtual const CB::CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};
	}
}