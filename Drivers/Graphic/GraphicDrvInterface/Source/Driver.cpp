#include "../Internal/Driver.h"

namespace CB{
	const CString	g_strCreateManagerFuncName = L"CreateManager";

	CDriver::CDriver(const CString& strDriverName) :
		m_Module(strDriverName, false),
		m_pCreate(0)
	{
		try{
			this->m_Module.Load();

			this->m_pCreate = this->m_Module.Get<CreateManagerProc>(g_strCreateManagerFuncName);
		}
		catch(Exception::CException& Exception){
			CR_RETHROW(L"Failed to load graphic driver " + strDriverName + L".", Exception);
		}
	}

	CDriver::~CDriver(){
	}

	CRefPtr<Graphic::IManager>	CDriver::CreateManager(CRefPtr<Window::IManager> pWindowManager){
		return this->m_pCreate(this, pWindowManager.Get());
	}

	namespace Graphic{
		CRefPtr<IDriver>	LoadDriver(const CString& strDriverName){
			return new CDriver(strDriverName);
		}
	}
}