#pragma once

#include "Macros.h"
#include "CBString.h"

#define		CR_THROW(A)	throw CB::Exception::CException(A, __FUNCTIONW__, __FILEW__, __LINE__);
#define		CR_RETHROW(A,B)	throw CB::Exception::CException(A, __FUNCTIONW__, __FILEW__, __LINE__, B);
#define		CR_INFO()	__FUNCTIONW__, __FILEW__, __LINE__

#define		CR_THROWNOTIMPLEMENTED()	CR_THROW(L"Not Implemented.")

#ifdef _DEBUG
#define		CR_ASSERT(A,B)	if(!(A)){ CR_THROW(B); }
#else
#define		CR_ASSERT(A,B)
#endif

namespace CB{
	namespace Exception{
		class COMMON_API CException{
		protected:
			CString		m_strMessage;
			CString		m_strFunction;
			CString		m_strFile;
			uint32		m_uLine;
			CException*		m_pException;

		public:
			CException(const CException& Exception);
			CException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);
			virtual ~CException();

			virtual const CString	GetMessage() const;
			const CString&			GetFunction() const;
			const CString&			GetFile() const;
			const uint32			GetLine() const;
			const CException&		GetInnerException() const;

			const bool HasInnerException() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CInvalidArgumentException : public CException{
		protected:
			CB::CString	m_strArgumentName;
			CB::CString	m_strValue;

		public:
			CInvalidArgumentException(const CInvalidArgumentException& Exception);
			CInvalidArgumentException(const CB::CString& strArgName, const CB::CString& strArgValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CInvalidArgumentException(const CB::CString& strArgName, const CB::CString& strArgValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CB::CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CNullArgumentException : public CInvalidArgumentException{
		public:
			CNullArgumentException(const CNullArgumentException& Exception);
			CNullArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CNullArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CB::CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CZeroLengthArgumentException : public CInvalidArgumentException{
		public:
			CZeroLengthArgumentException(const CZeroLengthArgumentException& Exception);
			CZeroLengthArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CZeroLengthArgumentException(const CB::CString& strArgName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CB::CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API COutOfMemoryException : public CException{
		public:
			COutOfMemoryException(const COutOfMemoryException& Exception);
			COutOfMemoryException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			COutOfMemoryException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CNullPointerException : public CException{
		protected:
			CB::CString	m_strPointerName;

		public:
			CNullPointerException(const CNullPointerException& Exception);
			CNullPointerException(const CB::CString& strPtrName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CNullPointerException(const CB::CString& strPtrName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CB::CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CZeroLengthException : public CException{
		protected:
			CB::CString	m_strSenderName;
			
		public:
			CZeroLengthException(const CZeroLengthException& Exception);
			CZeroLengthException(const CB::CString& strSenderName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CZeroLengthException(const CB::CString& strSenderName, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CB::CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CInvalidVarValueException : public CException{
		protected:
			CB::CString	m_strVarName;
			CB::CString m_strVarValue;

		public:
			CInvalidVarValueException(const CInvalidVarValueException& Exception);
			CInvalidVarValueException(const CB::CString& strVarName, const CB::CString& strVarValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine);
			CInvalidVarValueException(const CB::CString& strVarName, const CB::CString& strVarValue, const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CB::CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

#ifdef _WIN32
		class COMMON_API CWindowException : public CException{
		protected:
			CString	m_strError;

		public:
			CWindowException(const CWindowException& Exception);
			CWindowException(const uint32 uError, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CWindowException(const uint32 uError, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};

		class COMMON_API CCOMException : public CException{
		protected:
			uint32 m_hResult;

		public:
			CCOMException(const CCOMException& Exception);
			CCOMException(const uint32 hResult, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CCOMException(const uint32 hResult, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};
#endif
	}
}

#ifndef _STR2WSTR
#define __STR2WSTR(STR)	L##STR
#define _STR2WSTR(STR)	__STR2WSTR(STR)
#endif

#ifndef __FUNCTIONW__
#define __FUNCTIONW__	_STR2WSTR(__FUNCTION__)
#endif

#ifndef __FILEW__
#define __FILEW__	_STR2WSTR(__FILE__)
#endif

#ifdef _WIN32
#define CR_THROWWIN(A,B)	throw CB::Exception::CWindowException((A), (B), CR_INFO());
#define CR_THROWCOM(A,B)	throw CB::Exception::CCOMException((A), (B), CR_INFO());
#endif