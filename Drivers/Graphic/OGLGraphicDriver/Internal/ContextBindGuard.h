#pragma once

#include <Types.h>

namespace CB{
	class CRCBindGuard{
	private:
		void*	m_hDC;
		void*	m_hRC;

	public:
		CRCBindGuard();
		~CRCBindGuard();
	};
}