#pragma once

#include <Types.h>
#include <Math_Size2D.h>

#include "Graphic_Consts.h"

namespace CB{
	namespace Graphic{
		class IOutputWindow;

		class CDeviceParameters{
		public:
			IOutputWindow*	pOutputWindow;

			Math::CSize2D	BackBufferSize;
			BufferFormat	BackBufferFormat;
			
			BufferFormat	DepthStencilFormat;

			bool	bFullScreen;
			uint32	uFullScreenRefreshRate;

			CDeviceParameters();
			CDeviceParameters( const CDeviceParameters& params );
			CDeviceParameters( 
				IOutputWindow* pOutput, 
				Math::CSize2D BBSize = Math::CSize2D(0),
				BufferFormat BBFormat = BufferFormat::Unknown,
				BufferFormat DSFormat = BufferFormat::Unknown,
				bool	fullScreen = false,
				uint32	refreshRate = 0
				);
		};
	}
}
