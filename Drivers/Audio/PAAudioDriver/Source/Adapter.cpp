#include "../Internal/Adapter.h"
#include "../Internal/Device.h"

#include <CBStringEx.h>
#include <Logger.h>

namespace CB{
	CPAAdapter::CPAAdapter(CRefPtr<CPAManager> pManager, const CString& strAdapter, const uint32 uIndex) :
		Manage::IManagedObject<CPAManager, CPAAdapter>(pManager),
		m_strAdapter(strAdapter),
		m_uIndex(uIndex)
	{
		Log::Write(L"Initializing PortAudio Adapter " + this->m_strAdapter);
	}

	CPAAdapter::~CPAAdapter(){
		Log::Write(L"Deinitializing OpenAL Adapter " + this->m_strAdapter);
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