#include "../Internal/Output.h"
#include "../Internal/Utils.h"

#include "../Internal/Context.h"

namespace CB{
	COGLOutput::COGLOutput(CRefPtr<COGLAdapter> pAdapter, const uint32 uIndex, const DISPLAY_DEVICEW& deviceInfo) :
		Manage::IManagedObject<COGLAdapter, COGLOutput>(pAdapter),
		m_uIndex(uIndex),
		m_DeviceInfo(deviceInfo),
		m_bDisplayChanged(false)
	{
		Log::Write(CString(L"Initializing OGL Output: ") + m_DeviceInfo.DeviceName);
		CDeviceContext DC = CreateDCW(deviceInfo.DeviceName, 0, 0, 0);

		PIXELFORMATDESCRIPTOR pfd = { 0 };
		int iMaxFormat = DescribePixelFormat(DC.Get(), 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
		for(int iFormat = 1; iFormat <= iMaxFormat; iFormat++){
			DescribePixelFormat(DC.Get(), iFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

			Graphic::BufferFormat uFormat = GLUtils::ToColorBufferFormat(pfd);
			if(!Collection::Contains(this->m_SupportedFormats, uFormat)){
				this->m_SupportedFormats.Add(uFormat);
			}
		}
	}

	COGLOutput::~COGLOutput(){
		Log::Write(L"Deinitializing Output: " + this->GetName());
		if(this->m_bDisplayChanged){
			ChangeDisplaySettingsExW(this->m_DeviceInfo.DeviceName, 0, 0, CDS_RESET, 0);
		}
	}

	HDC	COGLOutput::CreateDeviceContext(){
		return CreateDCW(this->m_DeviceInfo.DeviceName, 0, 0, 0);
	}

	const uint32	COGLOutput::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IAdapter>	COGLOutput::GetAdapter() const{
		return this->m_pParent.Cast<Graphic::IAdapter>();
	}

	const uint32	COGLOutput::GetIndex() const{
		return this->m_uIndex;
	}

	const CString	COGLOutput::GetName() const{
		return this->m_DeviceInfo.DeviceName;
	}

	const uint32	COGLOutput::GetNumberOfDisplayModes(const Graphic::BufferFormat uFormat) const{
		if(!Collection::Contains(this->m_SupportedFormats, uFormat)){
			return 0;
		}

		uint32 uMode = 0;
		DEVMODEW mode = { 0 };
		mode.dmSize = sizeof(DEVMODEW);
		while(EnumDisplaySettingsExW(this->m_DeviceInfo.DeviceName, uMode, &mode, 0)){
			uMode++;
		}
		return uMode;
	}

	const Collection::CList<Graphic::CDisplayMode>	COGLOutput::GetDisplayModes(const Graphic::BufferFormat uFormat) const{
		if(!Collection::Contains(this->m_SupportedFormats, uFormat)){
			return Collection::CList<Graphic::CDisplayMode>();
		}

		Collection::CList<Graphic::CDisplayMode> modeList;
		DEVMODEW mode = { 0 };
		uint32 uBits = GLUtils::GetBitsPerPixel(uFormat);

		mode.dmSize = sizeof(DEVMODEW);
		for(uint32 uMode = 0; EnumDisplaySettingsExW(this->m_DeviceInfo.DeviceName, uMode, &mode, 0); uMode++){
			if(!(mode.dmFields & DM_BITSPERPEL && 
				mode.dmFields & DM_PELSWIDTH && 
				mode.dmFields & DM_PELSHEIGHT && 
				mode.dmFields & DM_DISPLAYFREQUENCY)){
				continue;
			}

			Graphic::CDisplayMode displayMode(Math::CSize(mode.dmPelsWidth, mode.dmPelsHeight), mode.dmDisplayFrequency, uFormat);
			
			if(Collection::Contains(modeList, displayMode))
				continue;

			modeList.Add(displayMode);
		}

		return modeList;
	}

	const Graphic::CDisplayMode	COGLOutput::GetCurrentMode() const{
		DEVMODEW devMode = { 0 };
		devMode.dmSize = sizeof(DEVMODEW);

		if(!EnumDisplaySettingsExW(this->m_DeviceInfo.DeviceName, ENUM_CURRENT_SETTINGS, &devMode, 0)){
			throw Exception::CWindowException(GetLastError(), L"Failed to retrieve current display mode.", CR_INFO());
		}

		Graphic::BufferFormat uFormat = Graphic::BufferFormat::Unknown;
		{
			CDeviceContext DC = CreateDCW(this->m_DeviceInfo.DeviceName, 0, 0, 0);
			
			int iFormat = GetPixelFormat(DC.Get());
			if(iFormat != 0){
				PIXELFORMATDESCRIPTOR pfd = { 0 };
				pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);

				if(DescribePixelFormat(DC.Get(), iFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)){
					uFormat = GLUtils::ToColorBufferFormat(pfd);
				}
			}
		}

		return Graphic::CDisplayMode(Math::CSize(devMode.dmPelsWidth, devMode.dmPelsHeight), devMode.dmDisplayFrequency, uFormat);
	}

	void	COGLOutput::SetCurrentMode(const Graphic::CDisplayMode& Mode){
		DEVMODEW devMode = { 0 };

		devMode.dmSize = sizeof(DEVMODEW);
		devMode.dmPelsWidth = Mode.Size.Width;
		devMode.dmPelsHeight = Mode.Size.Height;
		devMode.dmDisplayFrequency = Mode.uRefreshRate;
		devMode.dmBitsPerPel = GLUtils::GetBitsPerPixel(Mode.uFormat);

		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if(devMode.dmDisplayFrequency != 0){
			devMode.dmFields |= DM_DISPLAYFREQUENCY;
		}

		if(this->m_bDisplayChanged){
			ChangeDisplaySettingsExW(this->m_DeviceInfo.DeviceName, 0, 0, CDS_RESET, 0);
			this->m_bDisplayChanged = false;
		}

		if(ChangeDisplaySettingsExW(this->m_DeviceInfo.DeviceName, &devMode, 0, CDS_FULLSCREEN, 0) != DISP_CHANGE_SUCCESSFUL){
			CR_THROWWIN(GetLastError(), L"Failed to change display mode to: " + Mode.ToString());
		}
		this->m_bDisplayChanged = true;
		Log::Write(L"Changed device " + this->GetName() + L" display mode to: " + Mode.ToString());
	}
}