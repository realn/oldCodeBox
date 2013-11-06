#include "../Include/GraphicDriver.h"
#include "../../Common/Include/Module.h"

namespace CB{
	namespace Graphic{
		const CString	g_strCreateManagerFuncName = L"CreateManager";

		typedef	IManager*	(*CreateManagerProc)(IDriver* pDriver);

		class CDriver :
			public IDriver
		{
		private:
			CModule				m_Module;
			CreateManagerProc	m_pCreate;

		public:
			CDriver(const CString& strDriverName) :
				m_Module(strDriverName, true),
				m_pCreate(0)
			{
				this->m_pCreate = this->m_Module.Get<CreateManagerProc>(g_strCreateManagerFuncName);
			}

			CRefPtr<IManager>	CreateManager() override{
				return this->m_pCreate(this);
			}
		};

		CRefPtr<IDriver>	LoadDriver(const CString& strDriverName){
			return new CDriver(strDriverName);
		}
	}
}