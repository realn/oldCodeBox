#include "../Internal/Adapter.h"
#include "../Internal/Utils.h"
#include "../Internal/Output.h"
#include "../Internal/Device.h"
#include "../Internal/DisplayDeviceInfo.h"

namespace CB{
	COGLAdapter::COGLAdapter(CRefPtr<COGLManager> pManager, const uint32 uIndex, const CDisplayDeviceInfo& DeviceInfo, const Collection::CDictionary<CString, C ) :
		IManagedObject<COGLManager, COGLAdapter>(pManager),
		m_uIndex(uIndex),
		m_strDeviceID(strDeviceID),
		m_DeviceInfo(DeviceInfo),
		m_strName(DeviceInfo.Info.DeviceString)
	{
		Log::Write(L"Initializing OGL Adapter: " + m_strName);

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
		Log::Write(L"Deinitializing OGL Adapter: " + m_strName);
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
		return this->m_strName;
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

		auto pOGLOutput = pOutput.Cast<COGLOutput>();


		PIXELFORMATDESCRIPTOR pfd = { 0 };

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;

		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE;

		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

		GLUtils::SetPixelFormat(pfd, Desc.BackBuffer.uFormat);
		GLUtils::SetPixelFormat(pfd, Desc.uDepthStencilFormat);

		return new COGLDevice(this, pfd, Desc.OutputWindow, pOGLOutput);
	}

	const int32	COGLAdapter::FindPixelFormat(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc){

	}
}