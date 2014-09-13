#pragma once

namespace CB{
	namespace Internal{
		class CRCBindGuard{
		private:
			void*	m_hDC;
			void*	m_hRC;

		public:
			CRCBindGuard();
			~CRCBindGuard();
		};
	}
}