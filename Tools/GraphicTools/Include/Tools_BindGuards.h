#pragma once

#include "Macros.h"
#include <GraphicDriver.h>

namespace CB{
	namespace Tools{
		class GRAPHICTOOLS_API CGuardShader{
		private:
			Graphic::ShaderType			m_uType;
			CRefPtr<Graphic::IDevice>	m_pDevice;
			CRefPtr<Graphic::IShader>	m_pShader;

		public:
			CGuardShader(CRefPtr<Graphic::IDevice> pDevice, const Graphic::ShaderType uType);
			CGuardShader(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IShader> pShader);
			~CGuardShader();

		private:
			CR_NOASSIGN(CGuardShader);
			CR_NOCOPY(CGuardShader);
		};

		class GRAPHICTOOLS_API CGuardVertexDecl{
		private:
			CRefPtr<Graphic::IDevice>	m_pDevice;
			CRefPtr<Graphic::IVertexDeclaration>	m_pDecl;

		public:
			CGuardVertexDecl(CRefPtr<Graphic::IDevice> pDevice);
			CGuardVertexDecl(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IVertexDeclaration> pDecl);
			~CGuardVertexDecl();

		private:
			CR_NOASSIGN(CGuardVertexDecl);
			CR_NOCOPY(CGuardVertexDecl);
		};

		class GRAPHICTOOLS_API CGuardVertexStream{
		private:
			uint32	m_uStream;
			CRefPtr<Graphic::IDevice> m_pDevice;
			CRefPtr<Graphic::IBuffer> m_pBuffer;

		public:
			CGuardVertexStream(CRefPtr<Graphic::IDevice> pDevice, const uint32 uStream);
			CGuardVertexStream(CRefPtr<Graphic::IDevice> pDevice, const uint32 uStream, CRefPtr<Graphic::IBuffer> pBuffer);
			~CGuardVertexStream();
		};

		class GRAPHICTOOLS_API CGuardIndexStream{
		private:
			CRefPtr<Graphic::IDevice> m_pDevice;
			CRefPtr<Graphic::IBuffer> m_pBuffer;

		public:
			CGuardIndexStream(CRefPtr<Graphic::IDevice> pDevice);
			CGuardIndexStream(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IBuffer> pBuffer);
			~CGuardIndexStream();

		private:
			CR_NOASSIGN(CGuardIndexStream);
			CR_NOCOPY(CGuardIndexStream);
		};

		class GRAPHICTOOLS_API CGuardDeviceState{
		private:
			Graphic::DeviceStateType	m_uType;
			CRefPtr<Graphic::IDevice>	m_pDevice;
			CRefPtr<Graphic::IDeviceState>	m_pState;

		public:
			CGuardDeviceState(CRefPtr<Graphic::IDevice> pDevice, const Graphic::DeviceStateType uType);
			CGuardDeviceState(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IDeviceState> pState);
			~CGuardDeviceState();

		private:
			CR_NOASSIGN(CGuardDeviceState);
			CR_NOCOPY(CGuardDeviceState);
		};
	}
}