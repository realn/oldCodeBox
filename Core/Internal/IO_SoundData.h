#pragma once

#include "../Include/IO_Sound.h"

#include <sndfile.h>

#pragma comment(lib, "libsndfile.lib")

namespace CB{
	class CSoundData{
	public:
		CB::CRefPtr<CB::IO::IStream>	m_pStream;
		SF_INFO		m_Info;
		SNDFILE*	m_pFile;

	public:
		static sf_count_t	SF_GetLength(void* pUserData);
		static sf_count_t	SF_Seek(sf_count_t uMove, int iSeek, void* pUserData);
		static sf_count_t	SF_Read(void* pData, sf_count_t iSize, void* pUserData);
		static sf_count_t	SF_Write(const void* pData, sf_count_t iSize, void* pUserData);
		static sf_count_t	SF_GetPos(void* pUserData);

	public:
		CSoundData();
		~CSoundData();

		void	Open();
		void	Close();
	};
}