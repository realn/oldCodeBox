#pragma once

#include "../../WindowDrvInterface/Include/WindowDriver.h"
#include "WinPlatform.h"

namespace CB{
	//====================================
	//	Device Context Interface
	//====================================
	class IDeviceContext{
	public:
		virtual HDC&	Get() const = 0;
	};

	//====================================
	//	Pure Device Context class
	//====================================
	class CDeviceContext :
		public IDeviceContext
	{
	private:
		mutable HDC m_hDC;

	public:
		CDeviceContext() : 
			m_hDC(0)
		{}
		CDeviceContext(HDC hDC) : 
			m_hDC(hDC)
		{}
		~CDeviceContext(){ 
			if(m_hDC){ 
				DeleteDC(m_hDC); 
				m_hDC = 0; 
			} 
		}

		const CDeviceContext&	operator=(HDC hDC){
			this->m_hDC = hDC;
			return *this;
		}

		HDC& Get() const override { 
			return m_hDC; 
		}
	};

	class CWindowDeviceContext :
		public IDeviceContext
	{
	private:
		CRefPtr<CB::Window::IWindow> m_pWindow;
		mutable HDC m_hDC;

	public:
		CWindowDeviceContext() : 
			m_hDC(0)
		{}
		CWindowDeviceContext(CRefPtr<Window::IWindow> pWindow) :
			m_pWindow(pWindow),
			m_hDC(GetDC((HWND)pWindow->GetHandle()))
		{}
		~CWindowDeviceContext(){ 
			this->Release();
		}

		void	Release(){
			if(m_hDC){ 
				ReleaseDC((HWND)this->m_pWindow->GetHandle(), this->m_hDC); 
				m_hDC = 0; 
			} 
		}

		const CWindowDeviceContext&	operator=(CRefPtr<Window::IWindow> pWindow){
			this->Release();
			this->m_pWindow = pWindow;
			this->m_hDC = GetDC((HWND)this->m_pWindow->GetHandle());
			return *this;
		}

		CRefPtr<Window::IWindow>	GetWindow() const {
			return this->m_pWindow;
		}
		HDC&	Get() const override { 
			return m_hDC; 
		}
	};

	class CGLContext{
	private:
		mutable HGLRC	m_GLContext;

	public:
		CGLContext() :
			m_GLContext(0)
		{
		}
		CGLContext(const IDeviceContext& DC) : 
			m_GLContext(0)
		{
			this->CreateContext(DC);
		}
		~CGLContext(){
			this->Free();
		}

		void	Free(){
			if(this->m_GLContext){
				wglMakeCurrent(0, 0);
				wglDeleteContext(this->m_GLContext);
				this->m_GLContext = 0;
			}
		}

		void	Bind(const IDeviceContext& DC){
			if(!wglMakeCurrent(DC.Get(), this->m_GLContext)){
				CR_THROWWIN(GetLastError(), L"Failed to make gl render context current.");
			}
		}
		void	Unbind(){
			wglMakeCurrent(0, 0);
		}

		HGLRC&	Get() const {
			return this->m_GLContext;
		}

		void	CreateContext(const IDeviceContext& DC){
			this->Free();

			this->m_GLContext = wglCreateContext(DC.Get());
			if(this->m_GLContext == 0){
				CR_THROWWIN(GetLastError(), L"Failed to create GL Legacy Context.");
			}
		}
	};
}