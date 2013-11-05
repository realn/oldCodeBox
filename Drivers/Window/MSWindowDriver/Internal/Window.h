#pragma once

#include "Manager.h"
#include "WinPlatform.h"

namespace CB{
	class CWindow : 
		public Window::IWindow,
		public Manage::IManagedObject<CWindowManager, CWindow>
	{
	private:
		HWND			m_hWindow;
		Window::Style	m_uStyle;

	public:
		CWindow(CRefPtr<CWindowManager> pMng, const CString& strClass, const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size, const Math::CPoint& Position);
		~CWindow();
		
		//IWindow implementation

		const unsigned GetApiId() const override;

		CRefPtr<Window::IManager>	GetManager() const override;

		void	SetPosition(const Math::CPoint& Position) override;
		const Math::CPoint	GetPosition() const override;

		void	SetSize(const Math::CSize& Size) override;
		const Math::CSize	GetSize() const override;

		void	SetVisible(const bool bVisible) override;
		const bool	IsVisible() const override;

		void	SetTitle(const CString& strTitle) override;
		const CString	GetTitle() const override;

		void	SetStyle(const Window::Style uStyle) override;
		const Window::Style	GetStyle() const override;

		void*	GetHandle() const override;

		//end of IWindow implementation

		const bool	ProcessMessage(const unsigned uMessage, const WPARAM wParam, const LPARAM lParam);
	};
}