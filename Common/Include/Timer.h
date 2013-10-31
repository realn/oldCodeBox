#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class COMMON_API CTimer{
	private:
		uint64	m_uFrequency;
		uint64	m_uLastTime;
		uint64	m_uThisTime;

	public:
		CTimer();
		~CTimer();

		const float32	GetTimeDelta() const;
		const float64	GetTimeDeltaDouble() const;

		void	Update();
	};
}