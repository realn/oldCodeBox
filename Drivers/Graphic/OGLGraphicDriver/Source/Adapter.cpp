#include "../Internal/Adapter.h"
#include "../Internal/Utils.h"
#include "../Internal/Output.h"
#include "../Internal/Device.h"
#include "../Internal/DisplayDeviceInfo.h"

namespace CB{
	COGLAdapter::COGLAdapter(CRefPtr<COGLManager> pManager, const uint32 uIndex, const CDisplayDeviceInfo& DeviceInfo) :
		IManagedObject<COGLManager, COGLAdapter>(pManager),
		m_uIndex(uIndex),
		m_strDeviceID(DeviceInfo.strDeviceId),
		m_DeviceInfo(DeviceInfo),
		m_strName(DeviceInfo.strDeviceName)
	{
		Log::Write(L"Initializing OGL Adapter: " + m_strName);
	}

	COGLAdapter::~COGLAdapter(){
		Log::Write(L"Deinitializing OGL Adapter: " + m_strName);
	}

	const uint32	COGLAdapter::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IManager>	COGLAdapter::GetManager() const{
		return this->GetParent().Cast<Graphic::IManager>();
	}

	const uint32	COGLAdapter::GetIndex() const{
		return this->m_uIndex;
	}

	const CString	COGLAdapter::GetName() const{
		return this->m_strName;
	}

	const uint32	COGLAdapter::GetNumberOfOutputs() const{
		return this->m_DeviceInfo.strDisplayList.GetLength();
	}

	const bool	CompareOutput(const CPtr<COGLOutput>& pOutput, const uint32& uIndex){
		return pOutput->GetIndex() == uIndex;
	}

	CRefPtr<Graphic::IOutput>	COGLAdapter::GetOutput(const uint32 uIndex){
		uint32 uOutIndex = 0;
		if(Collection::TryFind(Manage::IObjectManager<COGLOutput>::m_pObjectList, CompareOutput, uIndex, uOutIndex)){
			return Manage::IObjectManager<COGLOutput>::m_pObjectList[uOutIndex].Get();
		}

		return new COGLOutput(this, uIndex, this->m_DeviceInfo.strDisplayList[uIndex]);
	}

	CRefPtr<Graphic::IOutput>	COGLAdapter::GetDefaultOutput(){
		return this->GetOutput(0);
	}

	CRefPtr<Graphic::IOutput>	COGLAdapter::GetOutputForWindow(CRefPtr<Window::IWindow> pWindow){
		HMONITOR hMonitor = MonitorFromWindow(reinterpret_cast<HWND>(pWindow->GetHandle()), MONITOR_DEFAULTTONEAREST);
		if(hMonitor == 0){
			CR_THROWWIN(GetLastError(), L"Failed search for output for window " + pWindow->GetTitle());
		}

		MONITORINFOEXW info;
		Memory::SetZero(info);
		info.cbSize = sizeof(MONITORINFOEXW);

		if(!GetMonitorInfoW(hMonitor, &info)){
			CR_THROWWIN(GetLastError(), L"Failed to retrive information for output for window " + pWindow->GetTitle());
		}

		if(!this->m_DeviceInfo.strDisplayList.Contains(info.szDevice)){
			CR_THROW(L"Display output " + CString(info.szDevice) + L" for window " + pWindow->GetTitle() + L" does not belong to adapter " + this->m_strName);
		}

		return this->GetOutput(this->m_DeviceInfo.strDisplayList.IndexOf(info.szDevice));
	}

	CRefPtr<Graphic::IDevice>	COGLAdapter::CreateDevice(CRefPtr<Window::IWindow> pFocusWindow, const Graphic::CDeviceDesc& Desc, const Collection::ICountable<Graphic::FeatureLevel>& FeatureLevels){
		CRefPtr<Window::IWindow> pWindow = Desc.OutputWindow.IsValid() ? Desc.OutputWindow : pFocusWindow;

		return this->CreateDevice(pFocusWindow, Desc, FeatureLevels, this->GetOutputForWindow(pWindow));
	}

	CRefPtr<Graphic::IDevice>	COGLAdapter::CreateDevice(CRefPtr<Window::IWindow> pFocusWindow, const Graphic::CDeviceDesc& Desc, const Collection::ICountable<Graphic::FeatureLevel>& FeatureLevels, CRefPtr<Graphic::IOutput> pOutput){
		CR_APICHECK(this, pOutput);

		CRefPtr<COGLOutput>	pOGLOutput = pOutput.Cast<COGLOutput>();
		CRefPtr<Window::IWindow> pWindow = Desc.OutputWindow.IsValid() ? Desc.OutputWindow : pFocusWindow;

		return new COGLDevice(this, pWindow, Desc, FeatureLevels, pOGLOutput);
	}
}