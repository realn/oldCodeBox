#include "../Internal/IO_SoundData.h"
#include "../Include/Memory.h"

namespace CB{
	sf_count_t	CSoundData::SF_GetLength(void* pUserData){
		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		return pSoundData->m_pStream->GetLength();
	}

	sf_count_t	CSoundData::SF_Seek(sf_count_t iMove, int iSeek, void* pUserData){
		try{
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

			pSoundData->m_pStream->SetPos((iMove < 0 ? (uint32)(iMove * -1) : (uint32)iMove), (iMove < 0 ? IO::Direction::Back : IO::Direction::Forward), uPosType);
			return pSoundData->m_pStream->GetPos();
		}
		catch(Exception::CException&){
			return 0;
		}
	}

	sf_count_t	CSoundData::SF_Read(void* pData, sf_count_t iSize, void* pUserData){
		if(iSize <= 0)
			return 0;

		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		pSoundData->m_pStream->Read(pData, (uint32)iSize, 1);
		return iSize;
	}

	sf_count_t	CSoundData::SF_Write(const void* pData, sf_count_t iSize, void* pUserData){
		if(iSize <= 0)
			return 0;

		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		pSoundData->m_pStream->Write(pData, (uint32)iSize, 1);
		return iSize;
	}

	sf_count_t	CSoundData::SF_GetPos(void* pUserData){
		CSoundData* pSoundData = static_cast<CSoundData*>(pUserData);
		return (sf_count_t)pSoundData->m_pStream->GetPos();
	}

	CSoundData::CSoundData() : 
		m_pFile(0)
	{
	}

	CSoundData::~CSoundData(){
		try{
			this->Close();
		}
		catch(Exception::CException&){}
	}

	void	CSoundData::Open(){
		SF_VIRTUAL_IO SoundVirtualIO;
		SoundVirtualIO.get_filelen	= SF_GetLength;
		SoundVirtualIO.read			= SF_Read;
		SoundVirtualIO.write		= SF_Write;
		SoundVirtualIO.seek			= SF_Seek;
		SoundVirtualIO.tell			= SF_GetPos;

		Memory::SetZero(this->m_Info);

		this->m_pFile = sf_open_virtual(&SoundVirtualIO, SFM_READ, &this->m_Info, this);
		if(this->m_pFile == 0){
			throw CB::Exception::CInvalidVarValueException(L"SFLib Error", CB::String::FromANSI((const int8*)sf_strerror(0)),
				L"Failed to open sound file.", CR_INFO());
		}
	}

	void	CSoundData::Close(){
		if(this->m_pFile){
			sf_close(this->m_pFile);
			this->m_pFile = 0;
		}
	}
}