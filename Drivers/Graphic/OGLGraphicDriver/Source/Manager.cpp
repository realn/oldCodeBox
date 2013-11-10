#include "../Internal/Manager.h"
#include "../Internal/Adapter.h"

#include "../Internal/WinPlatform.h"

namespace CB{
	const uint32	g_uApiID = *((uint32*)"OGL1");

	BOOL CALLBACK	MonitorProc(HMONITOR hMonitor, HDC hDC, LPRECT lpRect, LPARAM lParam){
		auto pManager = reinterpret_cast<COGLManager*>(lParam);

		MONITORINFOEXW info;
		info.cbSize = sizeof(MONITORINFOEX);
		if(GetMonitorInfoW(hMonitor, &info) && info.dwFlags){
			Math::CRectangle rect(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);

			pManager->AddMonitor(info.szDevice, rect, (info.dwFlags & MONITORINFOF_PRIMARY) > 0);
		}

		return true;
	}

	COGLManager::COGLManager(CRefPtr<Graphic::IDriver> pDriver) :
		m_pDriver(pDriver)
	{
		if(!EnumDisplayMonitors(0, 0, MonitorProc, reinterpret_cast<LPARAM>(this))){
			CR_THROWWIN(GetLastError(), L"Failed to enumerate all monitors.");
		}

		Log::Write(L"Initializing OGL Manager.");
		DISPLAY_DEVICEW device = { 0 };
		device.cb = sizeof(DISPLAY_DEVICEW);
		for(uint32 uIndex = 0; EnumDisplayDevicesW(0, uIndex, &device, 0); uIndex++){
			if(!(device.StateFlags & DISPLAY_DEVICE_ACTIVE))
				continue;

			if(device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE){
				if(this->m_AdapterList.Contains(device.DeviceID)){
					auto devInfo = this->m_AdapterList[device.DeviceID];

					this->m_AdapterList.DeleteByKey(device.DeviceID);
					
					if(!devInfo.strDisplayList.Contains(device.DeviceName)){
						devInfo.strDisplayList.Insert(0, device.DeviceName);
					}
					else{
						devInfo.strDisplayList.Remove(devInfo.strDisplayList.IndexOf(device.DeviceName));
						devInfo.strDisplayList.Insert(0, device.DeviceName);
					}

					this->m_AdapterList.Insert(0, device.DeviceID, devInfo);
				}
				else{
					CDisplayDeviceInfo devInfo;

					devInfo.strDeviceId = device.DeviceID;
					devInfo.strDeviceName = device.DeviceString;
					devInfo.strDisplayList.Add(device.DeviceName);

					this->m_AdapterList.Insert(0, device.DeviceID, devInfo);
				}
			}
			else{
				if(this->m_AdapterList.Contains(device.DeviceID)){
					CDisplayDeviceInfo& info = this->m_AdapterList[device.DeviceID];

					if(!info.strDisplayList.Contains(device.DeviceName)){
						info.strDisplayList.Add(device.DeviceName);
					}
				}
				else{
					CDisplayDeviceInfo devInfo; 

					devInfo.strDeviceId = device.DeviceID;
					devInfo.strDeviceName = device.DeviceString;
					devInfo.strDisplayList.Add(device.DeviceName);

					this->m_AdapterList.Add(device.DeviceID, devInfo);
				}
			}
		}
	}

	COGLManager::~COGLManager(){
		Log::Write(L"Deinitializing OGL Manager.");
	}

	const uint32	COGLManager::GetApiId() const{
		return g_uApiID;
	}

	const uint32	COGLManager::GetNumberOfAdapters() const{
		return this->m_AdapterList.GetLength();
	}

	const bool	CompareAdapter(const CPtr<COGLAdapter>& pAdapter, const uint32& uIndex){
		return pAdapter->GetIndex() == uIndex;
	}

	CRefPtr<Graphic::IAdapter>	COGLManager::GetAdapter(const uint32 uIndex){
		uint32 uFound = 0;
		if(Collection::TryFind(this->m_pObjectList, CompareAdapter, uIndex, uFound)){
			return this->m_pObjectList[uFound].GetCast<Graphic::IAdapter>();
		}

		return new COGLAdapter(this, uIndex, this->m_AdapterList.GetKey(uIndex), this->m_AdapterList.GetValue(uIndex));
	}

	CRefPtr<Graphic::IAdapter>	COGLManager::GetDefaultAdapter(){
		return this->GetAdapter(0);
	}

	void	COGLManager::AddMonitor(const CString& strDevice, const Math::CRectangle& Rect, const bool bPrimary){
		if(!this->m_Monitors.Contains(strDevice)){
			if(bPrimary){
				this->m_Monitors.Insert(0, strDevice, Rect);
			}
			else{
				this->m_Monitors.Add(strDevice, Rect);
			}
		}
	}
}