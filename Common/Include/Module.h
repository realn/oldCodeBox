#pragma once

#include "Macros.h"
#include "CBString.h"
#include "Ref.h"
#include "SmartPointers_Hidden.h"
#include "Collection_Dictionary.h"

namespace CB{
	class COMMON_API CModule{
	private:
		CString		m_strName;
		CHiddenPtr	m_pHandle;

	public:
		CModule(const CString& strModule);
		CModule(const CString& strModule, const bool bLoad);
		CModule(const CModule& Module);
		~CModule();

		void	Load();
		void	Unload();

		void*	GetFunction(const CString& strFunctionName);

		const bool	operator==(const CModule& Module) const;
		const bool	operator!=(const CModule& Module) const;

		template<typename _T>
		_T	Get(const CString& strFunctionName){
			return reinterpret_cast<_T>(this->GetFunction(strFunctionName));
		}
	};

	class COMMON_API CModuleRef :
		public CModule,
		public IRef
	{
	private:
		CModuleRef(const CModuleRef& module);
	public:
		CModuleRef(const CString& strModule);
		CModuleRef(const CString& strModule, const bool bLoad);

		template<typename _T>
		_T	Get(const CString& strFunctionName){
			return reinterpret_cast<_T>(this->GetFunction(strFunctionName));
		}
	};

	class COMMON_API CModuleManager : 
		public IRef
	{
	private:
		Collection::CDictionary<CString,CModule> m_ModuleDictionary;

	protected:
		CModuleManager(const CModuleManager& Manager);

	public:
		CModuleManager();
		~CModuleManager();

		void	LoadModule(const CString& strName);
		void	UnloadModule(const CString& strName);

		void*	GetFunction(const CString& strModuleName, const CString& strFunctionName);

		template<typename _T>
		_T	Get(const CString& strModuleName, const CString& strFunctionName){
			return reinterpret_cast<_T>(this->GetFunction(strModuleName, strFunctionName));
		}
	};

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