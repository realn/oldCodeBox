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
		void	SetSize(const Math::CSize& Size) override;
		void	SetVisible(const bool bVisible) override;
		void	SetTitle(const CString& strTitle) override;
		void	SetStyle(const Window::Style uStyle) override;

		const Math::CPoint	GetPosition() const override;
		const Math::CSize	GetSize() const override;
		const bool			IsVisible() const override;
		const CString		GetTitle() const override;
		const Window::Style	GetStyle() const override;

		void*	GetHandle() const override;

		//end of IWindow implementation

		const bool	ProcessMessage(const unsigned uMessage, const WPARAM wParam, const LPARAM lParam);
	};
}