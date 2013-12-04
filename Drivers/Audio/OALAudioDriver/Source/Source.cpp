#include "../Internal/Source.h"

namespace CB{
	COALSource::COALSource(CRefPtr<COALDevice> pDevice) :
		Manage::IManagedObject<COALDevice, COALSource>(pDevice),
		m_uSource(0)
	{
		alGenSources(1, &this->m_uSource);
	}

	COALSource::~COALSource(){
		if(this->m_uSource != 0 && alIsSource(this->m_uSource)){
			alDeleteSources(1, &this->m_uSource);
			this->m_uSource = 0;
		}
	}

	const uint32	COALSource::GetApiId() const {
		return g_uApiId;
	}

	void	COALSource::SetGain(const float32 fGain){
		alSourcef(this->m_uSource, AL_GAIN, fGain);
	}

	void	COALSource::SetPosition(const Math::CVector3D& vPosition){
		alSourcefv(this->m_uSource, AL_POSITION, vPosition.GetPointer());
	}

	void	COALSource::SetVelocity(const Math::CVector3D& vVelocity) {
		alSourcefv(this->m_uSource, AL_VELOCITY, vVelocity.GetPointer());
	}

	const Math::CVector3D	COALSource::GetPosition() const {
		Math::CVector3D vResult;
		alGetSourcefv(this->m_uSource, AL_POSITION, vResult.GetPointer());
		return vResult;
	}

	const Math::CVector3D	COALSource::GetVelocity() const {
		Math::CVector3D vResult;
		alGetSourcefv(this->m_uSource, AL_VELOCITY, vResult.GetPointer());
		return vResult;
	}

	const float32	COALSource::GetGain() const {
		float32 fResult = 0.0f;
		alGetSourcef(this->m_uSource, AL_GAIN, &fResult);
		return fResult;
	}

	void		COALSource::SetPositionRelative(const bool bEnabled){
		alSourcei(this->m_uSource, AL_SOURCE_RELATIVE, bEnabled ? AL_TRUE : AL_FALSE);
	}

	const bool	COALSource::IsPositionRelative() const{
		ALint iResult = 0;
		alGetSourcei(this->m_uSource, AL_SOURCE_RELATIVE, &iResult);
		return iResult == AL_TRUE ? true : false;
	}
}