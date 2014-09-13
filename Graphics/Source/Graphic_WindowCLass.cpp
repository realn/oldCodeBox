#include "stdafx.h"
#include "../Internal/Graphic_WindowClass.h"
#include "../Include/Graphic_Window.h"

#include <windowsx.h>

#include <Logger.h>
#include <Math_Point2D.h>
#include <Math_Size2D.h>
#include <Collection_Funcs.h>

namespace CB{
	namespace Manage{
		Internal::CWindowClass*	CRefSingleton<Internal::CWindowClass>::ms_pInstance;
	}
	namespace Internal{

		CWindowClass::CWindowClass() :
			m_strClassName( L"SimpleGraphicWindowCLS" )
		{
			Log::Write(L"Initialzing window class...");

			WNDCLASSEXW winClass;
			Memory::SetZero(winClass);

			winClass.cbSize = sizeof(WNDCLASSEXW);
			winClass.lpszClassName = this->m_strClassName.GetPointer();
			winClass.hInstance = GetModuleHandleW(0);
			winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			winClass.lpfnWndProc = staticWindowCallback;
			winClass.cbClsExtra = 0;
			winClass.cbWndExtra = 0;
			winClass.hbrBackground = CreateSolidBrush(RGB(0,0,0));
			winClass.hCursor = LoadCursorW(0, IDC_ARROW);
			winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
			winClass.hIconSm = 0;
			winClass.lpszMenuName = 0;

			Log::Write(L"Creating window class " + this->m_strClassName + L"...", Log::LogLevel::Debug);
			if(!RegisterClassExW(&winClass)){
				throw Exception::CWindowException(GetLastError(),
					L"Failed to register class " + this->m_strClassName, __FUNCTIONW__, __FILEW__, __LINE__);
			}

			this->InitMessageMap();
		}

		CWindowClass::~CWindowClass(){
			Log::Write(L"Deinitializing window class...");
			Log::Write(L"Destroing window class " + this->m_strClassName + L"...", Log::LogLevel::Debug);
			if(!UnregisterClassW(this->m_strClassName.GetPointer(), GetModuleHandleW(0))){
				Log::Write(L"Failed to unregister window class " + this->m_strClassName + L".", Log::LogLevel::Error);
			}
		}

		void	CWindowClass::AddWindow( CPtr<Graphic::CWindow> pWindow ){
			if( !Collection::Contains( this->m_WindowList, pWindow ) ){
				this->m_WindowList.Add( pWindow );
			}
		}

		void	CWindowClass::RemoveWindow( CPtr<Graphic::CWindow> pWindow ){
			uint32 uIndex = 0;
			if( Collection::TryFind( this->m_WindowList, pWindow, uIndex ) ){
				this->m_WindowList.Remove( uIndex );
			}
		}

		const CString	CWindowClass::GetClassName() const{
			return this->m_strClassName;
		}

		void	CWindowClass::InitMessageMap(){
			this->m_MessageMap.Add( WM_CREATE, MessageMethod( this, &CWindowClass::MessageCreate ) );
			this->m_MessageMap.Add( WM_CLOSE, MessageMethod( this, &CWindowClass::MessageClose ) );
			this->m_MessageMap.Add( WM_SIZE, MessageMethod( this, &CWindowClass::MessageSize ) );
			this->m_MessageMap.Add( WM_MOVE, MessageMethod( this, &CWindowClass::MessageMove ) );
			this->m_MessageMap.Add( WM_SHOWWINDOW, MessageMethod( this, &CWindowClass::MessageShowWindow ) );
			this->m_MessageMap.Add( WM_ACTIVATE, MessageMethod( this, &CWindowClass::MessageActivate ) );
			this->m_MessageMap.Add( WM_KEYDOWN, MessageMethod( this, &CWindowClass::MessageKey ) );
			this->m_MessageMap.Add( WM_KEYUP, MessageMethod( this, &CWindowClass::MessageKey ) );
			this->m_MessageMap.Add( WM_CHAR, MessageMethod( this, &CWindowClass::MessageChar ) );
			this->m_MessageMap.Add( WM_MOUSEMOVE, MessageMethod( this, &CWindowClass::MessageMouseMove ) );
			this->m_MessageMap.Add( WM_LBUTTONUP, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
			this->m_MessageMap.Add( WM_RBUTTONUP, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
			this->m_MessageMap.Add( WM_MBUTTONUP, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
			this->m_MessageMap.Add( WM_XBUTTONUP, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
			this->m_MessageMap.Add( WM_LBUTTONDOWN, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
			this->m_MessageMap.Add( WM_RBUTTONDOWN, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
			this->m_MessageMap.Add( WM_MBUTTONDOWN, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
			this->m_MessageMap.Add( WM_XBUTTONDOWN, MessageMethod( this, &CWindowClass::MessageMouseKey ) );
		}

		LRESULT CALLBACK	CWindowClass::staticWindowCallback( HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			CRefPtr<CWindowClass> pClass = CWindowClass::GetInstance();
			
			return pClass->WindowCallback( hWindow, uMsg, wParam, lParam );
		}

		const bool	CompareWinHandle( const CPtr<Graphic::CWindow>& pWindow, const HWND& hWindow ){
			return pWindow->GetHandle() == hWindow;
		}

		int	CWindowClass::WindowCallback( HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			uint32 uIndex = 0;
			if(!Collection::TryFind( this->m_WindowList, CompareWinHandle, hWindow, uIndex ) )
				return DefWindowProcW( hWindow, uMsg, wParam, lParam );

			Graphic::CWindow& window = *this->m_WindowList[uIndex];

			if( this->m_MessageMap.Contains( uMsg ) ){
				return this->m_MessageMap[(MessageID)uMsg]( window, uMsg, wParam, lParam );
			}
			
			if(window.OnEvent.IsValid()){
				if( window.OnEvent(window, uMsg, wParam, lParam) )
					return 0;
			}

			return DefWindowProcW( hWindow, uMsg, wParam, lParam );
		}

		const bool	CWindowClass::TryGetVirtualKey(const uint32 uKeyCode, Graphic::VirtualKey& uKeyOut){
			uKeyOut = Graphic::VirtualKey::Undefined;
			switch (uKeyCode)
			{
			#define CR_DEFVK(_KEY, _CODE)	case _CODE:	uKeyOut = Graphic::VirtualKey::_KEY; return true;
			#include "../Include/VirtualKeys.incl"
			#undef CR_DEFVK
			default:
				return false;
			}
		}

		const bool	CWindowClass::TryGetMouseVirtualButton(const uint32 uMsg, const WPARAM wParam, Graphic::VirtualKey& uKeyOut){
			switch (uMsg)
			{
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_LBUTTONDBLCLK:	
				uKeyOut = Graphic::VirtualKey::LBUTTON;	
				return true;

			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_RBUTTONDBLCLK:
				uKeyOut = Graphic::VirtualKey::RBUTTON;
				return true;

			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_MBUTTONDBLCLK:
				uKeyOut = Graphic::VirtualKey::MBUTTON;
				return true;

			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
			case WM_XBUTTONDBLCLK:
				switch (GET_XBUTTON_WPARAM(wParam))
				{
				case 0x01:	uKeyOut = Graphic::VirtualKey::XBUTTON1;	return true;
				case 0x02:	uKeyOut = Graphic::VirtualKey::XBUTTON2;	return true;
				default:
					return false;
				}

			default:
				return false;
			}
		}

		int32	CWindowClass::MessageCreate( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			if(window.OnCreate.IsValid()){
				if( window.OnCreate(window) )
					return 0;
			}
			
			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}
		
		int32	CWindowClass::MessageClose(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			if(window.OnClose.IsValid()){
				if( window.OnClose(window) )
					return 0;
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageSize(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			switch (wParam){
			case SIZE_RESTORED:	
				if(window.OnSizeChange.IsValid()){
					if(window.OnSizeChange(window, Math::CSize2D(LOWORD(lParam), HIWORD(lParam)), window.GetSize()))
						return 0;
				}
				break;
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageMove(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			if(window.OnPositionChange.IsValid()){
				if( window.OnPositionChange(window, Math::CPoint2D(LOWORD(lParam), HIWORD(lParam)), window.GetPosition()) )
					return 0;
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageShowWindow(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			if(window.OnVisibilityChange.IsValid()){
				if( window.OnVisibilityChange(window, wParam == TRUE ? true : false, window.IsVisible()) )
					return 0;
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageActivate(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			bool bResult = false;
			if(LOWORD(wParam) > 0){
				if(window.OnFocusGain.IsValid()){
					bResult = window.OnFocusGain(window);
				}
			}
			else{
				if(window.OnFocusLost.IsValid()){
					bResult = window.OnFocusLost(window);
				}
			}
			if(window.OnFocusChange.IsValid()){
				bResult = window.OnFocusChange(window, LOWORD(wParam) > 0) || bResult;
			}

			if( bResult )
				return 0;

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageKey(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			Graphic::VirtualKey uKey = Graphic::VirtualKey::Undefined;
			if( TryGetVirtualKey((uint32)wParam, uKey) ){
				if( uMsg == WM_KEYDOWN && window.OnKeyDown.IsValid() ){
					if( window.OnKeyDown(window, uKey) ){
						return 0;
					}
				}
				else if( uMsg == WM_KEYUP && window.OnKeyUp.IsValid() ){
					if( window.OnKeyUp( window, uKey ) ){
						return 0;
					}
				}
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageChar(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			if(window.OnChar.IsValid()){
				if( window.OnChar(window, wParam) )
					return 0;
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageMouseMove(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			if(window.OnMouseMove.IsValid()){
				int32 iX = GET_X_LPARAM(lParam);
				int32 iY = GET_Y_LPARAM(lParam);
				if( window.OnMouseMove(window, Math::CPoint2D(iX, iY) ) )
					return 0;
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}

		int32	CWindowClass::MessageMouseKey(Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam ){
			Graphic::VirtualKey uKey = Graphic::VirtualKey::Undefined;
			if( this->TryGetMouseVirtualButton( uMsg, wParam, uKey ) ){
				switch( uMsg ){
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_XBUTTONDOWN:
					if(window.OnMouseButtonDown.IsValid()){
						if( window.OnMouseButtonDown(window, uKey) )
							return 0;
					}
					break;

				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
				case WM_MBUTTONUP:
				case WM_XBUTTONUP:
					if( window.OnMouseButtonUp.IsValid() ){
						if( window.OnMouseButtonUp(window, uKey) )
							return 0;
					}
					break;
				}
			}

			return DefWindowProcW( reinterpret_cast<HWND>(window.GetHandle()), uMsg, wParam, lParam );
		}
	}
}