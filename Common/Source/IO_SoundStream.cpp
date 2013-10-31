#include "../Include/IO_SoundStream.h"
#include "../Include/IO_Sound.h"

class CSoundStream : public CB::IO::ISoundStream{
private:
	CB::IO::CSound	m_Sound;

public:
	CSoundStream(CB::CRefPtr<CB::IO::IStream> pFileSoundStream);

	const bool	CanWrite() const;
	const bool	CanRead() const;

	void	Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements);
	void	Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements);

	void	Read(CB::CRefPtr<CB::IO::IStream> pOutStream, const unsigned uSizeInBytes);
	void	Write(CB::CRefPtr<CB::IO::IStream> pInStream, const unsigned uSizeInBytes);

	const bool	IsEndOfStream() const;
	const bool	IsBeginingOfStream() const;

	const unsigned	GetLength() const;

	void	SetPos(const int uPos, const CB::IO::StreamPos uType);

	const unsigned	GetPos() const;

	void	Flush(){};

	const unsigned	GetNumberOfChannels() const;
	const unsigned	GetNumberOfFrames() const;
	const unsigned	GetFrequency() const;
	const unsigned	GetSampleSize() const;
	const unsigned	GetFrameSize() const;
};

CSoundStream::CSoundStream(CB::CRefPtr<CB::IO::IStream> pFileSoundStream) : m_Sound(pFileSoundStream){
}

const bool	CSoundStream::CanRead() const{
	return true;
}

const bool	CSoundStream::CanWrite() const{
	return false;
}

void	CSoundStream::Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
	unsigned uSize = uSizeInBytes * uNumberOfElements;
	unsigned uFrames = uSize / this->GetFrameSize();

	m_Sound.ReadFrames((short*)pData, uFrames);
}

void	CSoundStream::Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
	throw CB::Exception::CException(
		L"Not implemented.", __FUNCTIONW__, __FILEW__, __LINE__);
}

void	CSoundStream::Read(CB::CRefPtr<CB::IO::IStream> pOutStream, const unsigned uSizeInBytes){
	CB::Collection::CList<unsigned char> Buffer(uSizeInBytes);
	this->Read(&Buffer[0], 1, uSizeInBytes);
	pOutStream->Write(Buffer);
}

void	CSoundStream::Write(const CB::CRefPtr<CB::IO::IStream> pInStream, const unsigned uSizeInBytes){
}

const bool	CSoundStream::IsEndOfStream() const{
	return this->m_Sound.GetFrame() == this->m_Sound.GetNumberOfFrames();
}

const bool	CSoundStream::IsBeginingOfStream() const{
	return this->m_Sound.GetFrame() == 0;
}

const unsigned	CSoundStream::GetLength() const{
	return this->GetNumberOfFrames() * this->GetFrameSize();
}

void	CSoundStream::SetPos(const int uPos, const CB::IO::StreamPos uType){
	this->m_Sound.SetFrame(uPos / this->GetFrameSize(), uType);
}

const unsigned	CSoundStream::GetPos() const{
	return this->m_Sound.GetFrame() * this->GetFrameSize();
}

const unsigned	CSoundStream::GetNumberOfChannels() const{
	return this->m_Sound.GetNumberOfChannels();
}

const unsigned	CSoundStream::GetNumberOfFrames() const{
	return this->m_Sound.GetNumberOfFrames();
}

const unsigned	CSoundStream::GetFrequency() const{
	return this->m_Sound.GetFrequency();
}

const unsigned	CSoundStream::GetSampleSize() const{
	return sizeof(short);
}

const unsigned	CSoundStream::GetFrameSize() const{
	return this->GetSampleSize() * this->GetNumberOfChannels();
}

namespace CB{
	namespace Audio{
		CRefPtr<IO::ISoundStream>	CreateStream(CRefPtr<IO::IStream> pSoundFileStream){
			return new CSoundStream(pSoundFileStream);
		}
	}
}