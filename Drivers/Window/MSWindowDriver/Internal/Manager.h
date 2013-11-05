#pragma once

#include "../Include/MSWindowDriver.h"
#include <Manage_Object.h>
#include "WinPlatform.h"

namespace CB{
	extern const uint32 g_uApiId;

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

		const uint32	GetApiId() const override;

		CRefPtr<Window::IWindow>	CreateWindow(const CString& strTitle, const Window::Style uStyle) override;
		CRefPtr<Window::IWindow>	CreateWindow(const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size) override;
		CRefPtr<Window::IWindow>	CreateWindow(const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size, const Math::CPoint& Position) override;

		void	ProcessEvents() override;
		void	ProcessEvents(const uint32 uMaxEvents) override;

		const bool	SupportsMultiWindow() const override;
		const bool	SupportsStyle(const Window::Style uStyle) const override;

		//end of IWindowManager
	};
}