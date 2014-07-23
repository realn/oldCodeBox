#include "stdafx.h"
#include "../Include/Timer.h"
#include "../Internal/WinPlatform.h"
#include "../Include/Exception.h"
#include "../Include/WindowsErrors.h"

namespace CB{
	CTimer::CTimer() :
		m_uLastTime(0),
		m_uThisTime(0),
		m_uFrequency(0)
	{
		if(!QueryPerformanceFrequency((LARGE_INTEGER*)&this->m_uFrequency)){
			CR_THROWWIN(GetLastError(), L"Cannot query performance counter frequency.");
		}

		if(!QueryPerformanceCounter((LARGE_INTEGER*)&this->m_uThisTime)){
			CR_THROWWIN(GetLastError(), L"Failed to query current performance counter time.");
		}

		this->m_uLastTime = this->m_uThisTime - 1;
	}

	CTimer::~CTimer(){
	}

	const float32	CTimer::GetTimeDelta() const{
		return (float32)this->GetTimeDeltaDouble();
	}

	const float64	CTimer::GetTimeDeltaDouble() const{
		return (float64)(this->m_uThisTime - this->m_uLastTime) / (float64)this->m_uFrequency;
	}

	void	CTimer::Update(){
		uint64 uTick = 0;

		if(QueryPerformanceCounter((LARGE_INTEGER*)&uTick)){
			this->m_uLastTime = this->m_uThisTime;
			this->m_uThisTime = uTick;
		}
	}
}