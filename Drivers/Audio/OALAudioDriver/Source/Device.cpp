#include "../Internal/Device.h"
#include "../Internal/Buffer.h"
#include "../Internal/Source.h"
#include "../Internal/Listener.h"
#include "../Internal/OpenAL.h"

#include <Logger.h>
#include <Collection_Array.h>

namespace CB{
	COALDevice::COALDevice(CRefPtr<COALAdapter> pAdapter) :
		Manage::IManagedObject<COALAdapter, COALDevice>(pAdapter),
		m_pContext(0)
	{
		Log::Write(L"Initializing OpenAL Device...");
		ALCint attibs[] = {
			ALC_MAJOR_VERSION, 1,
			ALC_MINOR_VERSION, 1,
			0, 0,
		};
		this->m_pContext = alcCreateContext(this->m_pParent->GetALCDevice(), attibs);
		if(!this->m_pContext){
			auto uError = alcGetError(this->m_pParent->GetALCDevice());
			CR_THROW(L"Failed to create device for adapter " + this->m_pParent->GetName() + L", error: " + String::ToHexString(uError));
		}
		if(!alcMakeContextCurrent(this->m_pContext)){
			auto uError = alcGetError(this->m_pParent->GetALCDevice());
			alcDestroyContext(this->m_pContext);
			CR_THROW(L"Failed to make context current for adapter " + this->m_pParent->GetName() + L", error: " + String::ToHexString(uError));
		}

		//AL::LoadExtensions(this->m_pParent->GetALCDevice());
	}

	COALDevice::~COALDevice(){
		Log::Write(L"Deinitializing OpenAL Device...");
		if(this->m_pContext){
			auto pCtx = alcGetCurrentContext();
			if(pCtx == this->m_pContext){
				alcMakeContextCurrent(0);
			}
			alcDestroyContext(this->m_pContext);
			this->m_pContext = 0;
		}
	}

	const uint32	COALDevice::GetApiId() const {
		return g_uApiId;
	}


	CRefPtr<Audio::IListener>	COALDevice::CreateListener(){
		if(!Manage::IObjectManager<COALDevice, COALListener>::m_pObjectList.IsEmpty()){
			return Manage::IObjectManager<COALDevice, COALListener>::m_pObjectList[0].GetCast<Audio::IListener>();
		}
		return new COALListener(this);
	}

	CRefPtr<Audio::ISource>	COALDevice::CreateSource(const Audio::SourceType uType){
		return new COALSource(this, uType);
	}
		
	CRefPtr<Audio::IBuffer>		COALDevice::CreateBuffer(const Audio::ChannelFormat uFormat, const Audio::SampleType uType, const uint32 uSampleRate, const uint32 uSamples){
		return new COALBuffer(this, uFormat, uType, uSampleRate, uSamples);
	}

	void	COALDevice::SetSpeedOfSound(const float32 fUnitsPerSecond) {
		alSpeedOfSound(fUnitsPerSecond);
	}

	const float32	COALDevice::GetSpeedOfSound() const {
		return alGetFloat(AL_SPEED_OF_SOUND);
	}

	void	COALDevice::ProcessEvents(){
		alcProcessContext(this->m_pContext);
	}
}