#pragma once

#include "Macros.h"
#include "Types.h"
#include "Exception.h"

namespace CB{
	namespace Exception{
		class COMMON_API CModuleException : 
			public CException
		{
		protected:
			CString	m_strModuleName;

		public:
			CModuleException(const CModuleException& Exception);
			CModuleException(const CString& strModuleName, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CModuleException(const CString& strModuleName, const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API CModuleLoadException : 
			public CModuleException
		{
		public:
			CModuleLoadException(const CModuleLoadException& Exception);
			CModuleLoadException(const CString& strModuleName, const CString& strError, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CModuleLoadException(const CString& strModuleName, const CString& strError, const CString& strFunction, const CString& strFile, const uint32 uLine, const Exception::CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual Exception::CException*	CreateCopy() const override;
		};

		class COMMON_API CModuleNotFoundException : 
			public CModuleLoadException
		{
		public:
			CModuleNotFoundException(const CModuleNotFoundException& Exception);
			CModuleNotFoundException(const CString& strModuleName, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CModuleNotFoundException(const CString& strModuleName, const CString& strFunction, const CString& strFile, const uint32 uLine, const Exception::CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual Exception::CException*	CreateCopy() const override;
		};

		class COMMON_API CModuleFunctionLoadException : 
			public CModuleException
		{
		protected:
			CString	m_strModuleFunction;

		public:
			CModuleFunctionLoadException(const CModuleFunctionLoadException& Exception);
			CModuleFunctionLoadException(const CString& strModuleName, const CString& strModuleFunction, const CString& strError, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CModuleFunctionLoadException(const CString& strModuleName, const CString& strModuleFunction, const CString& strError, const CString& strFunction, const CString& strFile, const uint32 uLine, const Exception::CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual Exception::CException*	CreateCopy() const override;
		};

		class COMMON_API CModuleFunctionNotFoundException : 
			public CModuleFunctionLoadException
		{
		public:
			CModuleFunctionNotFoundException(const CModuleFunctionNotFoundException& Exception);
			CModuleFunctionNotFoundException(const CString& strModuleName, const CString& strModuleFunction, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CModuleFunctionNotFoundException(const CString& strModuleName, const CString& strModuleFunction, const CString& strFunction, const CString& strFile, const uint32 uLine, const Exception::CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual Exception::CException*	CreateCopy() const override;
		};
	}
}