#include "../Internal/Manager.h"
#include "../Internal/Adapter.h"
#include "../Internal/Utils.h"

#include <CBStringEx.h>
#include <Logger.h>
#include <Collection_Funcs.h>

namespace CB{
	const uint32	g_uApiId = *reinterpret_cast<uint32*>("PtAo");

	CPAManager::CPAManager(CRefPtr<Audio::IDriver> pDriver) :
		m_pDriver(pDriver),
		m_uDefaultIndex(0)
	{
		Log::Write(L"Initializing PortAudio Audio manager...");

		auto uError = Pa_Initialize();
		if(uError != paNoError){
			CR_THROW(L"Failed to initialize port audio, Error: " + Utils::ToErrorString(uError));
		}

		Log::Write(L"Enumerating audio adapters...", Log::LogLevel::Debug);
		auto uDeviceCount = Pa_GetDeviceCount();
		for(PaDeviceIndex uIndex = 0; uIndex < uDeviceCount; uIndex++){
			auto pInfo = Pa_GetDeviceInfo(uIndex);
			auto pApiInfo = Pa_GetHostApiInfo(pInfo->hostApi);
			
			auto strAdapter = String::FromANSI(reinterpret_cast<const int8*>(pInfo->name));
			auto strHostApi = String::FromANSI(reinterpret_cast<const int8*>(pApiInfo->name));

			strAdapter += L"[" + strHostApi + L"]";

			Log::Write(L"Audio Adapter Found: " + strAdapter, Log::LogLevel::Debug);
			this->m_strAdapterList.Add(strAdapter);
		}
		Log::Write(L"End of enumeration of audio adapters.", Log::LogLevel::Debug);

		if(!this->m_strAdapterList.IsEmpty()){
			Log::Write(L"Finding default audio adapter...", Log::LogLevel::Debug);

			auto uDefaultIndex = Pa_GetDefaultOutputDevice();
			if(uDefaultIndex == paNoDevice){
				Log::Write(L"Got null pointer for default device - assuming default as first in list.");
				uDefaultIndex = 0;
			}

			auto pInfo = Pa_GetDeviceInfo(uDefaultIndex);
			auto pApiInfo = Pa_GetHostApiInfo(pInfo->hostApi);
			
			auto strAdapter = String::FromANSI(reinterpret_cast<const int8*>(pInfo->name));
			auto strHostApi = String::FromANSI(reinterpret_cast<const int8*>(pApiInfo->name));

			strAdapter += L"[" + strHostApi + L"]";
			Log::Write(L"Found default PortAudio adapter: " + strAdapter, Log::LogLevel::Debug);

			this->m_uDefaultIndex = uDefaultIndex;
		}
	}

	CPAManager::~CPAManager(){
		Log::Write(L"Deinitializing OpenAL Audio Manager...");
		auto uError = Pa_Terminate();
		if(uError != paNoError){
			Log::Write(L"Error on audio manager deinitialization: " + Utils::ToErrorString(uError), Log::LogLevel::Error);
		}
	}

	const uint32	CPAManager::GetApiId() const{
		return g_uApiId;
	}

	const uint32		CPAManager::GetNumberOfAdapters() const{
		return this->m_strAdapterList.GetLength();
	}

	const bool	CompareAdapter(const CPtr<CPAAdapter>& pAdapter, const uint32& uIndex){
		return pAdapter->GetIndex() == uIndex;
	}

	CRefPtr<Audio::IAdapter>	CPAManager::GetAdapter(const uint32 uIndex){
		uint32 uOutIndex = 0;
		if(Collection::TryFind(this->m_pObjectList, CompareAdapter, uIndex, uOutIndex)){
			return this->m_pObjectList[uOutIndex].GetCast<Audio::IAdapter>();
		}
		
		return new CPAAdapter(this, this->m_strAdapterList[uIndex], uIndex);
	}

	CRefPtr<Audio::IAdapter>	CPAManager::GetDefaultAdapter(){
		return this->GetAdapter(this->m_uDefaultIndex);
	}
}