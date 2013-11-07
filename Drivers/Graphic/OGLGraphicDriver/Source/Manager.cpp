#include "../Internal/Manager.h"
#include "../Internal/Adapter.h"

namespace CB{
	const uint32	g_uApiID = *((uint32*)"OGL1");

	COGLManager::COGLManager(CRefPtr<Graphic::IDriver> pDriver) :
		m_pDriver(pDriver)
	{
		Log::Write(L"Initializing OGL Manager.");
		DISPLAY_DEVICEW device = { 0 };
		device.cb = sizeof(DISPLAY_DEVICEW);
		for(uint32 uIndex = 0; EnumDisplayDevicesW(0, uIndex, &device, 0); uIndex++){
			if(!(device.StateFlags & DISPLAY_DEVICE_ACTIVE))
				continue;

			if(device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE){
				if(this->m_AdapterList.Contains(device.DeviceID)){
					this->m_AdapterList.DeleteByKey(device.DeviceID);
				}
				this->m_AdapterList.Insert(0, device.DeviceID, device);
			}
			else if(!this->m_AdapterList.Contains(device.DeviceID)){
				this->m_AdapterList.Add(device.DeviceID, device);
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
}