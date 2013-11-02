#include "../Internal/IO_SoundStream.h"
#include "../Include/Collection_List.h"

namespace CB{
	CSoundStream::CSoundStream(CB::CRefPtr<CB::IO::IStream> pFileSoundStream) : 
		m_Sound(pFileSoundStream)
	{
	}

	CSoundStream::~CSoundStream(){
	}

	const bool	CSoundStream::CanRead() const{
		return true;
	}

	const bool	CSoundStream::CanWrite() const{
		return false;
	}

	void	CSoundStream::Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
		uint32 uSize = uSizeInBytes * uNumberOfElements;
		uint32 uFrames = uSize / this->GetFrameSize();

		m_Sound.ReadFrames((short*)pData, uFrames);
	}

	void	CSoundStream::Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
		CR_THROWNOTIMPLEMENTED();
	}

	void	CSoundStream::Read(CB::CRefPtr<CB::IO::IStream> pOutStream, const uint32 uSizeInBytes){
		CB::Collection::CList<byte> Buffer(uSizeInBytes);
		dynamic_cast<IO::IStream*>(this)->Read(Buffer);
		pOutStream->Write(Buffer);
	}

	void	CSoundStream::Write(const CB::CRefPtr<CB::IO::IStream> pInStream, const uint32 uSizeInBytes){
		CR_THROWNOTIMPLEMENTED();
	}

	const bool	CSoundStream::IsEndOfStream() const{
		return this->m_Sound.GetFrame() == this->m_Sound.GetNumberOfFrames();
	}

	const bool	CSoundStream::IsBeginingOfStream() const{
		return this->m_Sound.GetFrame() == 0;
	}

	const uint32	CSoundStream::GetLength() const{
		return this->GetNumberOfFrames() * this->GetFrameSize();
	}

	void	CSoundStream::SetPos(const uint32 uPos, const IO::Direction uDirection, const IO::StreamPos uType){
		this->m_Sound.SetFrame(uPos / this->GetFrameSize(), uDirection, uType);
	}

	const uint32	CSoundStream::GetPos() const{
		return this->m_Sound.GetFrame() * this->GetFrameSize();
	}

	void	CSoundStream::Flush(){
	}

	const uint32	CSoundStream::GetNumberOfChannels() const{
		return this->m_Sound.GetNumberOfChannels();
	}

	const uint32	CSoundStream::GetNumberOfFrames() const{
		return this->m_Sound.GetNumberOfFrames();
	}

	const uint32	CSoundStream::GetFrequency() const{
		return this->m_Sound.GetFrequency();
	}

	const uint32	CSoundStream::GetSampleSize() const{
		return sizeof(short);
	}

	const uint32	CSoundStream::GetFrameSize() const{
		return this->GetSampleSize() * this->GetNumberOfChannels();
	}

	namespace Audio{
		CRefPtr<IO::ISoundStream>	CreateStream(CRefPtr<IO::IStream> pSoundFileStream){
			return new CSoundStream(pSoundFileStream);
		}
	}
}