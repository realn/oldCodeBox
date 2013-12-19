#include "../Internal/Source.h"
#include "../Internal/Buffer.h"
#include "../Internal/OpenAL.h"
#include "../Internal/Utils.h"

namespace CB{
	COALSource::COALSource(CRefPtr<COALDevice> pDevice, const Audio::SourceType uType) :
		Manage::IManagedObject<COALDevice, COALSource>(pDevice),
		m_uType(uType),
		m_uSource(0)
	{
		alGenSources(1, &this->m_uSource);	CR_ALCHECK();
	}

	COALSource::~COALSource(){
		if(this->m_uSource != 0 && alIsSource(this->m_uSource)){
			CR_ALBINDCHECK(this->m_pParent->GetContext());
			alDeleteSources(1, &this->m_uSource);	CR_ALCHECK();
			this->m_uSource = 0;
		}
	}

	const uint32	COALSource::GetApiId() const {
		return g_uApiId;
	}

	void	COALSource::SetVolume(const float32 fGain){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcef(this->m_uSource, AL_GAIN, fGain);	CR_ALCHECK();
	}

	void	COALSource::SetPosition(const Math::CVector3D& vPosition){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcefv(this->m_uSource, AL_POSITION, vPosition.GetPointer());	CR_ALCHECK();
	}

	void	COALSource::SetVelocity(const Math::CVector3D& vVelocity) {
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcefv(this->m_uSource, AL_VELOCITY, vVelocity.GetPointer());	CR_ALCHECK();
	}

	const Math::CVector3D	COALSource::GetPosition() const {
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		Math::CVector3D vResult;
		alGetSourcefv(this->m_uSource, AL_POSITION, vResult.GetPointer());	CR_ALCHECK();
		return vResult;
	}

	const Math::CVector3D	COALSource::GetVelocity() const {
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		Math::CVector3D vResult;
		alGetSourcefv(this->m_uSource, AL_VELOCITY, vResult.GetPointer());	CR_ALCHECK();
		return vResult;
	}

	const float32	COALSource::GetVolume() const {
		return this->GetSourceFloat(AL_GAIN);
	}

	void			COALSource::SetDistanceModel(const Audio::DistanceModel uModel){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		auto uALModel = Utils::ToDistanceModel(uModel);
		alSourcei(this->m_uSource, AL_DISTANCE_MODEL, uALModel);	CR_ALCHECK();
	}

	const Audio::DistanceModel	COALSource::GetDistanceModel() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		ALenum uEnum = this->GetSourceInt(AL_DISTANCE_MODEL);	CR_ALCHECK();
		return Utils::ToDistanceModel(uEnum);
	}

	void	COALSource::SetPitch(const float32 fValue){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcef(this->m_uSource, AL_PITCH, fValue);	CR_ALCHECK();
	}

	const float32	COALSource::GetPitch() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_PITCH);
	}

	void	COALSource::SetCone(const float32 fInnerDeg, const float32 fOuterDeg){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcef(this->m_uSource, AL_CONE_INNER_ANGLE, fInnerDeg);	CR_ALCHECK();
		alSourcef(this->m_uSource, AL_CONE_OUTER_ANGLE, fOuterDeg);	CR_ALCHECK();
	}

	const float32	COALSource::GetConeInner() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_CONE_INNER_ANGLE);
	}

	const float32	COALSource::GetConeOuter() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_CONE_OUTER_ANGLE);
	}

	void			COALSource::SetConeOuterVolume(const float fVolume){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcef(this->m_uSource, AL_CONE_OUTER_GAIN, fVolume);	CR_ALCHECK();
	}

	const float32	COALSource::GetConeOuterVolume() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_CONE_OUTER_GAIN);
	}

	void			COALSource::SetVolumeClamp(const float32 fMin, const float32 fMax){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcef(this->m_uSource, AL_MIN_GAIN, fMin);	CR_ALCHECK();
		alSourcef(this->m_uSource, AL_MAX_GAIN, fMax);	CR_ALCHECK();
	}

	const float32	COALSource::GetVolumeMin() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_MIN_GAIN);
	}

	const float32	COALSource::GetVolumeMax() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_MAX_GAIN);
	}

	void	COALSource::SetDirection(const Math::CVector3D& vDirection){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcefv(this->m_uSource, AL_DIRECTION, vDirection.GetPointer());	CR_ALCHECK();
	}

	const Math::CVector3D	COALSource::GetDirection() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		Math::CVector3D vValue;
		alGetSourcefv(this->m_uSource, AL_DIRECTION, vValue.GetPointer());	CR_ALCHECK();
		return vValue;
	}

	void	COALSource::SetRollOffFactor(const float32 fFactor){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcef(this->m_uSource, AL_ROLLOFF_FACTOR, fFactor);	CR_ALCHECK();
	}

	const float32	COALSource::GetRollOffFactor() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_ROLLOFF_FACTOR);
	}

	void	COALSource::SetDistance(const float32 fReference, const float32 fMax){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcef(this->m_uSource, AL_REFERENCE_DISTANCE, fReference);	CR_ALCHECK();
		alSourcef(this->m_uSource, AL_MAX_DISTANCE, fMax);	CR_ALCHECK();
	}

	const float32	COALSource::GetDistanceReference() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_REFERENCE_DISTANCE);
	}

	const float32	COALSource::GetDistanceMax() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		return this->GetSourceFloat(AL_MAX_DISTANCE);
	}

	void		COALSource::SetPositionRelative(const bool bEnabled){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcei(this->m_uSource, AL_SOURCE_RELATIVE, bEnabled ? AL_TRUE : AL_FALSE);	CR_ALCHECK();
	}

	const bool	COALSource::IsPositionRelative() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		ALint iResult = 0;
		alGetSourcei(this->m_uSource, AL_SOURCE_RELATIVE, &iResult);	CR_ALCHECK();
		return iResult == AL_TRUE ? true : false;
	}

	void	COALSource::Play(){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcePlay(this->m_uSource);	CR_ALCHECK();
	}

	void	COALSource::Stop(){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourceStop(this->m_uSource);	CR_ALCHECK();
	}

	void	COALSource::Pause(){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcePause(this->m_uSource);	CR_ALCHECK();
	}

	void	COALSource::Rewind(){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourceRewind(this->m_uSource);	CR_ALCHECK();
	}

	const Audio::SourceType	COALSource::GetType() const{
		return this->m_uType;
	}

	const Audio::SourceState	COALSource::GetState() const{
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		ALint iState = 0;
		alGetSourcei(this->m_uSource, AL_SOURCE_STATE, &iState);	CR_ALCHECK();
		switch (iState)
		{
		case AL_INITIAL:	return Audio::SourceState::None;
		case AL_PLAYING:	return Audio::SourceState::Playing;
		case AL_PAUSED:		return Audio::SourceState::Paused;
		case AL_STOPPED:	return Audio::SourceState::Stopped;
		default:
			throw Exception::CInvalidVarValueException(L"iState", String::ToHexString((uint32)iState),
				L"Unknown state value returned from OpenAL", CR_INFO());
		}
	}

	void	COALSource::AttachBuffer(CRefPtr<Audio::IBuffer> pBuffer){
		CR_APICHECK(this, pBuffer);
		CR_ALBINDCHECK(this->m_pParent->GetContext());

		auto pALBuffer = pBuffer.Cast<COALBuffer>();
		if(this->m_uType == Audio::SourceType::Static){
			this->m_pBufferList.Clear();
			alSourcei(this->m_uSource, AL_BUFFER, pALBuffer->GetBufferID());	CR_ALCHECK();
		}
		else{
			ALuint  uBuffer = pALBuffer->GetBufferID();
			alSourceQueueBuffers(this->m_uSource, 1, &uBuffer);	CR_ALCHECK();
		}
		this->m_pBufferList.Add(pALBuffer);
	}

	void	COALSource::AttachBuffer(Collection::ICountable<CRefPtr<Audio::IBuffer>>& pBufferList){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		if(this->m_uType == Audio::SourceType::Static){
			throw Exception::CInvalidVarValueException(L"m_uType", String::ToString(this->m_uType),
				L"Cannot attach multiple buffers to static audio source.", CR_INFO());
		}
		else{
			Collection::CList<ALuint> ALBufferList;
			CRefPtr<COALBuffer> pALBuffer;
			for(uint32 uIndex = 0; uIndex < pBufferList.GetLength(); uIndex++){
				CR_APICHECK(this, pBufferList[uIndex]);

				pALBuffer = pBufferList[uIndex].Cast<COALBuffer>();
				ALBufferList.Add(pALBuffer->GetBufferID());

				if(!Collection::Contains(this->m_pBufferList, pALBuffer)){
					this->m_pBufferList.Add(pALBuffer);
				}
			}

			alSourceQueueBuffers(this->m_uSource, ALBufferList.GetLength(), ALBufferList.GetPointer());	CR_ALCHECK();
		}
	}

	CRefPtr<Audio::IBuffer>	COALSource::GetBuffer() const{
		if(this->m_uType == Audio::SourceType::Static){
			CR_EXGUARD();
			return this->m_pBufferList[0].Cast<Audio::IBuffer>();
			CR_ENDEXGUARD(L"Error while retrieving audio buffer from source.");
		}
		else{
			CR_THROW(L"Only static source can return one buffer.");
		}
	}

	const bool CompareBuffer(const CRefPtr<COALBuffer>& pBuffer, const ALuint& uBufferID){
		return pBuffer->GetBufferID() == uBufferID;
	}

	Collection::CList<CRefPtr<Audio::IBuffer>>	COALSource::GetBuffers(const bool bProcessedOnly) const{
		if(this->m_uType == Audio::SourceType::Streaming){
			CR_EXGUARD();

			Collection::CList<CRefPtr<Audio::IBuffer>> pResult;
			if(bProcessedOnly){
				CR_ALBINDCHECK(this->m_pParent->GetContext());

				ALuint uCount = 0;
				Collection::CList<ALuint> BufferIDList;

				alGetSourcei(this->m_uSource, AL_BUFFERS_PROCESSED, reinterpret_cast<ALint*>(&uCount));	CR_ALCHECK();
				if(uCount > 0){
					BufferIDList.Resize(uCount);
					alSourceUnqueueBuffers(this->m_uSource, uCount, BufferIDList.GetPointer());	CR_ALCHECK();
				}

				for(uint32 uIndex = 0; uIndex < BufferIDList.GetLength(); uIndex++){
					auto uBufferIndex = Collection::Find(this->m_pBufferList, CompareBuffer, BufferIDList[uIndex]);
					pResult.Add(this->m_pBufferList[uBufferIndex].Cast<Audio::IBuffer>());
				}
			}
			else{
				for(uint32 uIndex = 0; uIndex < this->m_pBufferList.GetLength(); uIndex++){
					pResult.Add(this->m_pBufferList[uIndex].Cast<Audio::IBuffer>());
				}
			}

			return pResult;

			CR_ENDEXGUARD(L"Error while retrieving audio buffer list from source.");
		}
		else{
			CR_THROW(L"Cannot retrieve multiple buffers from static source.");
		}
	}

	void	COALSource::FreeBuffer(){
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		alSourcei(this->m_uSource, AL_BUFFER, 0);	CR_ALCHECK();
		this->m_pBufferList.Clear();
	}

	const bool	COALSource::HasAttachedBuffer() const{
		return !this->m_pBufferList.IsEmpty();
	}

	const bool	COALSource::HasProcessedBuffers() const {
		CR_ALBINDCHECK(this->m_pParent->GetContext());
		ALint uCount = 0;
		alGetSourcei(this->m_uSource, AL_BUFFERS_PROCESSED, &uCount);	CR_ALCHECK();
		return uCount > 0;
	}

	const float32	COALSource::GetSourceFloat(const uint32 uEnum) const{
		float32 fValue = 0.0f;
		alGetSourcef(this->m_uSource, uEnum, &fValue);	CR_ALCHECK();
		return fValue;
	}

	const int32	COALSource::GetSourceInt(const uint32 uEnum) const{
		int32 iValue = 0;
		alGetSourcei(this->m_uSource, uEnum, &iValue);	CR_ALCHECK();
		return iValue;
	}
}