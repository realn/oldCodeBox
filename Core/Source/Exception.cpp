#include "stdafx.h"
#include "../Include/Exception.h"
#include "../Include/Collection_StringList.h"

namespace CB{
	namespace Exception{

		CException::CException(const CException& Exception) : 
			m_strMessage(Exception.m_strMessage),
			m_strFunction(Exception.m_strFunction),
			m_strFile(Exception.m_strFile),
			m_uLine(Exception.m_uLine),
			m_pException(0)
		{
			if(Exception.m_pException){
				this->m_pException = Exception.m_pException->CreateCopy();
			}
		}

		CException::CException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) :
			m_strMessage(strMessage),
			m_strFunction(strFunction),
			m_strFile(strFile),
			m_uLine(uLine),
			m_pException(0)
		{}

		CException::CException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException) : 
			m_strMessage(strMessage),
			m_strFunction(strFunction),
			m_strFile(strFile),
			m_uLine(uLine),
			m_pException(0)
		{
			this->m_pException	= InnerException.CreateCopy();
		};

		CException::~CException(){
			if(this->m_pException){
				delete this->m_pException;
				this->m_pException = 0;
			}
		}

		const CB::CString	CException::GetMessage() const{
			return this->m_strMessage;
		}

		const CB::CString&	CException::GetFunction() const{
			return this->m_strFunction;
		}

		const CB::CString&	CException::GetFile() const{
			return this->m_strFile;
		}

		const uint32	CException::GetLine() const{
			return this->m_uLine;
		}

		const CException&	CException::GetInnerException() const{
			return *this->m_pException;
		}

		const bool	CException::HasInnerException() const{
			return this->m_pException != 0;
		}

		CException*	CException::CreateCopy() const{
			return new CException(*this);
		}

		//	Invalid argument exception

		CInvalidArgumentException::CInvalidArgumentException(const CInvalidArgumentException& Exception) : 
			CException(Exception),
			m_strArgumentName(Exception.m_strArgumentName),
			m_strValue(Exception.m_strValue)
		{}

		CInvalidArgumentException::CInvalidArgumentException(const CB::CString& strArgName, const CB::CString& strArgValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CException(strMessage, strFunction, strFile, uLine),
			m_strArgumentName(strArgName),
			m_strValue(strArgValue)
		{}

		CInvalidArgumentException::CInvalidArgumentException(const CB::CString& strArgName, const CB::CString& strArgValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException) :
			CException(strMessage, strFunction, strFile, uLine, InnerException),
			m_strArgumentName(strArgName),
			m_strValue(strArgValue)
		{}

		const CB::CString	CInvalidArgumentException::GetMessage() const{
			CB::Collection::CStringList VarList;

			VarList.Add(this->m_strArgumentName);
			VarList.Add(this->m_strValue);

			return String::VarReplace(L"Argument {0} has invalid value {1}.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CInvalidArgumentException::CreateCopy() const{
			return new CInvalidArgumentException(*this);
		}

		//	Null argument exception

		CNullArgumentException::CNullArgumentException(const CNullArgumentException& Exception) : 
			CInvalidArgumentException(Exception)
		{}

		CNullArgumentException::CNullArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) 
			: CInvalidArgumentException(strArgName, L"NULL", strMessage, strFunction, strFile, uLine){
		}

		CNullArgumentException::CNullArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException)
			: CInvalidArgumentException(strArgName, L"NULL", strMessage, strFunction, strFile, uLine, InnerException){
		}

		const CB::CString	CNullArgumentException::GetMessage() const{
			CB::Collection::CStringList	strVars;

			strVars.Add(this->m_strArgumentName);

			return CB::String::VarReplace(L"Argument {0} is NULL.", strVars, true) + L" " + this->m_strMessage;
		}

		CException*	CNullArgumentException::CreateCopy() const{
			return new CNullArgumentException(*this);
		}

		//	Zero length Argument Exception

		CZeroLengthArgumentException::CZeroLengthArgumentException(const CZeroLengthArgumentException& Exception) : 
			CInvalidArgumentException(Exception)
		{}

		CZeroLengthArgumentException::CZeroLengthArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) 
			: CInvalidArgumentException(strArgName, L"0", strMessage, strFunction, strFile, uLine){
		}

		CZeroLengthArgumentException::CZeroLengthArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException)
			: CInvalidArgumentException(strArgName, L"0", strMessage, strFunction, strFile, uLine, InnerException){
		}

		const CB::CString	CZeroLengthArgumentException::GetMessage() const{
			CB::Collection::CStringList	strVars;

			strVars.Add(this->m_strArgumentName);

			return CB::String::VarReplace(L"Argument {0} has zero length.", strVars, true) + L" " + this->m_strMessage;
		}

		CException*	CZeroLengthArgumentException::CreateCopy() const{
			return new CZeroLengthArgumentException(*this);
		}

		//	Out of memory exception

		COutOfMemoryException::COutOfMemoryException(const COutOfMemoryException& Exception) : 
			CException(Exception){
		}

		COutOfMemoryException::COutOfMemoryException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) :
			CException(strMessage, strFunction, strFile, uLine){
		}

		COutOfMemoryException::COutOfMemoryException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException) :
			CException(strMessage, strFunction, strFile, uLine, InnerException){
		}

		CException*	COutOfMemoryException::CreateCopy() const{
			return new COutOfMemoryException(*this);
		}

		//	Null pointer exception

		CNullPointerException::CNullPointerException(const CNullPointerException& Exception) : 
			CException(Exception),
			m_strPointerName(Exception.m_strPointerName)
		{}

		CNullPointerException::CNullPointerException(const CB::CString& strPtrName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine)
			: CException(strMessage, strFunction, strFile, uLine),
			m_strPointerName(strPtrName)
		{}

		CNullPointerException::CNullPointerException(const CB::CString& strPtrName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException)
			: CException(strMessage, strFunction, strFile, uLine, InnerException),
			m_strPointerName(strPtrName)
		{}

		const CB::CString	CNullPointerException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strPointerName);

			return CB::String::VarReplace(L"Pointer named {0} has null value.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CNullPointerException::CreateCopy() const{
			return new CNullPointerException(*this);
		}

		//	Zero length exception

		CZeroLengthException::CZeroLengthException(const CZeroLengthException& Exception) : 
			CException(Exception),
			m_strSenderName(Exception.m_strSenderName)
		{}

		CZeroLengthException::CZeroLengthException(const CB::CString& strSenderName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) 
			: CException(strMessage, strFunction, strFile, uLine),
			m_strSenderName(strSenderName)
		{}

		CZeroLengthException::CZeroLengthException(const CB::CString& strSenderName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException) 
			: CException(strMessage, strFunction, strFile, uLine, InnerException),
			m_strSenderName(strSenderName)
		{}

		const CB::CString	CZeroLengthException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strSenderName);

			return CB::String::VarReplace(L"{0} has zero length.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CZeroLengthException::CreateCopy() const{
			return new CZeroLengthException(*this);
		}

		//	Invalid var value exception

		CInvalidVarValueException::CInvalidVarValueException(const CInvalidVarValueException& Exception) : 
			CException(Exception),
			m_strVarName(Exception.m_strVarName),
			m_strVarValue(Exception.m_strVarValue)
		{}

		CInvalidVarValueException::CInvalidVarValueException(const CB::CString& strVarName, const CB::CString& strVarValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine) : 
			CException(strMessage, strFunction, strFile, uLine),
			m_strVarName(strVarName),
			m_strVarValue(strVarValue)
		{}

		CInvalidVarValueException::CInvalidVarValueException(const CB::CString& strVarName, const CB::CString& strVarValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException) : 
			CException(strMessage, strFunction, strFile, uLine),
			m_strVarName(strVarName),
			m_strVarValue(strVarValue)
		{}

		const CB::CString	CInvalidVarValueException::GetMessage() const{
			CB::Collection::CStringList	VarList;

			VarList.Add(this->m_strVarName);
			VarList.Add(this->m_strVarValue);

			return CB::String::VarReplace(L"{0} has invalid value of {1}.", VarList, true) + L" " + this->m_strMessage;
		}

		CException*	CInvalidVarValueException::CreateCopy() const{
			return new CInvalidVarValueException(*this);
		}


	}
}