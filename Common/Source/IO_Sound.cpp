#include "../Include/IO_Sound.h"
#include <sndfile.h>

#pragma comment(lib, "libsndfile.lib")

class CSoundData{
public:
	CB::CRefPtr<CB::IO::IStream>	m_pStream;
	SF_INFO		m_Info;
	SNDFILE*	m_pFile;

public:
	static sf_count_t	SF_GetLength(void* pUserData){
		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		return pSoundData->m_pStream->GetLength();
	}
	static sf_count_t	SF_Seek(sf_count_t uMove, int iSeek, void* pUserData){
		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		CB::IO::StreamPos uPosType = CB::IO::StreamPos::Begin;
		
		switch (iSeek)
		{
		case SEEK_CUR:	uPosType = CB::IO::StreamPos::Current;	break;
		case SEEK_END:	uPosType = CB::IO::StreamPos::End;		break;
		case SEEK_SET:	uPosType = CB::IO::StreamPos::Begin;	break;
		default:
			break;
		}

		pSoundData->m_pStream->SetPos((int)uMove, uPosType);
		return pSoundData->m_pStream->GetPos();
	}
	static sf_count_t	SF_Read(void* pData, sf_count_t iSize, void* pUserData){
		if(iSize <= 0)
			return 0;

		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		pSoundData->m_pStream->Read(pData, (unsigned)iSize, 1);
		return iSize;
	}
	static sf_count_t	SF_Write(const void* pData, sf_count_t iSize, void* pUserData){
		if(iSize <= 0)
			return 0;

		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		pSoundData->m_pStream->Write(pData, (unsigned)iSize, 1);
		return iSize;
	}
	static sf_count_t	SF_GetPos(void* pUserData){
		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		return (sf_count_t)pSoundData->m_pStream->GetPos();
	}

public:
	CSoundData() : m_pFile(0){}
	~CSoundData(){
		this->Close();
	}

	void	Open(){
		SF_VIRTUAL_IO SoundVirtualIO;
		SoundVirtualIO.get_filelen	= SF_GetLength;
		SoundVirtualIO.read			= SF_Read;
		SoundVirtualIO.write		= SF_Write;
		SoundVirtualIO.seek			= SF_Seek;
		SoundVirtualIO.tell			= SF_GetPos;

		CB::Memory::SetZero(this->m_Info);

		this->m_pFile = sf_open_virtual(&SoundVirtualIO, SFM_READ, &this->m_Info, this);
		if(this->m_pFile == 0){
			throw CB::Exception::CInvalidVarValueException(L"SFLib Error", CB::String::FromANSI(sf_strerror(0)),
				L"Failed to open sound file.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}
	void	Close(){
		if(this->m_pFile){
			sf_close(this->m_pFile);
			this->m_pFile = 0;
		}
	}
};

namespace CB{
	namespace IO{
		CSound::CSound(CRefPtr<IStream> pStream){
			try{
				CAutoPtr<CSoundData> pData = new CSoundData();

				pData->m_pStream = pStream;
				pData->Open();

				this->m_pData.Set<CSoundData>(pData.Reset());
			}
			catch(Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while opening sound file.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		CSound::~CSound(){
			this->m_pData.Delete<CSoundData>();
		}

		const unsigned	CSound::GetNumberOfChannels() const{
			return this->m_pData.Get<CSoundData>()->m_Info.channels;
		}

		const unsigned	CSound::GetNumberOfFrames() const{
			auto iFrames = this->m_pData.Get<CSoundData>()->m_Info.frames;
			if(iFrames < 0)
				return 0;
			return (unsigned)iFrames;
		}

		const unsigned	CSound::GetFrequency() const{
			return this->m_pData.Get<CSoundData>()->m_Info.samplerate;
		}

		CRefPtr<IStream>	CSound::GetStream() const{
			return this->m_pData.Get<CSoundData>()->m_pStream;
		}

		void	CSound::ReadFrames(short* pData, const unsigned uFrames){
			if(sf_readf_short(this->m_pData.Get<CSoundData>()->m_pFile, pData, uFrames) == 0){
				throw CB::Exception::CException(
					L"Failed to read sound data.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		void	CSound::ReadFrames(Collection::CList<short>& Data, const unsigned uFrames){
			this->ReadFrames(&Data[0], uFrames);
		}

		void	CSound::ReadFrames(Collection::CList<short>& Data){
			this->ReadFrames(Data, Data.GetLength() / this->GetNumberOfChannels());
		}

		void	CSound::WriteFrames(const short* pData, const unsigned uFrames){
			if(sf_writef_short(this->m_pData.Get<CSoundData>()->m_pFile, pData, uFrames) == 0){
				throw Exception::CException(
					L"Failed to write sound data.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		void	CSound::WriteFrames(const Collection::CList<short>& Data, const unsigned uFrames){
			this->WriteFrames(&Data[0], uFrames);
		}

		void	CSound::WriteFrames(const Collection::CList<short>& Data){
			this->WriteFrames(Data, Data.GetLength() / this->GetNumberOfChannels());
		}

		void	CSound::SetFrame(const unsigned uFrame){
			this->SetFrame(uFrame, StreamPos::Begin);
		}

		void	CSound::SetFrame(const int iFrame, const StreamPos uType){
			int iMode = 0;
			switch (uType)
			{
			case StreamPos::Begin:		iMode = SEEK_SET;	break;
			case StreamPos::Current:	iMode = SEEK_CUR;	break;
			case StreamPos::End:		iMode = SEEK_END;	break;
			default:
				throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
					L"Unknown seek mode.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(sf_seek(this->m_pData.Get<CSoundData>()->m_pFile, iFrame, iMode) == -1){
				throw Exception::CException(
					L"Failed to set frame position in sound data.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const unsigned	CSound::GetFrame() const{
			auto iSeek = sf_seek(this->m_pData.Get<CSoundData>()->m_pFile, 0, SEEK_CUR);
			if(iSeek < 0){
				throw Exception::CException(
					L"Failed to retrieve current pos in sound data.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return (unsigned)iSeek;
		}
	}
}