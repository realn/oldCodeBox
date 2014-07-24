#include "stdafx.h"
#include "../Include/IO_Sound.h"
#include "../Internal/IO_SoundData.h"
#include "../Include/SmartPointers_AutoPtr.h"
#include "../Include/IO_Stream.h"

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
				throw CB::Exception::CException(L"Error while opening sound file.", CR_INFO(), Exception);
			}
		}

		CSound::~CSound(){
			try{
				this->m_pData.Delete<CSoundData>();
			}
			catch(Exception::CException&){}
		}

		const uint32	CSound::GetNumberOfChannels() const{
			return this->m_pData.Get<CSoundData>()->m_Info.channels;
		}

		const uint32	CSound::GetNumberOfFrames() const{
			auto iFrames = this->m_pData.Get<CSoundData>()->m_Info.frames;
			if(iFrames < 0)
				return 0;
			return (uint32)iFrames;
		}

		const uint32	CSound::GetFrequency() const{
			return this->m_pData.Get<CSoundData>()->m_Info.samplerate;
		}

		CRefPtr<IStream>	CSound::GetStream() const{
			return this->m_pData.Get<CSoundData>()->m_pStream;
		}

		void	CSound::ReadFrames(int16* pData, const uint32 uFrames){
			if(sf_readf_short(this->m_pData.Get<CSoundData>()->m_pFile, pData, uFrames) == 0){
				throw CB::Exception::CException(L"Failed to read sound data.", CR_INFO());
			}
		}

		void	CSound::ReadFrames(Collection::IPacked<int16>& Data, const uint32 uFrames){
			this->ReadFrames(Data.GetPointer(), uFrames);
		}

		void	CSound::ReadFrames(Collection::IPacked<int16>& Data){
			this->ReadFrames(Data, Data.GetLength() / this->GetNumberOfChannels());
		}

		void	CSound::WriteFrames(const int16* pData, const uint32 uFrames){
			if(sf_writef_short(this->m_pData.Get<CSoundData>()->m_pFile, pData, uFrames) == 0){
				throw Exception::CException(L"Failed to write sound data.", CR_INFO());
			}
		}

		void	CSound::WriteFrames(const Collection::IPacked<int16>& Data, const uint32 uFrames){
			this->WriteFrames(Data.GetPointer(), uFrames);
		}

		void	CSound::WriteFrames(const Collection::IPacked<int16>& Data){
			this->WriteFrames(Data, Data.GetLength() / this->GetNumberOfChannels());
		}

		void	CSound::SetFrame(const uint32 uFrame){
			this->SetFrame(uFrame, Direction::Forward, StreamPos::Begin);
		}

		void	CSound::SetFrame(const uint32 uFrame, const Direction uDirection, const StreamPos uType){
			int32 iMode = 0;
			switch (uType)
			{
			case StreamPos::Begin:		iMode = SEEK_SET;	break;
			case StreamPos::Current:	iMode = SEEK_CUR;	break;
			case StreamPos::End:		iMode = SEEK_END;	break;
			default:
				throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
					L"Unknown seek mode.", CR_INFO());
			}

			int iFrame = 0;
			if(uDirection == Direction::Forward){
				iFrame = (int32)uFrame;
			}
			else{
				iFrame = (int32)uFrame * -1;
			}

			if(sf_seek(this->m_pData.Get<CSoundData>()->m_pFile, iFrame, iMode) == -1){
				throw Exception::CException(L"Failed to set frame position in sound data.", CR_INFO());
			}
		}

		const uint32	CSound::GetFrame() const{
			auto iSeek = sf_seek(this->m_pData.Get<CSoundData>()->m_pFile, 0, SEEK_CUR);
			if(iSeek < 0){
				throw Exception::CException(L"Failed to retrieve current pos in sound data.", CR_INFO());
			}
			return (uint32)iSeek;
		}
	}
}