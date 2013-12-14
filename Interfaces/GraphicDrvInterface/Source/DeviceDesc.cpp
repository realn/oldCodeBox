#include "../Include/GraphicDriver_Structs.h"
#include "../Include/GraphicDriver_Strings.h"
#include <CBStringEx.h>

namespace CB{
	namespace Graphic{
		CDeviceDesc::CDeviceDesc() : 
			uDepthStencilFormat(BufferFormat::D24S8), 
			bFullScreen(false)
		{
		}

		CDeviceDesc::CDeviceDesc(const CDeviceDesc& Desc) :
			BackBuffer(Desc.BackBuffer),
			uDepthStencilFormat(Desc.uDepthStencilFormat),
			bFullScreen(Desc.bFullScreen)
		{
			if(Desc.OutputWindow.IsValid()){
				this->OutputWindow = Desc.OutputWindow;
			}
		}

		CDeviceDesc::CDeviceDesc(CRefPtr<Window::IWindow> pWindow, const CDisplayMode& Mode, const BufferFormat uDepthStencilFormat) :
			OutputWindow(pWindow),
			BackBuffer(Mode),
			uDepthStencilFormat(uDepthStencilFormat),
			bFullScreen(false)
		{
		}

		CDeviceDesc::CDeviceDesc(CRefPtr<Window::IWindow> pWindow, const CDisplayMode& Mode, const BufferFormat uDepthStencilFormat, const bool bFullScreen) :
			OutputWindow(pWindow),
			BackBuffer(Mode),
			uDepthStencilFormat(uDepthStencilFormat),
			bFullScreen(bFullScreen)
		{
		}

		const CDeviceDesc&	CDeviceDesc::operator=(const CDeviceDesc& Desc){
			if(Desc.OutputWindow.IsValid()){
				this->OutputWindow = Desc.OutputWindow;
			}
			else{
				this->OutputWindow.Reset();
			}
			this->BackBuffer = Desc.BackBuffer;
			this->uDepthStencilFormat = Desc.uDepthStencilFormat;
			this->bFullScreen = Desc.bFullScreen;

			return *this;
		}

		const CString	CDeviceDesc::ToString() const{
			Collection::CStringList list;
			if(this->OutputWindow.IsValid()){
				list.Add(L"OutputWindow: (" + this->OutputWindow->GetTitle() + L")");
			}
			else{
				list.Add(L"OutputWindow: (NULL)");
			}
			list.Add(L"BackBuffer: (" + this->BackBuffer.ToString() + L")");
			list.Add(L"DepthStencilFormat: " + String::ToString(this->uDepthStencilFormat));
			list.Add(L"FullScreen: " + String::FromBool(this->bFullScreen));
			
			return list.ToString(L", ");
		}
	}
}