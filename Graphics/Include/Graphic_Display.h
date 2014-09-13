#pragma once

#include <Types.h>
#include <CBString.h>

namespace CB{
	namespace Collection{
		template<typename _T>	class CList;
	}

	namespace Math{
		class CRectangle;
	}

	namespace Graphic{
		class CAdapter;
		class CDisplayMode;

		extern const uint32	DEFAULT_DISPLAY;

		class CDisplay{
		private:
			const uint32	m_uIndex;
			uint32	m_uAdapterIndex;
			CString m_strId;
			CString m_strName;

			void*	m_Handle;

		public:
			CDisplay( const uint32 uIndex = DEFAULT_DISPLAY );
			CDisplay( const CAdapter& adapter, const uint32 uIndex = DEFAULT_DISPLAY );
			~CDisplay();

			const CString&	GetId() const;
			const CString&	GetName() const;
			const CAdapter	GetAdapter() const;

			const Math::CRectangle	GetRect() const;
			const Math::CRectangle	GetClientRect() const;

			const bool	IsPrimary() const;

			static const uint32	Count();
			static const uint32 Count( const CAdapter& adapter );

			const Collection::CList<CDisplayMode>	GetModes() const;
			const CDisplayMode	GetCurrentMode() const;
			void	SetMode( const CDisplayMode& mode );

			void	SetHandle( void* pHandle );

		private:
			void	Init( const CAdapter& adapter );

			
		};
	}
}