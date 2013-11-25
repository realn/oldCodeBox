#include "../Internal/Manager.h"
#include "../Internal/Adapter.h"
#include <CBStringEx.h>
#include <Logger.h>
#include <Collection_Funcs.h>

#include <als\alc.h>
#pragma comment(lib, "OpenAL32.lib")

namespace CB{
	const uint32	g_uApiId = *reinterpret_cast<uint32*>("OALS");
	const uint32	MAX_DEVICES_CHARS = 512;

	COALManager::COALManager(CRefPtr<Audio::IDriver> pDriver) :
		m_pDriver(pDriver)
	{
		Log::Write(L"Initializing OpenAL Audio manager...");
		auto szDevices = alcGetString(0, ALC_DEVICE_SPECIFIER);
		if(szDevices == 0){
			CR_THROW(L"Failed to enumerate adapters - got null pointer.");
		}
		if(szDevices[0] == 0 && szDevices[1] == 0){
			CR_THROW(L"Failed to enumerate adapters - empty list.");
		}

		Log::Write(L"Enumerating audio adapters...", Log::LogLevel::Debug);
		uint32 uLastPos = 0;
		for(uint32 uIndex = 0; uIndex < MAX_DEVICES_CHARS; uIndex++){
			if(szDevices[uIndex] == 0 && uIndex - uLastPos > 0){
				Collection::CList<int8> szAdapter(uIndex - uLastPos);
				Memory::CopyArray<int8>(reinterpret_cast<const int8*>(szDevices + uLastPos), szAdapter.GetPointer(), szAdapter.GetLength());

				auto strAdapter = String::FromANSI(szAdapter);
				Log::Write(L"Audio Adapter Found: " + strAdapter, Log::LogLevel::Debug);

				this->m_strAdapterList.Add(strAdapter);

				uLastPos = uIndex + 1;
				if(szDevices[uIndex + 1] == 0){
					break;
				}
			}
		}
		Log::Write(L"End of enumeration of audio adapters.", Log::LogLevel::Debug);

		if(!this->m_strAdapterList.IsEmpty()){
			Log::Write(L"Finding default audio adapter...", Log::LogLevel::Debug);

			auto szDevice = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);
			if(szDevice == 0){
				Log::Write(L"Got null pointer for default device - assuming default as first in list.");
			}
			CString strAdapter = String::FromANSI(reinterpret_cast<const int8*>(szDevice));
			Log::Write(L"Found default audio adapter: " + strAdapter, Log::LogLevel::Debug);

			uint32 uIndex = 0;
			if(Collection::TryFind(this->m_strAdapterList, strAdapter, uIndex)){
				if(uIndex != 0){
					this->m_strAdapterList.Remove(uIndex);
					this->m_strAdapterList.Insert(0, strAdapter);
				}
			}
			else{
				Log::Write(L"Default adapter " + strAdapter + L" not found on list - adding ass default.", Log::LogLevel::Debug);
				this->m_strAdapterList.Insert(0, strAdapter);
			}
		}
	}

	COALManager::~COALManager(){
		Log::Write(L"Deinitializing OpenAL Audio Manager...");
	}

	const uint32	COALManager::GetApiId() const{
		return g_uApiId;
	}

	const uint32		COALManager::GetNumberOfAdapters() const{
		return this->m_strAdapterList.GetLength();
	}

	const bool	CompareAdapter(const CPtr<COALAdapter>& pAdapter, const uint32& uIndex){
		return pAdapter->GetIndex() == uIndex;
	}

	CRefPtr<Audio::IAdapter>	COALManager::GetAdapter(const uint32 uIndex){
		uint32 uOutIndex = 0;
		if(Collection::TryFind(this->m_pObjectList, CompareAdapter, uIndex, uOutIndex)){
			return this->m_pObjectList[uOutIndex].GetCast<Audio::IAdapter>();
		}
		
		return new COALAdapter(this, this->m_strAdapterList[uIndex], uIndex);
	}

	CRefPtr<Audio::IAdapter>	COALManager::GetDefaultAdapter(){
		return this->GetAdapter(0);
	}
}