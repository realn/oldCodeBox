#pragma once

#include "../../Common/Include/CBString.h"
#include "../Internal/WinPlatform.h"

namespace CB{
	class CWindowsError{
	private:
		DWORD	m_dwErrorCode;

	public:
		CWindowsError(const DWORD dwErrorCode) : m_dwErrorCode(dwErrorCode){
		}

		const CString	GetMessage() const{
			LPCWSTR szMessage = 0;
			if(FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 0, this->m_dwErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&szMessage, 1, 0)){
				CString strReturn(szMessage);
				LocalFree((HLOCAL)szMessage);

				return strReturn;
			}

			return L"Error nr " + String::FromUInt32(this->m_dwErrorCode);
		}
	};
}