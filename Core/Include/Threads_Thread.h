#pragma once

#include "Macros.h"
#include "Types.h"
#include "SmartPointers_Hidden.h"

namespace CB{
	namespace Threads{
		//=============================================================
		//	Thread abstract class, for derived usage.
		//=============================================================
		class IThread{
		private:
			CHiddenPtr	m_pHandle;
			uint32		m_uID;
			bool		m_bRunning;

			IThread(const IThread& Thread);
		protected:

			IThread();
			IThread(const bool bStarted);
			virtual ~IThread();
		public:
			void	Suspend();
			void	Resume();

			virtual void	RunThread() = 0;

			const bool	IsRunning() const;
			const bool	IsSuspended() const;

			void*	GetHandle() const;
		};

		extern COMMON_API void	Wait(const uint32 uMiliseconds);
	}
}