#pragma once

#include "Macros.h"
#include "Types.h"
#include "SmartPointers_Hidden.h"

namespace CB{
	namespace Threads{
		//=============================================================
		//	Mutex object, that's basically an monitor implemenation.
		//	Designed to use with CLock class.
		//=============================================================
		class CMutex{
		private:
			CHiddenPtr	m_pHandle;

			CMutex(const CMutex& Mutex);
		public:
			CMutex();
			~CMutex();

			void	Lock();
			void	Unlock();

			void*	GetHandle() const;
		};
	}
}