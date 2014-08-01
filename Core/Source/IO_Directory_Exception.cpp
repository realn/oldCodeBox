#include "stdafx.h"
#include "../Include/IO_Directory_Exceptions.h"
#include "../Include/Collection_StringList.h"

namespace CB{
	namespace Exception{
		CDirectoryException::CDirectoryException(const CDirectoryException& Exception) : 
			CException(Exception), 
			m_strPath(Exception.m_strPath)
		{
		}

		CDirectoryException::CDirectoryException(const CString& strPath, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CException(strMessage, strFunction, strFile, uLine), m_strPath(strPath)
		{
		}

		CDirectoryException::CDirectoryException(const CString& strPath, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CException(strMessage, strFunction, strFile, uLine, InnerException), m_strPath(strPath)
		{
		}

		const CString	CDirectoryException::GetMessage() const{
			Collection::CStringList VarList;

			VarList.Add(this->m_strPath);
			VarList.Add(this->m_strMessage);

			return String::VarReplace(L"Error while processing directory {0}. {1}", VarList, true);
		}

		CException*	CDirectoryException::CreateCopy() const{
			return new CDirectoryException(*this);
		}
	}
}