#pragma once

#include <Types.h>
#include <SmartPointers_AutoPtr.h>
#include "Graphic_Consts.h"

namespace CB{
	namespace Collection{
		template<typename _Type> class ICountable;
	}

	namespace Internal{
		class CDeviceContext;
		class CRenderContext;
	}

	namespace Graphic{
		class IOutputWindow;
		class CDeviceParameters;
		class CAdapter;
		class CDisplay;

		class CDevice{
		private:
			IOutputWindow*	m_pOutputWindow;
			CAutoPtr<Internal::CDeviceContext>	m_pDC;
			CAutoPtr<Internal::CRenderContext>	m_pRC;
			FeatureLevel	m_FeatureLevel;

		public:
			CDevice( const CDeviceParameters& params, const Collection::ICountable<FeatureLevel>& featureLevel );
			CDevice( const CDeviceParameters& params, const Collection::ICountable<FeatureLevel>& featureLevel, const CAdapter& adapter );
			CDevice( const CDeviceParameters& params, const Collection::ICountable<FeatureLevel>& featureLevel, const CDisplay& display );
			~CDevice();

			IOutputWindow*	GetOuputWindow() const;

			void	SetOutputWindow( IOutputWindow* pOutput );
		};
	}
}