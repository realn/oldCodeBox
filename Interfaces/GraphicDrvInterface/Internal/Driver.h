#include "../Include/GraphicDriver.h"
#include <Module.h>

namespace CB{
	typedef	Graphic::IManager*	(*CreateManagerProc)(Graphic::IDriver* pDriver, Window::IManager* pWindowManager);

	class CDriver :
		public Graphic::IDriver
	{
	private:
		CModule				m_Module;
		CreateManagerProc	m_pCreate;

	public:
		CDriver(const CString& strDriverName);
		~CDriver();

		CRefPtr<Graphic::IManager>	CreateManager(CRefPtr<Window::IManager> pWindowManager) override;
	};
}