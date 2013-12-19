#include "../Internal/Device.h"
#include "../Internal/Buffer.h"
#include "../Internal/Source.h"
#include "../Internal/Listener.h"
#include "../Internal/OpenAL.h"
#include "../Internal/Utils.h"

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

	ALCcontext*	COALDevice::GetContext() const{
		return this->m_pContext;
	}

	const uint32	COALDevice::GetApiId() const {
		return g_uApiId;
	}

	CRefPtr<Audio::IListener>	COALDevice::CreateListener(){
		CR_ALBINDCHECK(this->m_pContext);

		if(!Manage::IObjectManager<COALDevice, COALListener>::m_pObjectList.IsEmpty()){
			return Manage::IObjectManager<COALDevice, COALListener>::m_pObjectList[0].GetCast<Audio::IListener>();
		}
		return new COALListener(this);
	}

	CRefPtr<Audio::ISource>	COALDevice::CreateSource(const Audio::SourceType uType){
		CR_ALBINDCHECK(this->m_pContext);

		return new COALSource(this, uType);
	}
		
	CRefPtr<Audio::IBuffer>		COALDevice::CreateBuffer(const Audio::ChannelFormat uFormat, const Audio::SampleType uType, const uint32 uSampleRate, const uint32 uSamples){
		CR_ALBINDCHECK(this->m_pContext);

		return new COALBuffer(this, uFormat, uType, uSampleRate, uSamples);
	}

	void	COALDevice::SetDopplerFactor(const float32 fFactor){
		CR_ALBINDCHECK(this->m_pContext);

		alDopplerFactor(fFactor);	CR_ALCHECK();
	}

	const float32	COALDevice::GetDopplerFactor() const{
		CR_ALBINDCHECK(this->m_pContext);

		return alGetFloat(AL_DOPPLER_FACTOR);
	}

	void	COALDevice::SetSpeedOfSound(const float32 fUnitsPerSecond){
		CR_ALBINDCHECK(this->m_pContext);

		alSpeedOfSound(fUnitsPerSecond);	CR_ALCHECK();
	}

	const float32	COALDevice::GetSpeedOfSound() const{
		CR_ALBINDCHECK(this->m_pContext);

		return alGetFloat(AL_SPEED_OF_SOUND);
	}

	void	COALDevice::SetSourceDistanceModels(const bool bEnabled){
		CR_ALBINDCHECK(this->m_pContext);

		if(bEnabled){
			alEnable(AL_SOURCE_DISTANCE_MODEL);	CR_ALCHECK();
		}
		else{
			alDisable(AL_SOURCE_DISTANCE_MODEL);	CR_ALCHECK();
		}
	}

	const bool	COALDevice::IsSourceDistanceModelsEnabled() const{
		CR_ALBINDCHECK(this->m_pContext);

		return alIsEnabled(AL_SOURCE_DISTANCE_MODEL) == AL_TRUE ? true : false;
	}

	void			COALDevice::SetDistanceModel(const Audio::DistanceModel uModel){
		CR_ALBINDCHECK(this->m_pContext);
		auto uALModel = Utils::ToDistanceModel(uModel);
		alDistanceModel(uALModel);	CR_ALCHECK();
	}

	const Audio::DistanceModel	COALDevice::GetDistanceModel() const{
		CR_ALBINDCHECK(this->m_pContext);
		auto uEnum = alGetInteger(AL_DISTANCE_MODEL);	CR_ALCHECK();
		return Utils::ToDistanceModel(uEnum);
	}

	void	COALDevice::ProcessEvents(){
		CR_ALBINDCHECK(this->m_pContext);

		alcProcessContext(this->m_pContext);
	}
}