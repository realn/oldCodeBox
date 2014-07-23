#include "stdafx.h"
#include "../Include/Threads.h"
#include "../Include/Exception.h"
#include "../Include/SmartPointers_AutoPtr.h"
#include "../Include/Memory.h"

namespace CB{
	namespace Threads{
		DWORD WINAPI	ThreadProc(void* pUserData){
			auto pThread = reinterpret_cast<IThread*>(pUserData);

			pThread->RunThread();

			return 0;
		}

		IThread::IThread() :
			m_bRunning(false),
			m_uID(0)
		{
			HANDLE hThread = CreateThread(0, 0, ThreadProc, this, 0, reinterpret_cast<DWORD*>(&this->m_uID));
			if(hThread== 0 || hThread == INVALID_HANDLE_VALUE){
				CR_THROW(L"Failed to create thread.");
			}
			this->m_pHandle.Set<void>(hThread);
			this->m_bRunning = true;
		}

		IThread::IThread(const IThread& Thread){
		}

		IThread::IThread(const bool bStarted) :
			m_bRunning(false),
			m_uID(0)
		{
			HANDLE hThread = CreateThread(0, 0, ThreadProc, this, bStarted ? CREATE_SUSPENDED : 0, reinterpret_cast<DWORD*>(&this->m_uID));
			if(hThread== 0 || hThread == INVALID_HANDLE_VALUE){
				CR_THROW(L"Failed to create thread.");
			}
			this->m_pHandle.Set<void>(hThread);
			this->m_bRunning = bStarted;
		}

		IThread::~IThread(){
			try{
				if(this->m_pHandle.IsValid()){
					if(!CloseHandle(this->m_pHandle.Get<void>())){
						//	Throw kept for Visual Studio exception tracking.
						CR_THROW(L"Failed to terminate thread.");
					}
					this->m_pHandle.Reset<void>();
				}
			}
			catch(Exception::CException&){}
		}

		void	IThread::Resume(){
			ResumeThread(this->m_pHandle.Get<void>());
			this->m_bRunning = true;
		}

		void	IThread::Suspend(){
			SuspendThread(this->m_pHandle.Get<void>());
			this->m_bRunning = false;
		}

		const bool	IThread::IsRunning() const{
			return this->m_bRunning;
		}

		const bool	IThread::IsSuspended() const{
			return !this->m_bRunning;
		}

		void*	IThread::GetHandle() const{
			return this->m_pHandle.Get<void>();
		}

		//===================

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

		void*	CMutex::GetHandle() const{
			return this->m_pHandle.Get<void>();
		}

		//====================

		CLock::CLock(const CLock& Lock) : 
			m_Mutex(Lock.m_Mutex)
		{
		}

		CLock::CLock(CMutex& Mutex) : 
			m_Mutex(Mutex)
		{
			void* pSection = this->m_Mutex.GetHandle();
			EnterCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(pSection));
		}

		CLock::~CLock(){
			void* pSection = this->m_Mutex.GetHandle();
			LeaveCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(pSection));
		}

		//===============================================================================
		//	FUNCS	
		//===============================================================================

		void	Wait(const uint32 uMiliseconds){
			Sleep((DWORD)uMiliseconds);
		}
	}
}