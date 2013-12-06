#include "../Internal/Adapter.h"
#include "../Internal/Device.h"
#include <CBStringEx.h>
#include <Logger.h>

namespace CB{
	COALAdapter::COALAdapter(CRefPtr<COALManager> pManager, const CString& strAdapter, const uint32 uIndex) :
		Manage::IManagedObject<COALManager, COALAdapter>(pManager),
		m_strAdapter(strAdapter),
		m_uIndex(uIndex),
		m_pAdapter(0)
	{
		Log::Write(L"Initializing OpenAL Adapter " + this->m_strAdapter);
		//auto szDevice = String::ToANSI(this->m_strAdapter);
		auto szDevice = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);
		ALCdevice* pDevice = alcOpenDevice(szDevice);
		if(pDevice == 0){
			auto uError = alcGetError(0);
			CR_THROW(L"Failed to create adapter " + this->m_strAdapter);
		}

		this->m_pAdapter = pDevice;
	}

	COALAdapter::~COALAdapter(){
		Log::Write(L"Deinitializing OpenAL Adapter " + this->m_strAdapter);
		if(this->m_pAdapter != 0){
			alcCloseDevice(this->m_pAdapter);
			this->m_pAdapter= 0;
		}
	}

	ALCdevice*	COALAdapter::GetALCDevice() const{
		return this->m_pAdapter;
	}

	const uint32	COALAdapter::GetApiId() const{
		return g_uApiId;
	}

	const uint32	COALAdapter::GetIndex() const{
		return this->m_uIndex;
	}

	const CString	COALAdapter::GetName() const{
		return this->m_strAdapter;
	}

	CRefPtr<Audio::IDevice>	COALAdapter::CreateDevice(){
		return new COALDevice(this);
	}
}