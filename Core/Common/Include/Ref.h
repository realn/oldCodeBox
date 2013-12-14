#pragma once

#include "CBString.h"
#include "Exception.h"

namespace CB{
	class COMMON_API IRef{
	private:
		uint32	m_uRefCount;

	protected:
		IRef();
		virtual ~IRef();

	public:
		const uint32	AddRef();
		const uint32	Release();

		const uint32	GetRefCount() const;
	};

	namespace Exception{
		class COMMON_API CNotZeroReferenceException : 
			public CException
		{
		public:
			CNotZeroReferenceException(const CNotZeroReferenceException& Exception);
			CNotZeroReferenceException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CNotZeroReferenceException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual CException*	CreateCopy() const override;
		};
	}
}