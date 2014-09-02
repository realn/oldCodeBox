#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	namespace Threads{
		class CMutex;

		//=============================================================
		//	Mutex locking object for out-of-scope usage.
		//=============================================================
		class CLock{
		private:
			CMutex&		m_Mutex;

			CLock(const CLock& Lock);
		public:
			CLock(CMutex& Mutex);
			~CLock();
		};
	}
}