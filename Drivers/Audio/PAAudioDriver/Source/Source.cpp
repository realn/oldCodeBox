#include "../Internal/Source.h"
#include "../Internal/Buffer.h"

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
		ALenum uType = 0;
		alGetSourcei(this->m_uSource, AL_SOURCE_TYPE, reinterpret_cast<ALint*>(&uType));
		switch (uType)
		{
		case AL_STATIC:	return Audio::SourceType::Static;
		case AL_STREAMING:	return Audio::SourceType::Streaming;
		case AL_UNDETERMINED:	
		default:
			return Audio::SourceType::None;
		}
	}

	void	COALSource::SetStaticBuffer(CRefPtr<Audio::IBuffer> pBuffer){
		CR_APICHECK(this, pBuffer);

		this->m_pBuffer = pBuffer.Cast<COALBuffer>();

		alSourcei(this->m_uSource, AL_BUFFER, this->m_pBuffer->GetBufferID());
	}

	void	COALSource::QueueStreamingBuffers(const Collection::ICountable<CRefPtr<Audio::IBuffer>>& pBufferList){
		if(pBufferList.IsEmpty())
			return;

		this->m_pBufferList.Clear();
		Collection::CList<ALuint> Buffers(pBufferList.GetLength());
		for(uint32 uIndex = 0; uIndex < pBufferList.GetLength(); uIndex++){
			auto pBuffer = pBufferList[uIndex].Cast<COALBuffer>();

			this->m_pBufferList.Add(pBuffer);
			Buffers[uIndex] = pBuffer->GetBufferID();
		}

		alSourceQueueBuffers(this->m_uSource, Buffers.GetLength(), Buffers.GetPointer());
	}

	CRefPtr<Audio::IBuffer>	COALSource::GetStaticBuffer() const{
		return this->m_pBuffer.Cast<Audio::IBuffer>();
	}

	const Collection::CList<CRefPtr<Audio::IBuffer>>	COALSource::GetStremingBuffers() const{
		Collection::CList<CRefPtr<Audio::IBuffer>> Buffers(this->m_pBufferList.GetLength());
		for(uint32 uIndex = 0; uIndex < Buffers.GetLength(); uIndex++){
			Buffers[uIndex] = this->m_pBufferList[uIndex].Cast<Audio::IBuffer>();
		}
		return Buffers;
	}

	void	COALSource::FreeStaticBuffer(){
		if(this->m_pBuffer.IsValid()){
			this->Stop();
			alSourcei(this->m_uSource, AL_BUFFER, 0);
			this->m_pBuffer.Release();
		}
	}

	void	COALSource::FreeStreamingBuffers(){
		if(!this->m_pBufferList.IsEmpty()){
			this->Stop();
			Collection::CList<ALuint> Buffers(this->m_pBufferList.GetLength());
			alSourceUnqueueBuffers(this->m_uSource, Buffers.GetLength(), Buffers.GetPointer());
			alSourcei(this->m_uSource, AL_BUFFER, 0);
			this->m_pBufferList.Clear();
		}
	}

	const bool CompareBuffer(const CRefPtr<COALBuffer>& Buffer, const ALuint& id){
		return Buffer->GetBufferID() == id;
	}

	const Collection::CList<CRefPtr<Audio::IBuffer>>	COALSource::UnqueueProcessedBuffers(){
		ALuint uNumber = 0;
		alGetSourcei(this->m_uSource, AL_BUFFERS_PROCESSED, reinterpret_cast<ALint*>(&uNumber));
		if(uNumber == 0){
			return Collection::CList<CRefPtr<Audio::IBuffer>>();
		}

		Collection::CList<ALuint> Buffers(uNumber);
		alSourceUnqueueBuffers(this->m_uSource, uNumber, Buffers.GetPointer());
		
		Collection::CList<CRefPtr<Audio::IBuffer>> result;
		uint32 uFound = 0;
		for(uint32 uIndex = 0; uIndex < Buffers.GetLength(); uIndex++){
			uFound = 0;
			if(Collection::TryFind(this->m_pBufferList, CompareBuffer, Buffers[uIndex], uFound)){
				result.Add(this->m_pBufferList[uFound].Cast<Audio::IBuffer>());
				this->m_pBufferList.Remove(uFound);
			}
		}

		return result;
	}
}