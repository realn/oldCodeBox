#include "../Include/Tools_BindGuards.h"
#include <Logger.h>

namespace CB{
	namespace Tools{
		CGuardShader::CGuardShader(CRefPtr<Graphic::IDevice> pDevice, const Graphic::ShaderType uType) :
			m_uType(uType),
			m_pDevice(pDevice)
		{
			this->m_pShader = this->m_pDevice->GetShader(this->m_uType);
		}

		CGuardShader::CGuardShader(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IShader> pShader) :
			m_uType(pShader->GetType()),
			m_pDevice(pDevice)
		{
			this->m_pShader = this->m_pDevice->GetShader(this->m_uType);
			this->m_pDevice->SetShader(pShader);
		}

		CGuardShader::~CGuardShader(){
			try{
				if(this->m_pShader.IsValid()){
					this->m_pDevice->SetShader(this->m_pShader);
				}
				else{
					this->m_pDevice->FreeShader(this->m_uType);
				}
			}
			catch(Exception::CException& Exception){
				Log::Write(Exception, Log::LogLevel::Warning);
			}
		}

		CGuardVertexDecl::CGuardVertexDecl(CRefPtr<Graphic::IDevice> pDevie) :
			m_pDevice(pDevie)
		{
			this->m_pDecl = this->m_pDevice->GetVertexDeclaration();
		}

		CGuardVertexDecl::CGuardVertexDecl(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IVertexDeclaration> pDecl) :
			m_pDevice(pDevice)
		{
			this->m_pDecl = this->m_pDevice->GetVertexDeclaration();
			this->m_pDevice->SetVertexDeclaration(pDecl);
		}

		CGuardVertexDecl::~CGuardVertexDecl(){
			try{
				if(this->m_pDecl.IsValid()){
					this->m_pDevice->SetVertexDeclaration(this->m_pDecl);
				}
				else{
					this->m_pDevice->FreeVertexDeclaration();
				}
			}
			catch(Exception::CException& Exception){
				Log::Write(Exception, Log::LogLevel::Warning);
			}
		}

		CGuardVertexStream::CGuardVertexStream(CRefPtr<Graphic::IDevice> pDevice, const uint32 uStream) :
			m_uStream(uStream),
			m_pDevice(pDevice)
		{
			this->m_pBuffer = this->m_pDevice->GetVertexBuffer(this->m_uStream);
		}

		CGuardVertexStream::CGuardVertexStream(CRefPtr<Graphic::IDevice> pDevice, const uint32 uStream, CRefPtr<Graphic::IBuffer> pBuffer) :
			m_uStream(uStream),
			m_pDevice(pDevice)
		{
			this->m_pBuffer = this->m_pDevice->GetVertexBuffer(this->m_uStream);
			this->m_pDevice->SetVertexBuffer(this->m_uStream, pBuffer);
		}

		CGuardVertexStream::~CGuardVertexStream(){
			try{
				if(this->m_pBuffer.IsValid()){
					this->m_pDevice->SetVertexBuffer(this->m_uStream, this->m_pBuffer);
				}
				else{
					this->m_pDevice->FreeVertexBuffer(this->m_uStream);
				}
			}
			catch(Exception::CException& Exception){
				Log::Write(Exception, Log::LogLevel::Warning);
			}
		}

		CGuardIndexStream::CGuardIndexStream(CRefPtr<Graphic::IDevice> pDevice) :
			m_pDevice(pDevice)
		{
			this->m_pBuffer = this->m_pDevice->GetIndexBuffer();
		}

		CGuardIndexStream::CGuardIndexStream(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IBuffer> pBuffer) :
			m_pDevice(pDevice)
		{
			this->m_pBuffer = this->m_pDevice->GetIndexBuffer();
			this->m_pDevice->SetIndexBuffer(pBuffer);
		}

		CGuardIndexStream::~CGuardIndexStream(){
			try{
				if(this->m_pBuffer.IsValid()){
					this->m_pDevice->SetIndexBuffer(this->m_pBuffer);
				}
				else{
					this->m_pDevice->FreeIndexBuffer();
				}
			}
			catch(Exception::CException& Exception){
				Log::Write(Exception, Log::LogLevel::Warning);
			}
		}

		CGuardDeviceState::CGuardDeviceState(CRefPtr<Graphic::IDevice> pDevice, const Graphic::DeviceStateType uType) :
			m_uType(uType),
			m_pDevice(pDevice)
		{
			this->m_pState = this->m_pDevice->GetState(this->m_uType);
		}

		CGuardDeviceState::CGuardDeviceState(CRefPtr<Graphic::IDevice> pDevice, CRefPtr<Graphic::IDeviceState> pState) :
			m_uType(pState->GetType()),
			m_pDevice(pDevice)
		{
			this->m_pState = this->m_pDevice->GetState(this->m_uType);
			this->m_pDevice->SetState(pState);
		}

		CGuardDeviceState::~CGuardDeviceState(){
			try{
				if(this->m_pState.IsValid()){
					this->m_pDevice->SetState(this->m_pState);
				}
				else{
					this->m_pDevice->FreeState(this->m_uType);
				}
			}
			catch(Exception::CException& Exception){
				Log::Write(Exception, Log::LogLevel::Warning);
			}
		}
	}
}