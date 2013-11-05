#include "../Internal/Manager.h"
#include "../Internal/Window.h"
#include <Math.h>
#include <Logger.h>

LRESULT CALLBACK WndCallbackProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace CB{
	const uint32	g_uApiId = *((uint32*)"MSW5");

	CWindowManager::CWindowManager(CRefPtr<Window::IDriver> pDriver) :
		m_pDriver(pDriver),
		m_strClassName(L"WINCLS_" + String::ToString(Math::RandUInt32()))
	{
		Log::Write(L"Initialzing window manager...");

		WNDCLASSEXW winClass;
		Memory::SetZero(winClass);

		winClass.cbSize = sizeof(WNDCLASSEXW);
		winClass.lpszClassName = this->m_strClassName.GetPointer();
		winClass.hInstance = GetModuleHandleW(0);
		winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		winClass.lpfnWndProc = WndCallbackProc;
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
	}

	CWindowManager::~CWindowManager(){
		Log::Write(L"Deinitializing window manager...");
		Log::Write(L"Destroing window class " + this->m_strClassName + L"...", Log::LogLevel::Debug);
		if(!UnregisterClassW(this->m_strClassName.GetPointer(), GetModuleHandleW(0))){
			Log::Write(L"Failed to unregister window class " + this->m_strClassName + L".", Log::LogLevel::Error);
		}
	}

	const uint32	CWindowManager::GetApiId() const{
		return g_uApiId;
	}

	CRefPtr<Window::IWindow>	CWindowManager::CreateWindow(const CString& strTitle, const Window::Style uStyle){
		return this->CreateWindow(strTitle, uStyle, Math::CSize(640, 480), Math::CPoint(0, 0));
	}

	CRefPtr<Window::IWindow>	CWindowManager::CreateWindow(const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size){
		return this->CreateWindow(strTitle, uStyle, Size, Math::CPoint(0, 0));
	}

	CRefPtr<Window::IWindow>	CWindowManager::CreateWindow(const CString& strTitle, const Window::Style uStyle, const Math::CSize& Size, const Math::CPoint& Position){
		return new CWindow(this, this->m_strClassName, strTitle, uStyle, Size, Position);
	}

	void	CWindowManager::ProcessEvents(){
		this->ProcessEvents(0);
	}

	void	CWindowManager::ProcessEvents(const uint32 uMaxEvents){
		MSG msg;
		uint32 uNumEvents = uMaxEvents != 0 ? uMaxEvents : 0xFFFFFFFF;

		for(uint32 uIndex = 0; uIndex < this->m_pObjectList.GetLength(); uIndex++){
			Memory::SetZero(msg);

			HWND hWindow = static_cast<HWND>(this->m_pObjectList[uIndex].Get()->GetHandle());

			for(uint32 uIndex = 0; PeekMessageW(&msg, hWindow, 0, 0, PM_REMOVE) && uIndex < uNumEvents; uIndex++){
				TranslateMessage(&msg);
				DispatchMessageW(&msg);

				Memory::SetZero(msg);
			}
		}
	}

	const bool CWindowManager::SupportsMultiWindow() const{
		return true;
	}

	const bool	CWindowManager::SupportsStyle(const Window::Style uStyle) const{
		switch (uStyle){
		case Window::Style::Pure:		return true;
		case Window::Style::Single:		return true;
		case Window::Style::Sizeable:	return true;
		case Window::Style::SizeableToolWindow:	return true;
		case Window::Style::ToolWindow:	return true;
		default:
			return false;
		}
	}
}

LRESULT CALLBACK WndCallbackProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam){
	if(uMsg == WM_CREATE){
		LPCREATESTRUCTW pCreate = reinterpret_cast<LPCREATESTRUCTW>(lParam);

		CB::CWindow* pWindow = reinterpret_cast<CB::CWindow*>(pCreate->lpCreateParams);
		
		SetWindowLongPtrW(hWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));

		return DefWindowProcW(hWindow, uMsg, wParam, lParam);
	}
	if(uMsg == WM_DESTROY || uMsg == WM_NCDESTROY){
		return DefWindowProcW(hWindow, uMsg, wParam, lParam);
	}

	LONG_PTR lngWin = GetWindowLongPtrW(hWindow, GWLP_USERDATA);
	if(lngWin == 0){
		return DefWindowProcW(hWindow, uMsg, wParam, lParam);
	}

	CB::CRefPtr<CB::CWindow> pWindow = reinterpret_cast<CB::CWindow*>(lngWin);

	if(pWindow->ProcessMessage(uMsg, wParam, lParam))
		return 0;

	return DefWindowProcW(hWindow, uMsg, wParam, lParam);
}
