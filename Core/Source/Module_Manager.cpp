#include "stdafx.h"
#include "../Include/Module.h"
#include "../Include/CBString.h"

namespace CB{
	CModuleManager::CModuleManager(){
	}

	CModuleManager::CModuleManager(const CModuleManager& Manager){
	}

	CModuleManager::~CModuleManager(){
	}

	void	CModuleManager::LoadModule(const CString& strModuleName){
		try{
			if(this->m_ModuleDictionary.Contains(strModuleName)){
				return;
			}
			CModule module(strModuleName);
			module.Load();
			this->m_ModuleDictionary.Add(strModuleName, module);
		}
		catch(Exception::CModuleNotFoundException& Exception){
			throw Exception::CModuleNotFoundException(strModuleName, CR_INFO(), Exception);
		}
		catch(Exception::CModuleLoadException& Exception){
			throw Exception::CModuleLoadException(strModuleName, L"Internal loading error.", CR_INFO(), Exception);
		}
		catch(Exception::CException& Exception){
			throw Exception::CModuleException(strModuleName, L"Unknown internal error.", CR_INFO(), Exception);
		}
	}

	void	CModuleManager::UnloadModule(const CString& strModuleName){
		try{
			this->m_ModuleDictionary.DeleteByKey(strModuleName);
		}
		catch(Exception::CException& Exception){
			throw Exception::CModuleException(strModuleName, L"Failed to unload module.", CR_INFO(), Exception);
		}
	}

	void*	CModuleManager::GetFunction(const CString& strModuleName, const CString& strFunctionName){
		try{
			this->LoadModule(strModuleName);
			return this->m_ModuleDictionary[strModuleName].GetFunction(strFunctionName);
		}
		catch(Exception::CModuleFunctionNotFoundException& Exception){
			throw Exception::CModuleFunctionNotFoundException(strModuleName, strFunctionName, CR_INFO(), Exception);
		}
		catch(Exception::CModuleFunctionLoadException& Exception){
			throw Exception::CModuleFunctionLoadException(strModuleName, strFunctionName, L"Unknown loading error.", CR_INFO(), Exception);
		}
		catch(Exception::CModuleNotFoundException& Exception){
			throw Exception::CModuleNotFoundException(strModuleName, CR_INFO(), Exception);
		}
		catch(Exception::CModuleLoadException& Exception){
			throw Exception::CModuleLoadException(strModuleName, L"Failed loading module for function loading.", CR_INFO(), Exception);
		}
		catch(Exception::CException& Exception){
			throw Exception::CModuleException(strModuleName, L"Error while loading function " + strFunctionName + L".", CR_INFO(), Exception);
		}
	}
}