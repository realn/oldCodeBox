#include "../Internal/Device.h"
#include "../Internal/Buffer.h"
#include "../Internal/Source.h"
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

	void	COALDevice::SetGain(const float32 fGain) {
		alListenerf(AL_GAIN, fGain);
	}

	void	COALDevice::SetPosition(const Math::CVector3D& vPosition) {
		alListenerfv(AL_POSITION, vPosition.GetPointer());
	}
	void	COALDevice::SetVelocity(const Math::CVector3D& vVelocity) {
		alListenerfv(AL_VELOCITY, vVelocity.GetPointer());
	}

	const Math::CVector3D	COALDevice::GetPosition() const {
		Math::CVector3D	vResult;
		alGetListenerfv(AL_POSITION, vResult.GetPointer());
		return vResult;
	}

	const Math::CVector3D	COALDevice::GetVelocity() const {
		Math::CVector3D	vResult;
		alGetListenerfv(AL_VELOCITY, vResult.GetPointer());
		return vResult;
	}

	const float32	COALDevice::GetGain() const {
		float32 fResult = 0.0f;
		alGetListenerf(AL_GAIN, &fResult);
		return fResult;
	}

	void	COALDevice::SetOrientation(const Math::CVector3D& vForward, const Math::CVector3D& vUp) {
		float32 pfData[] = {
			vForward.X, vForward.Y, vForward.Z,
			vUp.X, vUp.Y, vUp.Z,
		};
		alListenerfv(AL_ORIENTATION, pfData);
	}

	const Math::CVector3D	COALDevice::GetOrientationForward() const {
		float32 pfData[6];
		alGetListenerfv(AL_ORIENTATION, pfData);
		return Math::CVector3D(pfData[0], pfData[1], pfData[2]);
	}

	const Math::CVector3D	COALDevice::GetOrientationUp() const {
		float32 pfData[6];
		alGetListenerfv(AL_ORIENTATION, pfData);
		return Math::CVector3D(pfData[3], pfData[4], pfData[5]);
	}

	CRefPtr<Audio::IListener>	COALDevice::GetListener() const {
		return this;
	}

	CRefPtr<Audio::ISource>	COALDevice::CreateSource() const {
		return new COALSource(this);
	}
		
	CRefPtr<Audio::IBuffer>		COALDevice::CreateBuffer(const Audio::BufferFormat uFormat, const uint32 uSampleRate, const uint32 uSamples){
		return new COALBuffer(this, uFormat, uSampleRate, uSamples);
	}

	void	COALDevice::SetSpeedOfSound(const float32 fUnitsPerSecond) {
		alSpeedOfSound(fUnitsPerSecond);
	}

	const float32	COALDevice::GetSpeedOfSound() const {
		return alGetFloat(AL_SPEED_OF_SOUND);
	}
}