#include "stdafx.h"
#include "../Include/Graphic_Window.h"
#include "../Include/Graphic_Strings.h"
#include "../Internal/Graphic_WindowImpl.h"
#include "../Internal/Graphic_WindowClass.h"

#include <Logger.h>
#include <Math_Point2D.h>
#include <Math_Size2D.h>
#include <Math_Rectangle.h>

namespace CB{
	namespace Graphic{
		const bool	GetMSWindowStyle(const Style uStyle, DWORD& dwOutStyle, DWORD& dwOutExStyle){
			switch (uStyle){
			case Style::Pure:
				dwOutStyle = WS_OVERLAPPED;
				dwOutExStyle = 0;
				return true;

			case Style::Single:
				dwOutStyle = WS_OVERLAPPEDWINDOW;
				dwOutExStyle = 0;
				return true;

			case Style::Sizeable:
				dwOutStyle = WS_OVERLAPPEDWINDOW;
				dwOutExStyle = WS_OVERLAPPEDWINDOW;
				return true;

			case Style::ToolWindow:
				dwOutStyle = WS_OVERLAPPEDWINDOW;
				dwOutExStyle = WS_EX_TOOLWINDOW;
				return true;

			case Style::SizeableToolWindow:
				dwOutStyle = WS_OVERLAPPEDWINDOW;
				dwOutExStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_TOOLWINDOW;
				return true;
		
			default:
				return false;
			}
		}

		void	ORCombiner(const bool* pbResult, const bool bValue){
			bool *pW = const_cast<bool*>(pbResult);

			(*pW) = *pW || bValue;
		}

		CWindow::CWindow(const CString& strTitle, const Style uStyle) :
			m_pImpl( new CWindowImpl() )
		{
			this->Init( strTitle, uStyle, Math::CSize2D(), Math::CPoint2D() );
		}

		CWindow::CWindow(const CString& strTitle, const Style uStyle, const Math::CSize2D& Size) :
			m_pImpl( new CWindowImpl() )
		{
			this->Init( strTitle, uStyle, Size, Math::CPoint2D() );
		}
		CWindow::CWindow(const CString& strTitle, const Style uStyle, const Math::CSize2D& Size, const Math::CPoint2D& Position) :
			m_pImpl( new CWindowImpl() )
		{
			this->Init( strTitle, uStyle, Size, Position );
		}

		void	CWindow::Init( const CString& strTitle, const Style style, const Math::CSize2D& size, const Math::CPoint2D& pos ) {
			CAutoPtr<CWindowImpl> pGuard = this->m_pImpl;

			this->m_pImpl->pWinClass = Internal::CWindowClass::GetInstance();
			this->m_pImpl->uStyle = style;

			Log::Write(L"Initializing window " + strTitle + L" of class " + m_pImpl->pWinClass->GetClassName() + L".", Log::LogLevel::Debug);
			DWORD dwStyle = 0, dwExStyle = 0;

			if(!GetMSWindowStyle(style, dwStyle, dwExStyle)){
				throw Exception::CInvalidArgumentException(L"uStyle", String::ToString(style),
					L"Unrecognized window style.", CR_INFO());
			}
			Log::Write(L"Selected window style: " + String::ToString(style) + L".", Log::LogLevel::Debug);

			HINSTANCE hInstance = GetModuleHandleW(0);

			RECT winRect = {0, 0, size.Width, size.Height};
			if(!AdjustWindowRectEx(&winRect, dwStyle, FALSE, dwExStyle)){
				CR_THROW(L"Failed to adjust client area rect.");
			}

			this->m_pImpl->hWindow = CreateWindowExW(
				dwExStyle, 
				this->m_pImpl->pWinClass->GetClassName().GetPointer(), 
				strTitle.GetPointer(), 
				dwStyle, 
				pos.X, pos.Y, 
				winRect.right - winRect.left, 
				winRect.bottom - winRect.top, 
				0, 0, hInstance, this); 

			if(this->m_pImpl->hWindow == 0 || this->m_pImpl->hWindow == INVALID_HANDLE_VALUE){
				throw Exception::CWindowException(GetLastError(),
					L"Fatal error durring window creation.", CR_INFO());
			}

			this->m_pImpl->pWinClass->AddWindow( this );

			this->OnClose.SetCombiner(ORCombiner);
			this->OnCreate.SetCombiner(ORCombiner);
			this->OnEvent.SetCombiner(ORCombiner);
			this->OnFocusChange.SetCombiner(ORCombiner);
			this->OnFocusGain.SetCombiner(ORCombiner);
			this->OnFocusLost.SetCombiner(ORCombiner);
			this->OnPositionChange.SetCombiner(ORCombiner);
			this->OnSizeChange.SetCombiner(ORCombiner);
			this->OnVisibilityChange.SetCombiner(ORCombiner);
			this->OnChar.SetCombiner(ORCombiner);
			this->OnKeyDown.SetCombiner(ORCombiner);
			this->OnKeyUp.SetCombiner(ORCombiner);
			this->OnMouseMove.SetCombiner(ORCombiner);
			this->OnMouseButtonUp.SetCombiner(ORCombiner);
			this->OnMouseButtonDown.SetCombiner(ORCombiner);

			Log::Write(L"Window initialized.", Log::LogLevel::Debug);
			pGuard.Reset();
		}

		CWindow::~CWindow(){
			Log::Write(L"Deinitializing window...", Log::LogLevel::Debug);
			if(this->m_pImpl->hWindow != 0 && this->m_pImpl->hWindow != INVALID_HANDLE_VALUE){
				if(IsWindow(this->m_pImpl->hWindow)){
					if(!DestroyWindow(this->m_pImpl->hWindow)){
						Log::Write( Exception::CWindowException(GetLastError(),
							L"Failed to destroy window.", CR_INFO()) );
					}
				}
			}
			if( this->m_pImpl != nullptr ){
				delete m_pImpl;
				this->m_pImpl = nullptr;
			}
		}

		void	CWindow::SetPosition(const Math::CPoint2D& Position){
			if(!SetWindowPos(this->m_pImpl->hWindow, 0, Position.X, Position.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)){
				throw Exception::CWindowException(GetLastError(), 
					L"Failed to set new window position. Pos: " + Position.ToString(), CR_INFO());
			}
		}

		const Math::CPoint2D	CWindow::GetPosition() const{
			RECT rect;
			Memory::SetZero(rect);
			if(!GetWindowRect(this->m_pImpl->hWindow, &rect)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to get window position.", CR_INFO());
			}
			return Math::CPoint2D(rect.left, rect.top);		
		}

		void	CWindow::SetSize(const Math::CSize2D& Size){
			DWORD dwStyle = 0, dwExStyle = 0;
			if(!GetMSWindowStyle(this->m_pImpl->uStyle, dwStyle, dwExStyle)){
				throw Exception::CInvalidArgumentException(L"uStyle", String::ToString(m_pImpl->uStyle),
					L"Unrecognized window style.", CR_INFO());
			}
			RECT winRect = {0, 0, Size.Width, Size.Height};
			if(!AdjustWindowRectEx(&winRect, dwStyle, FALSE, dwExStyle)){
				throw Exception::CWindowException(GetLastError(), 
					L"Failed to adjust client area rect.", CR_INFO());
			}
			if(!SetWindowPos(this->m_pImpl->hWindow, 0, 0, 0, winRect.right - winRect.left, winRect.bottom - winRect.top, SWP_NOMOVE | SWP_NOZORDER)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to set new window size, Size: " + Size.ToString(), CR_INFO());
			}
		}

		const Math::CSize2D	CWindow::GetSize() const{
			RECT rect;
			Memory::SetZero(rect);
			if(!GetClientRect(this->m_pImpl->hWindow, &rect)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to get window size.", CR_INFO());
			}
			return Math::CSize2D(rect.right - rect.left, rect.bottom - rect.top);
		}

		void	CWindow::SetRect( const Math::CRectangle& Rect ){
			DWORD dwStyle, dwExStyle;
			if(!GetMSWindowStyle(this->m_pImpl->uStyle, dwStyle, dwExStyle)){
				throw Exception::CInvalidArgumentException(L"uStyle", String::ToString(m_pImpl->uStyle),
					L"Unrecognized window style.", CR_INFO());
			}
			RECT winRect = {0, 0, Rect.Size.Width, Rect.Size.Height};
			if(!AdjustWindowRectEx(&winRect, dwStyle, FALSE, dwExStyle)){
				throw Exception::CWindowException(GetLastError(), 
					L"Failed to adjust client area rect.", CR_INFO());
			}
			if(!SetWindowPos(this->m_pImpl->hWindow, 0, Rect.Position.X, Rect.Position.Y, winRect.right - winRect.left, winRect.bottom - winRect.top, SWP_NOZORDER)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to set new window rect, Size: " + Rect.ToString(), CR_INFO());
			}
		}

		const Math::CRectangle	CWindow::GetRect() const{
			Math::CRectangle result;
			RECT rect;
			Memory::SetZero(rect);
			if(!GetWindowRect(this->m_pImpl->hWindow, &rect)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to get window position.", CR_INFO());
			}
			result.Position.Set( rect.left, rect.top );
			Memory::SetZero(rect);
			if(!GetClientRect(this->m_pImpl->hWindow, &rect)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to get window size.", CR_INFO());
			}
			result.Size.Set( rect.right - rect.left, rect.bottom - rect.top );

			return result;
		}

		void	CWindow::SetVisible(const bool bVisible){
			ShowWindow(this->m_pImpl->hWindow, bVisible ? SW_SHOW : SW_HIDE);
		}

		const bool	CWindow::IsVisible() const{
			if(IsWindowVisible(this->m_pImpl->hWindow)){
				return true;
			}
			return false;
		}

		void	CWindow::SetTitle(const CString& strTitle){
			if(!SetWindowTextW(this->m_pImpl->hWindow, strTitle.GetPointer())){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to set new window title, Title: " + strTitle, CR_INFO());
			}
		}

		const CString	CWindow::GetTitle() const{
			int iLen = GetWindowTextLengthW(this->m_pImpl->hWindow);
			if(iLen == 0){
				return L"";
			}

			if(iLen < 0){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to get window title.", CR_INFO());
			}

			CString result;
			result.Resize(iLen+1);

			if(!GetWindowTextW(this->m_pImpl->hWindow, &result[0], iLen + 1)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to get window title.", CR_INFO());
			}

			result = result.Trim();
			return result;
		}

		void	CWindow::SetStyle(const Graphic::Style uStyle){
			DWORD dwStyle = 0, dwExStyle = 0;
			if(!GetMSWindowStyle(uStyle, dwStyle, dwExStyle)){
				throw Exception::CInvalidArgumentException(L"uStyle", String::ToString(uStyle),
					L"Unrecognized window style.", CR_INFO());
			}
			Log::Write(L"Changed window style to: " + String::ToString(uStyle) + L".", Log::LogLevel::Debug);

			SetWindowLongW(this->m_pImpl->hWindow, GWL_STYLE, (LONG)dwStyle);
			SetWindowLongW(this->m_pImpl->hWindow, GWL_EXSTYLE, (LONG)dwExStyle);
			m_pImpl->uStyle = uStyle;
		}

		const Graphic::Style	CWindow::GetStyle() const{
			return this->m_pImpl->uStyle;
		}

		void*	CWindow::GetHandle() const{
			return reinterpret_cast<void*>(this->m_pImpl->hWindow);
		}

		void	CWindow::ProcessEvents(){
			ProcessEvents(0);
		}

		void	CWindow::ProcessEvents(const uint32 uMaxEvents){
			MSG msg;
			uint32 uNumEvents = uMaxEvents != 0 ? uMaxEvents : 0xFFFFFFFF;

			Memory::SetZero(msg);
			for(uint32 uIndex = 0; PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) && uIndex < uNumEvents; uIndex++){
				TranslateMessage(&msg);
				DispatchMessageW(&msg);

				Memory::SetZero(msg);
			}
		}
	}
}