#include "../Internal/Adapter.h"
#include "../Internal/Device.h"

#include <CBStringEx.h>
#include <Logger.h>

namespace CB{
	CPAAdapter::CPAAdapter(CRefPtr<CPAManager> pManager, const CString& strAdapter, const uint32 uIndex) :
		Manage::IManagedObject<CPAManager, CPAAdapter>(pManager),
		m_strAdapter(strAdapter),
		m_uIndex(uIndex),
		m_pAdapter(0)
	{
		Log::Write(L"Initializing PortAudio Adapter " + this->m_strAdapter);
		auto szDevice = String::ToANSI(this->m_strAdapter);

		ALCdevice* pDevice = alcOpenDevice(reinterpret_cast<const ALCchar*>(szDevice.GetPointer()));
		if(pDevice == 0){
			auto uError = alcGetError(0);
			CR_THROW(L"Failed to create adapter " + this->m_strAdapter);
		}

		this->m_pAdapter = pDevice;
	}

	CPAAdapter::~CPAAdapter(){
		Log::Write(L"Deinitializing OpenAL Adapter " + this->m_strAdapter);
		if(this->m_pAdapter != 0){
			alcCloseDevice(this->m_pAdapter);
			this->m_pAdapter= 0;
		}
	}

	ALCdevice*	CPAAdapter::GetALCDevice() const{
		return this->m_pAdapter;
	}

	const uint32	CPAAdapter::GetApiId() const{
		return g_uApiId;
	}

	const uint32	CPAAdapter::GetIndex() const{
		return this->m_uIndex;
	}

	const CString	CPAAdapter::GetName() const{
		return this->m_strAdapter;
	}

	CRefPtr<Audio::IDevice>	CPAAdapter::CreateDevice(){
		return new CPADevice(this);
	}
}