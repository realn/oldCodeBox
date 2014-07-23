#include "stdafx.h"
#include "../Include/Exception.h"
#include "../Include/WindowsErrors.h"

namespace CB{
	namespace Exception{
#ifdef _WIN32
		CWindowException::CWindowException(const CWindowException& Exception) : 
			CException(Exception), 
			m_strError(Exception.m_strError)
		{}

		CWindowException::CWindowException(const uint32 uError, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) : 
			CException(strMessage, strFunction, strFile, uLine), 
			m_strError(CWindowsError(uError).GetMessage())
		{}

		CWindowException::CWindowException(const uint32 uError, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) : 
			CException(strMessage, strFunction, strFile, uLine, InnerException), 
			m_strError(CWindowsError(uError).GetMessage())
		{}

		const CString	CWindowException::GetMessage() const{
			return this->m_strMessage + L" Windows Error: " + this->m_strError;
		}

		CException*	CWindowException::CreateCopy() const{
			return new CWindowException(*this);
		}

		CCOMException::CCOMException(const CCOMException& Exception) : 
			CException(Exception), 
			m_hResult(Exception.m_hResult)
		{}

		CCOMException::CCOMException(const uint32 hResult, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) : 
			CException(strMessage, strFunction, strFile, uLine), 
			m_hResult(hResult)
		{}

		CCOMException::CCOMException(const uint32 hResult, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) : 
			CException(strMessage, strFunction, strFile, uLine, InnerException), 
			m_hResult(hResult)
		{}

		const CString	CCOMException::GetMessage() const{
			return L"HRESULT: " + String::ToHexString(this->m_hResult) + L". " + this->m_strMessage;
		}

		CException*	CCOMException::CreateCopy() const{
			return new CCOMException(*this);
		}
#endif
	}
}