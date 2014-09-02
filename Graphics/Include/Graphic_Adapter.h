#pragma once

#include <Types.h>
#include <CBString.h>

namespace CB{
	namespace Graphic{
		extern const uint32	DEFAULT_ADAPTER;

		class CAdapter{
		private:
			const uint32	m_uIndex;
			CString			m_strId;
			CString			m_strName;
			CString			m_strDesc;

		public:
			CAdapter( uint32 uIndex = DEFAULT_ADAPTER );
			~CAdapter();

			const CString	GetId() const;
			const CString	GetName() const;
			const CString	GetDescription() const;

			static const uint32	Count();
			const uint32		CountDisplays() const;
		};
	}
}