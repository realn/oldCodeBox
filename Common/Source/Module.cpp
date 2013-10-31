#include "../Include/Module.h"
#include "../Internal/WinPlatform.h"
#include "../Include/WindowsErrors.h"
#include "../../Common/Include/CBStringEx.h"

namespace CB{
	CModule::CModule(const CString& strName) : 
		m_strName(strName)
	{
		this->Load();
	}

	CModule::CModule(const CString& strName, const bool bLoad) :
		m_strName(strName)
	{
		if(bLoad){
			this->Load();
		}
	}

	CModule::CModule(const CModule& Module) : 
		m_strName(Module.m_strName), 
		m_pHandle(Module.m_pHandle)
	{
		if(this->m_pHandle.IsValid()){
			// rainsing module reference count for proper handling
			this->m_pHandle.SetCast<HMODULE>(LoadLibraryW(this->m_strName.ToConst()));
		}
	}

	CModule::~CModule(){
		this->Unload();
	}

	void	CModule::Load(){
		if(this->m_pHandle.IsValid())
			return;

		this->m_pHandle.SetCast<HMODULE>(LoadLibraryW(this->m_strName.ToConst()));
		if(this->m_pHandle.IsNull()){
			DWORD dwError = GetLastError();
			if(dwError == ERROR_MOD_NOT_FOUND){
				throw Exception::CModuleNotFoundException(this->m_strName, __FUNCTIONW__, __FILEW__, __LINE__);
			}
			else{
				throw Exception::CModuleLoadException(this->m_strName,
					CWindowsError(GetLastError()).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}

	void	CModule::Unload(){
		if(this->m_pHandle.IsValid()){
			if(!FreeLibrary(this->m_pHandle.GetCast<HMODULE>())){
				throw Exception::CModuleException(this->m_strName,
					L"Failed to unload module: " + CWindowsError(GetLastError()).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}

	void*	CModule::GetFunction(const CString& strFunctionName){
		if(this->m_pHandle.IsNull()){
			throw Exception::CModuleException(this->m_strName,
				L"Module not loaded.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		if(strFunctionName.IsEmpty()){
			throw Exception::CModuleException(this->m_strName,
				L"Cannot load function with empty name string.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		Collection::CList<char> szFuncName(strFunctionName.GetLength() + 1);
		Memory::SetZeroArray(szFuncName);
		String::ToANSI(strFunctionName, szFuncName);

		FARPROC pFunc = GetProcAddress(this->m_pHandle.GetCast<HMODULE>(), &szFuncName[0]);
		if(pFunc == 0){
			DWORD dwError = GetLastError();

			if(dwError == ERROR_PROC_NOT_FOUND){
				throw Exception::CModuleFunctionNotFoundException(this->m_strName, strFunctionName, __FUNCTIONW__, __FILEW__, __LINE__);
			}
			else{
				throw Exception::CModuleFunctionLoadException(this->m_strName, strFunctionName,
					CWindowsError(dwError).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		return (void*)pFunc;
	}

	CModuleRef::CModuleRef(const CModuleRef& Module) :
		CModule(Module)
	{}

	CModuleRef::CModuleRef(const CString& strModule) :
		CModule(strModule)
	{}

	CModuleRef::CModuleRef(const CString& strModule, const bool bLoad) :
		CModule(strModule, bLoad)
	{}
}