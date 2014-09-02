#include "stdafx.h"
#include "../Include/Threads_Mutex.h"
#include "../Include/SmartPointers_AutoPtr.h"
#include "../Include/Memory.h"

namespace CB{
	namespace Threads{
		CMutex::CMutex(const CMutex& Mutex){
		}

		CMutex::CMutex(){
			CAutoPtr<CRITICAL_SECTION> pData = new CRITICAL_SECTION();
			Memory::SetZero(*pData);
			InitializeCriticalSection(pData.Get());
			this->m_pHandle.Set<CRITICAL_SECTION>(pData.Reset());
		}

		CMutex::~CMutex(){
			DeleteCriticalSection(this->m_pHandle.Get<CRITICAL_SECTION>());
			this->m_pHandle.Delete<CRITICAL_SECTION>();
		}

		void	CMutex::Lock(){
			void* pSection = this->GetHandle();
			EnterCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(pSection));
		}

		void	CMutex::Unlock(){
			void* pSection = this->GetHandle();
			LeaveCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(pSection));
		}

		void*	CMutex::GetHandle() const{
			return this->m_pHandle.Get<void>();
		}
	}
}