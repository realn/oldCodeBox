#include "../Internal/Source.h"
#include "../Internal/Buffer.h"
#include "../Internal/OpenAL.h"

namespace CB{
	COALSource::COALSource(CRefPtr<COALDevice> pDevice, const Audio::SourceType uType) :
		Manage::IManagedObject<COALDevice, COALSource>(pDevice),
		m_uType(uType),
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

	void	COALSource::SetVolume(const float32 fGain){
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

	const float32	COALSource::GetVolume() const {
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

	void	COALSource::Play(){
		alSourcePlay(this->m_uSource);
	}

	void	COALSource::Stop(){
		alSourceStop(this->m_uSource);
	}

	void	COALSource::Pause(){
		alSourcePause(this->m_uSource);
	}

	void	COALSource::Rewind(){
		alSourceRewind(this->m_uSource);
	}

	const Audio::SourceType	COALSource::GetType() const{
		return this->m_uType;
	}

	const Audio::SourceState	COALSource::GetState() const{
		ALint iState = 0;
		alGetSourcei(this->m_uSource, AL_SOURCE_STATE, &iState);
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

		auto pALBuffer = pBuffer.Cast<COALBuffer>();
		if(this->m_uType == Audio::SourceType::Static){
			this->m_pBufferList.Clear();
			alSourcei(this->m_uSource, AL_BUFFER, pALBuffer->GetBufferID());
		}
		else{
			ALuint  uBuffer = pALBuffer->GetBufferID();
			alSourceQueueBuffers(this->m_uSource, 1, &uBuffer);
		}
		this->m_pBufferList.Add(pALBuffer);
	}

	void	COALSource::AttachBuffer(Collection::ICountable<CRefPtr<Audio::IBuffer>>& pBufferList){
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

			alSourceQueueBuffers(this->m_uSource, ALBufferList.GetLength(), ALBufferList.GetPointer());
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
				ALuint uCount = 0;
				Collection::CList<ALuint> BufferIDList;

				alGetSourcei(this->m_uSource, AL_BUFFERS_PROCESSED, reinterpret_cast<ALint*>(&uCount));
				if(uCount > 0){
					BufferIDList.Resize(uCount);
					alSourceUnqueueBuffers(this->m_uSource, uCount, BufferIDList.GetPointer());
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
		alSourcei(this->m_uSource, AL_BUFFER, 0);
		this->m_pBufferList.Clear();
	}

	const bool	COALSource::HasAttachedBuffer() const{
		return !this->m_pBufferList.IsEmpty();
	}

	const bool	COALSource::HasProcessedBuffers() const {
		ALint uCount = 0;
		alGetSourcei(this->m_uSource, AL_BUFFERS_PROCESSED, &uCount);

		return uCount > 0;
	}
}