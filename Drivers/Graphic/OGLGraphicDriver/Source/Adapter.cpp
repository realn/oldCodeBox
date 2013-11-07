#include "../Internal/Adapter.h"
#include "../Internal/Utils.h"
#include "../Internal/Output.h"
#include "../Internal/Device.h"

namespace CB{
	COGLAdapter::COGLAdapter(CRefPtr<COGLManager> pManager, const uint32 uIndex, const CString& strDeviceID, const DISPLAY_DEVICEW& DeviceInfo ) :
		IManagedObject<COGLManager, COGLAdapter>(pManager),
		m_uIndex(uIndex),
		m_strDeviceID(strDeviceID),
		m_DeviceInfo(DeviceInfo)
	{
		Log::Write(CString(L"Initializing OGL Adapter: ") + m_DeviceInfo.DeviceString);

		DISPLAY_DEVICEW device = { 0 };
		device.cb = sizeof(DISPLAY_DEVICEW);
		for(uint32 uOutput = 0; EnumDisplayDevicesW(0, uOutput, &device, 0); uOutput++){
			if(!(device.StateFlags & DISPLAY_DEVICE_ACTIVE))
				continue;
			if(strDeviceID != device.DeviceID)
				continue;

			this->m_Outputs.Add(device);
		}
	}

	COGLAdapter::~COGLAdapter(){
		Log::Write(CString(L"Deinitializing OGL Adapter: ") + m_DeviceInfo.DeviceString);
	}

	const uint32	COGLAdapter::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IManager>	COGLAdapter::GetManager() const{
		return this->GetParent().Cast<Graphic::IManager>();
	}

	const uint32	COGLAdapter::GetIndex() const{
		return this->m_uIndex;
	}

	const CString	COGLAdapter::GetName() const{
		return this->m_DeviceInfo.DeviceString;
	}

	const uint32	COGLAdapter::GetNumberOfOutputs() const{
		return this->m_Outputs.GetLength();
	}

	CRefPtr<Graphic::IOutput>	COGLAdapter::GetOutput(const uint32 uIndex){
		return new COGLOutput(this, uIndex, this->m_Outputs[uIndex]);
	}

	CRefPtr<Graphic::IOutput>	COGLAdapter::GetDefaultOutput(){
		return this->GetOutput(0);
	}

	CRefPtr<Graphic::IDevice>	COGLAdapter::CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc){
		return this->CreateDevice(pWindow, Desc, this->GetDefaultOutput());
	}

	CRefPtr<Graphic::IDevice>	COGLAdapter::CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc, CRefPtr<Graphic::IOutput> pOutput){
		CR_APICHECK(this, pOutput);

		PIXELFORMATDESCRIPTOR pfd = { 0 };

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;

		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE;

		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

		GLUtils::SetPixelFormat(pfd, Desc.BackBuffer.uFormat);
		GLUtils::SetPixelFormat(pfd, Desc.uDepthStencilFormat);

		return new COGLDevice(this, pfd, Desc.OutputWindow, pOutput.Cast<COGLOutput>());
	}
}