#include "../Include/ApiObject.h"

namespace CB{
	namespace Exception{
		CApiMismatchException::CApiMismatchException(const CApiMismatchException& Exception) :
			CException(Exception), m_strTargetApi(Exception.m_strTargetApi), m_strMismatchApi(Exception.m_strMismatchApi)
		{
		}

		CApiMismatchException::CApiMismatchException(const unsigned uTargetApi, const unsigned uMismatchApi, const CString& strFunction, const CString& strFile, const unsigned uLine) :
			CException(L"Api Id mismatch.", strFunction, strFile, uLine),
			m_strTargetApi(String::FromUInt32(uTargetApi)), m_strMismatchApi(String::FromUInt32(uMismatchApi))
		{
		}

		CApiMismatchException::CApiMismatchException(const unsigned uTargetApi, const unsigned uMismatchApi, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& InnerException) :
			CException(L"Api Id mismatch.", strFunction, strFile, uLine, InnerException),
			m_strTargetApi(String::FromUInt32(uTargetApi)), m_strMismatchApi(String::FromUInt32(uMismatchApi))
		{
		}

		const CString	CApiMismatchException::GetMessage() const{
			return this->m_strMessage + L"For api id " + this->m_strTargetApi + L" got " + this->m_strMismatchApi + L".";
		}

		CException*	CApiMismatchException::CreateCopy() const{
			return new CApiMismatchException(*this);
		}
	}
}