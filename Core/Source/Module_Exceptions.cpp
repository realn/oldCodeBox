#include "stdafx.h"
#include "../Include/Module.h"
#include "../Include/Collection_StringList.h"

namespace CB{
	namespace Exception{
		CModuleException::CModuleException(const CModuleException& Exception) : 
			CException(Exception), 
			m_strModuleName(Exception.m_strModuleName)
		{}

		CModuleException::CModuleException(const CString& strModuleName, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CException(strMessage, strFunction, strFile, uLine), 
			m_strModuleName(strModuleName)
		{}

		CModuleException::CModuleException(const CString& strModuleName, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CException(strMessage, strFunction, strFile, uLine, InnerException), 
			m_strModuleName(strModuleName)
		{}

		const CString	CModuleException::GetMessage() const{
			return L"Error with " + this->m_strModuleName + L" module: " + this->m_strMessage;
		}

		CException*	CModuleException::CreateCopy() const{
			return new CModuleException(*this);
		}

		//====

		CModuleLoadException::CModuleLoadException(const CModuleLoadException& Exception) : 
			CModuleException(Exception)
		{}

		CModuleLoadException::CModuleLoadException(const CString& strModuleName, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CModuleException(strModuleName, strMessage, strFunction, strFile, uLine)
		{}

		CModuleLoadException::CModuleLoadException(const CString& strModuleName, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) : 
			CModuleException(strModuleName, strMessage, strFunction, strFile, uLine, InnerException)
		{}

		const CString	CModuleLoadException::GetMessage() const{
			return L"Error while loading " + this->m_strModuleName + L" module: " + this->m_strMessage;
		}

		CException*	CModuleLoadException::CreateCopy() const{
			return new CModuleLoadException(*this);
		}

		//====

		CModuleNotFoundException::CModuleNotFoundException(const CModuleNotFoundException& Exception) : 
			CModuleLoadException(Exception)
		{}

		CModuleNotFoundException::CModuleNotFoundException(const CString& strModuleName, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CModuleLoadException(strModuleName, L"Module Not found.", strFunction, strFile, uLine)
		{}

		CModuleNotFoundException::CModuleNotFoundException(const CString& strModuleName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) : 
			CModuleLoadException(strModuleName, L"Module not found.", strFunction, strFile, uLine, InnerException)
		{}

		const CString	CModuleNotFoundException::GetMessage() const{
			return L"Error while loading " + this->m_strModuleName + L" module: " + this->m_strMessage;
		}

		CException*	CModuleNotFoundException::CreateCopy() const{
			return new CModuleNotFoundException(*this);
		}

		//====

		CModuleFunctionLoadException::CModuleFunctionLoadException(const CModuleFunctionLoadException& Exception) : 
			CModuleException(Exception), 
			m_strModuleFunction(m_strModuleFunction)
		{}

		CModuleFunctionLoadException::CModuleFunctionLoadException(const CString& strModuleName, const CString& strModuleFunction, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CModuleException(strModuleName, strMessage, strFunction, strFile, uLine), 
			m_strModuleFunction(strModuleFunction)
		{}

		CModuleFunctionLoadException::CModuleFunctionLoadException(const CString& strModuleName, const CString& strModuleFunction, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CModuleException(strModuleName, strMessage, strFunction, strFile, uLine, InnerException), 
			m_strModuleFunction(strModuleFunction)
		{}

		const CString	CModuleFunctionLoadException::GetMessage() const{
			Collection::CStringList VarList;

			VarList.Add(this->m_strModuleName);
			VarList.Add(this->m_strModuleFunction);

			return String::VarReplace(L"Error while loading function {1} from {0} module: ", VarList, true) + this->m_strMessage;
		}

		CException*	CModuleFunctionLoadException::CreateCopy() const{
			return new CModuleFunctionLoadException(*this);
		}

		//====

		CModuleFunctionNotFoundException::CModuleFunctionNotFoundException(const CModuleFunctionNotFoundException& Exception) : 
			CModuleFunctionLoadException(Exception)
		{}

		CModuleFunctionNotFoundException::CModuleFunctionNotFoundException(const CString& strModuleName, const CString& strModuleFunction, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CModuleFunctionLoadException(strModuleName, strModuleFunction, L"Function not found.", strFunction, strFile, uLine)
		{}

		CModuleFunctionNotFoundException::CModuleFunctionNotFoundException(const CString& strModuleName, const CString& strModuleFunction, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CModuleFunctionLoadException(strModuleName, strModuleFunction, L"Function not found.", strFunction, strFile, uLine, InnerException)
		{}

		const CString	CModuleFunctionNotFoundException::GetMessage() const{
			Collection::CStringList VarList;

			VarList.Add(this->m_strModuleName);
			VarList.Add(this->m_strModuleFunction);

			return String::VarReplace(L"Error while loading function {1} from {0} module: ", VarList, true) + this->m_strMessage;
		}

		CException*	CModuleFunctionNotFoundException::CreateCopy() const{
			return new CModuleFunctionNotFoundException(*this);
		}
	}
}