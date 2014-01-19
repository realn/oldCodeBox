#include "../Internal/Window.h"
#include "../../Common/Include/WindowsErrors.h"
#include "../../Common/Include/Logger.h"

namespace CB{
	const bool	GetMSWindowStyle(const Window::Style uStyle, DWORD& dwOutStyle, DWORD& dwOutExStyle){
		switch (uStyle)
		{
		case Window::Style::Pure:
			dwOutStyle = WS_OVERLAPPED;
			dwOutExStyle = 0;
			return true;

		case Window::Style::Single:
			dwOutStyle = WS_OVERLAPPEDWINDOW;
			dwOutExStyle = 0;
			return true;

		case Window::Style::Sizeable:
			dwOutStyle = WS_OVERLAPPEDWINDOW;
			dwOutExStyle = WS_OVERLAPPEDWINDOW;
			return true;

		case Window::Style::ToolWindow:
			dwOutStyle = WS_OVERLAPPEDWINDOW;
			dwOutExStyle = WS_EX_TOOLWINDOW;
			return true;

		case Window::Style::SizeableToolWindow:
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

	CWindow::CWindow(CRefPtr<CWindowManager> pMng, const CString& strClass, const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size, const Math::CPoint& Position) :
		Manage::IManagedObject<CWindowManager, CWindow>(pMng), 
		m_hWindow(0),
		m_uStyle(uStyle)
	{
		Log::Write(L"Initializing window " + strTitle + L" of class " + strClass + L".", Log::LogLevel::Debug);
		DWORD dwStyle = 0, dwExStyle = 0;

		if(!GetMSWindowStyle(uStyle, dwStyle, dwExStyle)){
			throw Exception::CInvalidArgumentException(L"uStyle", String::ToString(uStyle),
				L"Unrecognized window style.", CR_INFO());
		}
		Log::Write(L"Selected window style: " + String::ToString(uStyle) + L".", Log::LogLevel::Debug);

		HINSTANCE hInstance = GetModuleHandleW(0);

		RECT winRect = {0, 0, Size.Width, Size.Height};
		if(!AdjustWindowRectEx(&winRect, dwStyle, FALSE, dwExStyle)){
			CR_THROW(L"Failed to adjust client area rect.");
		}

		this->m_hWindow = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, strClass.GetPointer(), strTitle.GetPointer(), WS_OVERLAPPEDWINDOW, 
			Position.X, Position.Y, winRect.right - winRect.left, winRect.bottom - winRect.top, 0, 0, hInstance, this); 

		if(this->m_hWindow == 0 || this->m_hWindow == INVALID_HANDLE_VALUE){
			throw Exception::CWindowException(GetLastError(),
				L"Fatal error durring window creation.", CR_INFO());
		}

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
	}

	CWindow::~CWindow(){
		try{
			Log::Write(L"Deinitializing window...", Log::LogLevel::Debug);
			if(this->m_hWindow != 0 && this->m_hWindow != INVALID_HANDLE_VALUE){
				if(IsWindow(this->m_hWindow)){
					SetWindowLongPtrW(this->m_hWindow, GWLP_USERDATA, 0);
					if(!DestroyWindow(this->m_hWindow)){
						throw Exception::CWindowException(GetLastError(),
							L"Failed to destroy window.", CR_INFO());
					}
				}
				this->m_hWindow = 0;
			}
		}
		catch(Exception::CException& Exception){
			Log::Write(Exception);
		}
	}

	const uint32	CWindow::GetApiId() const{
		return g_uApiId;
	}

	CRefPtr<Window::IManager>	CWindow::GetManager() const{
		return this->m_pParent.Cast<Window::IManager>();
	}

	void	CWindow::SetPosition(const Math::CPoint& Position){
		if(!SetWindowPos(this->m_hWindow, 0, Position.X, Position.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)){
			throw Exception::CWindowException(GetLastError(), 
				L"Failed to set new window position. Pos: " + Position.ToString(), CR_INFO());
		}
	}

	const Math::CPoint	CWindow::GetPosition() const{
		RECT rect;
		Memory::SetZero(rect);
		if(!GetWindowRect(this->m_hWindow, &rect)){
			throw Exception::CWindowException(GetLastError(),
				L"Failed to get window position.", CR_INFO());
		}
		return Math::CPoint(rect.left, rect.top);		
	}

	void	CWindow::SetSize(const Math::CSize& Size){
		DWORD dwStyle = 0, dwExStyle = 0;
		if(!GetMSWindowStyle(this->m_uStyle, dwStyle, dwExStyle)){
			throw Exception::CInvalidArgumentException(L"uStyle", String::ToString(m_uStyle),
				L"Unrecognized window style.", CR_INFO());
		}
		RECT winRect = {0, 0, Size.Width, Size.Height};
		if(!AdjustWindowRectEx(&winRect, dwStyle, FALSE, dwExStyle)){
			throw Exception::CWindowException(GetLastError(), 
				L"Failed to adjust client area rect.", CR_INFO());
		}
		if(!SetWindowPos(this->m_hWindow, 0, 0, 0, winRect.right - winRect.left, winRect.bottom - winRect.top, SWP_NOMOVE | SWP_NOZORDER)){
			throw Exception::CWindowException(GetLastError(),
				L"Failed to set new window size, Size: " + Size.ToString(), CR_INFO());
		}
	}

	const Math::CSize	CWindow::GetSize() const{
		RECT rect;
		Memory::SetZero(rect);
		if(!GetClientRect(this->m_hWindow, &rect)){
			throw Exception::CWindowException(GetLastError(),
				L"Failed to get window size.", CR_INFO());
		}
		return Math::CSize(rect.right - rect.left, rect.bottom - rect.top);
	}

	void	CWindow::SetVisible(const bool bVisible){
		ShowWindow(this->m_hWindow, bVisible ? SW_SHOW : SW_HIDE);
	}

	const bool	CWindow::IsVisible() const{
		if(IsWindowVisible(this->m_hWindow)){
			return true;
		}
		return false;
	}

	void	CWindow::SetTitle(const CString& strTitle){
		if(!SetWindowTextW(this->m_hWindow, strTitle.GetPointer())){
			throw Exception::CWindowException(GetLastError(),
				L"Failed to set new window title, Title: " + strTitle, CR_INFO());
		}
	}

	const CString	CWindow::GetTitle() const{
		int iLen = GetWindowTextLengthW(this->m_hWindow);
		if(iLen == 0){
			return L"";
		}

		if(iLen < 0){
			throw Exception::CWindowException(GetLastError(),
				L"Failed to get window title.", CR_INFO());
		}

		CString result;
		result.Resize(iLen+1);

		if(!GetWindowTextW(this->m_hWindow, &result[0], iLen + 1)){
			throw Exception::CWindowException(GetLastError(),
				L"Failed to get window title.", CR_INFO());
		}

		result = result.Trim();
		return result;
	}

	void	CWindow::SetStyle(const Window::Style uStyle){
		DWORD dwStyle = 0, dwExStyle = 0;
		if(!GetMSWindowStyle(uStyle, dwStyle, dwExStyle)){
			throw Exception::CInvalidArgumentException(L"uStyle", String::ToString(uStyle),
				L"Unrecognized window style.", CR_INFO());
		}
		Log::Write(L"Changed window style to: " + String::ToString(uStyle) + L".", Log::LogLevel::Debug);

		SetWindowLongW(this->m_hWindow, GWL_STYLE, (LONG)dwStyle);
		SetWindowLongW(this->m_hWindow, GWL_EXSTYLE, (LONG)dwExStyle);
		m_uStyle = uStyle;
	}

	const Window::Style	CWindow::GetStyle() const{
		return this->m_uStyle;
	}

	void*	CWindow::GetHandle() const{
		return static_cast<void*>(this->m_hWindow);
	}

	const bool	CWindow::ProcessMessage(const uint32 uMessage, const WPARAM wParam, const LPARAM lParam){
		switch (uMessage)
		{
		case WM_CREATE:	
			if(this->OnCreate.IsValid()){
				return this->OnCreate(this);
			}
			break;

		case WM_CLOSE:	
			if(this->OnClose.IsValid()){
				return this->OnClose(this);
			}
			break;

		case WM_SIZE:
			switch (wParam){
			case SIZE_RESTORED:	
				if(this->OnSizeChange.IsValid()){
					return this->OnSizeChange(this, Math::CSize(LOWORD(lParam), HIWORD(lParam)), this->GetSize());
				}
				break;
			}
			break;

		case WM_MOVE:	
			if(this->OnPositionChange.IsValid()){
				return this->OnPositionChange(this, Math::CPoint(LOWORD(lParam), HIWORD(lParam)), this->GetPosition());
			}
			break;

		case WM_SHOWWINDOW:	
			if(this->OnVisibilityChange.IsValid()){
				return this->OnVisibilityChange(this, wParam == TRUE ? true : false, this->IsVisible());
			}
			break;

		case WM_ACTIVATE:
			{
				bool bResult = false;
				if(LOWORD(wParam) > 0){
					if(this->OnFocusGain.IsValid()){
						bResult = this->OnFocusGain(this);
					}
				}
				else{
					if(this->OnFocusLost.IsValid()){
						bResult = this->OnFocusLost(this);
					}
				}
				if(this->OnFocusChange.IsValid()){
					return this->OnFocusChange(this, LOWORD(wParam) > 0) || bResult;
				}
				return bResult;
			}
			break;

		case WM_KEYDOWN:
			{
				Window::VirtualKey uKey = Window::VirtualKey::Undefined;
				if(this->OnKeyDown.IsValid() && TryGetVirtualKey((uint32)wParam, uKey)){
					return this->OnKeyDown(this, uKey);
				}
				return false;
			}
			break;

		case WM_KEYUP:
			{
				Window::VirtualKey uKey = Window::VirtualKey::Undefined;
				if(this->OnKeyUp.IsValid() && TryGetVirtualKey((uint32)wParam, uKey)){
					return this->OnKeyUp(this, uKey);
				}
				return false;
			}
			break;

		case WM_CHAR:
			{
				if(this->OnChar.IsValid()){
					return this->OnChar(this, wParam);
				}
				return false;
			}
			break;

		case WM_MOUSEMOVE:
			{
				if(this->OnMouseMove.IsValid()){
					int32 iX = GET_X_LPARAM(lParam);
					int32 iY = GET_Y_LPARAM(lParam);
					return this->OnMouseMove(this, Math::CPoint(iX, iY));
				}
				return false;
			}
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
			{
				Window::VirtualKey uKey = Window::VirtualKey::Undefined;
				if(this->OnMouseButtonDown.IsValid() && TryGetMouseVirtualButton(uMessage, wParam, uKey)){
					return this->OnMouseButtonDown(this, uKey);
				}
				return false;
			}
			break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
			{
				Window::VirtualKey uKey = Window::VirtualKey::Undefined;
				if(this->OnMouseButtonUp.IsValid() && TryGetMouseVirtualButton(uMessage, wParam, uKey)){
					return this->OnMouseButtonUp(this, uKey);
				}
				return false;
			}
			break;

		default:
			if(this->OnEvent.IsValid()){
				return this->OnEvent(this, uMessage, wParam, lParam);
			}
		}
		return false;
	}

	const bool	CWindow::TryGetVirtualKey(const uint32 uKeyCode, Window::VirtualKey& uKeyOut){
		uKeyOut = Window::VirtualKey::Undefined;
		switch (uKeyCode)
		{
		#define CR_DEFVK(_KEY, _CODE)	case _CODE:	uKeyOut = Window::VirtualKey::_KEY; return true;
		#include <VirtualKeys.incl>
		#undef CR_DEFVK
		default:
			return false;
		}
	}

	const bool	CWindow::TryGetMouseVirtualButton(const uint32 uMsg, const WPARAM wParam, Window::VirtualKey& uKeyOut){
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:	
			uKeyOut = Window::VirtualKey::LBUTTON;	
			return true;

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
			uKeyOut = Window::VirtualKey::RBUTTON;
			return true;

		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
			uKeyOut = Window::VirtualKey::MBUTTON;
			return true;

		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_XBUTTONDBLCLK:
			switch (GET_XBUTTON_WPARAM(wParam))
			{
			case 0x01:	uKeyOut = Window::VirtualKey::XBUTTON1;	return true;
			case 0x02:	uKeyOut = Window::VirtualKey::XBUTTON2;	return true;
			default:
				return false;
			}

		default:
			return false;
		}
	}
}