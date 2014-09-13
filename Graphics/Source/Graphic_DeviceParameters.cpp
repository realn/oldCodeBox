#include "stdafx.h"
#include "../Include/Graphic_DeviceParameters.h"

namespace CB{
	namespace Graphic{
		CDeviceParameters::CDeviceParameters() :
			pOutputWindow( nullptr ),
			BackBufferSize( 0 ),
			BackBufferFormat( BufferFormat::Unknown ),
			DepthStencilFormat( BufferFormat::Unknown ),
			bFullScreen( false ),
			uFullScreenRefreshRate( 0 )
		{}

		CDeviceParameters::CDeviceParameters(const CDeviceParameters& params ) :
			pOutputWindow( params.pOutputWindow ),
			BackBufferSize( params.BackBufferSize ),
			BackBufferFormat( params.BackBufferFormat ),
			DepthStencilFormat( params.DepthStencilFormat ),
			bFullScreen( params.bFullScreen ),
			uFullScreenRefreshRate( params.uFullScreenRefreshRate )
		{}

		CDeviceParameters::CDeviceParameters( 
			IOutputWindow* pOutput, 
			Math::CSize2D BBSize, 
			BufferFormat BBFormat, 
			BufferFormat DSFormat, 
			bool	fullScreen, 
			uint32	refreshRate
			) :
			pOutputWindow( pOutput ),
			BackBufferSize( BBSize),
			BackBufferFormat( BBFormat ),
			DepthStencilFormat( DSFormat ),
			bFullScreen( fullScreen ),
			uFullScreenRefreshRate( refreshRate )
		{}
	}
}