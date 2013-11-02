#include "../Include/MessageBox.h"
#include "../Internal/WinPlatform.h"
#include "../../Common/Include/CBStringEx.h"

namespace CB{
	namespace Message{
		void Show(const CString& strText){
			Show(strText, L"Message", Icon::None);
		}
		
		void Show(const CString& strText, const CString& strCaption){
			Show(strText, strCaption, Icon::None);
		}

		void Show(const CString& strText, const CString& strCaption, const Icon uIcon){

			DWORD dwIcon = 0;
			switch (uIcon)
			{
			case Icon::Information:	dwIcon = MB_ICONINFORMATION; break;
			case Icon::Exclamation:	dwIcon = MB_ICONEXCLAMATION; break;
			case Icon::Question:	dwIcon = MB_ICONQUESTION; break;
			case Icon::Warning:		dwIcon = MB_ICONWARNING; break;
			case Icon::Error:		dwIcon = MB_ICONERROR; break;
			default:
				break;
			}

			MessageBoxW(0, strText.GetPointer(), strCaption.GetPointer(), MB_OK | dwIcon);
		}

		void Show(const Exception::CException& Exception){
			Show(Exception, Icon::Error);
		}

		void Show(const Exception::CException& Exception, const Icon uIcon){
			Collection::CStringList list;

			const Exception::CException* pException = &Exception;

			list.Add(L"Exception occured:");
			list.Add(L" ");
			list.Add(L"Function: " + pException->GetFunction());
			list.Add(L"File: " + pException->GetFile());
			list.Add(L"Line: " + String::FromUInt32(pException->GetLine()));
			list.Add(L"Message: " + pException->GetMessage());
			
			while(pException->HasInnerException()){
				pException = &pException->GetInnerException();
				list.Add(L" ");
				list.Add(L"Inner exception:");
				list.Add(L" ");
				list.Add(L"Function: " + pException->GetFunction());
				list.Add(L"File: " + pException->GetFile());
				list.Add(L"Line: " + String::FromUInt32(pException->GetLine()));
				list.Add(L"Message: " + pException->GetMessage());
			}

			Show(list.ToString(L"\n"), L"Exception", uIcon);
		}
	}
}