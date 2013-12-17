#include "../Internal/Listener.h"
#include "../Internal/OpenAL.h"

#include <Logger.h>

namespace CB{
	COALListener::COALListener(CRefPtr<COALDevice> pDevice) :
		Manage::IManagedObject<COALDevice, COALListener>(pDevice)
	{
		Log::Write(L"Initializing OpenAL Listener.", Log::LogLevel::Debug);
	}

	COALListener::~COALListener(){
		Log::Write(L"Deinitializing OpenAL Listener.", Log::LogLevel::Debug);
	}

	const uint32	COALListener::GetApiId() const{
		return g_uApiId;
	}

	void	COALListener::SetVolume(const float32 fGain) {
		alListenerf(AL_GAIN, fGain);
	}

	void	COALListener::SetPosition(const Math::CVector3D& vPosition) {
		alListenerfv(AL_POSITION, vPosition.GetPointer());
	}
	void	COALListener::SetVelocity(const Math::CVector3D& vVelocity) {
		alListenerfv(AL_VELOCITY, vVelocity.GetPointer());
	}

	const Math::CVector3D	COALListener::GetPosition() const {
		Math::CVector3D	vResult;
		alGetListenerfv(AL_POSITION, vResult.GetPointer());
		return vResult;
	}

	const Math::CVector3D	COALListener::GetVelocity() const {
		Math::CVector3D	vResult;
		alGetListenerfv(AL_VELOCITY, vResult.GetPointer());
		return vResult;
	}

	const float32	COALListener::GetVolume() const {
		float32 fResult = 0.0f;
		alGetListenerf(AL_GAIN, &fResult);
		return fResult;
	}

	void	COALListener::SetOrientation(const Math::CVector3D& vForward, const Math::CVector3D& vUp) {
		float32 pfData[] = {
			vForward.X, vForward.Y, vForward.Z,
			vUp.X, vUp.Y, vUp.Z,
		};
		alListenerfv(AL_ORIENTATION, pfData);
	}

	const Math::CVector3D	COALListener::GetOrientationForward() const {
		float32 pfData[6];
		alGetListenerfv(AL_ORIENTATION, pfData);
		return Math::CVector3D(pfData[0], pfData[1], pfData[2]);
	}

	const Math::CVector3D	COALListener::GetOrientationUp() const {
		float32 pfData[6];
		alGetListenerfv(AL_ORIENTATION, pfData);
		return Math::CVector3D(pfData[3], pfData[4], pfData[5]);
	}
}