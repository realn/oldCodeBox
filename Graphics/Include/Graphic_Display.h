#pragma once

#include <Types.h>
#include <CBString.h>

namespace CB{
	namespace Graphic{
		class CAdapter;

		extern const uint32	DEFAULT_DISPLAY;

		class CDisplay{
		private:
			uint32	m_uIndex;
			CString m_strId;
			CString m_strName;
			CString	m_strDesc;
			CString m_strDevName;

		public:
			CDisplay( const uint32 uIndex = DEFAULT_DISPLAY );
			CDisplay( const CAdapter& adapter, const uint32 uIndex = DEFAULT_DISPLAY );
			~CDisplay();

			const CString&	GetId() const;
			const CString&	GetName() const;
			const CString&	GetDescription() const;
			const CString&	GetDeviceName() const;

			static const uint32	Count();
			static const uint32 Count( const CAdapter& adapter );
			const uint32		CountModes() const;

		private:
			void	Init( const CAdapter& adapter );
		};
	}
}