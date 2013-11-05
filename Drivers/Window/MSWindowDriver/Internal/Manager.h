#pragma once

#include "../Include/WindowDriver.h"
#include "../../Common/Include/Manage_Object.h"
#include "WinPlatform.h"

namespace CB{
	extern const unsigned g_uApiId;

	class CWindow;
	class CWindowManager : 
		public Window::IManager,
		public Manage::IObjectManager<CWindow>
	{
	private:
		CRefPtr<Window::IDriver>	m_pDriver;
		CString						m_strClassName;

	public:
		CWindowManager(CRefPtr<Window::IDriver> pDriver);
		~CWindowManager();

		//IWindowManager implementation

		const unsigned	GetApiId() const override;

		CRefPtr<Window::IWindow>	CreateWindow(const CString& strTitle, const Window::Style uStyle) override;
		CRefPtr<Window::IWindow>	CreateWindow(const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size) override;
		CRefPtr<Window::IWindow>	CreateWindow(const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size, const Math::CPoint& Position) override;

		void	ProcessEvents() override;
		void	ProcessEvents(const unsigned uMaxEvents) override;

		const bool	SupportsMultiWindow() const override;
		const bool	SupportsStyle(const Window::Style uStyle) const override;

		//end of IWindowManager
	};
}