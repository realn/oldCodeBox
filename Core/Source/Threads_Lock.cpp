#include "stdafx.h"
#include "../Include/Threads_Lock.h"
#include "../Include/Threads_Mutex.h"

namespace CB{
	namespace Threads{
		CLock::CLock(const CLock& Lock) : 
			m_Mutex(Lock.m_Mutex)
		{
		}

		CLock::CLock(CMutex& Mutex) : 
			m_Mutex(Mutex)
		{
			m_Mutex.Lock();
		}

		CLock::~CLock(){
			m_Mutex.Unlock();
		}
	}
}