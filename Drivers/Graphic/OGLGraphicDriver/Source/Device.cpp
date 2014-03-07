#include "../Internal/Device.h"
#include <CBStringEx.h>

//	Buffers
#include "../Internal/VertexBuffer.h"
#include "../Internal/IndexBuffer.h"

//	Shaders
#include "../Internal/VertexShader.h"
#include "../Internal/FragmentShader.h"

//	States
#include "../Internal/DepthStencilState.h"
#include "../Internal/BlendState.h"
#include "../Internal/RasterizerState.h"

//	Textures
#include "../Internal/Texture2D.h"
#include "../Internal/VertexDeclaration.h"

//	Misc
#include "../Internal/Utils.h"
#include "../Internal/ContextBindGuard.h"

namespace CB{
	//==========================================================
	//	Function Callbacks
	//==========================================================

	void ErrorCallback(){
		CGerror uError = cgGetError();
		GLenum	uGLError = GL::glGetError();

		auto strGLerror = L"GLError: " + String::FromUInt32(uGLError);
		auto strCGError = L"CGError: " + String::FromANSI(reinterpret_cast<const int8*>(cgGetErrorString(uError)));

		Log::Write(L"CG error encoutered: " + strGLerror + L" " + strCGError);
	}

	//==========================================================
	//	OpenGL Device implementation.
	//==========================================================

	COGLDevice::COGLDevice(CRefPtr<COGLAdapter> pAdapter, CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc, const Collection::ICountable<Graphic::FeatureLevel>& FeatureLevels, CRefPtr<COGLOutput> pOutput) :
		m_pOutputWindow(pWindow),
		m_pOutput(pOutput),
		m_WindowDC(m_pOutputWindow),
		m_uPrimitiveMode(GL::GL_TRIANGLES),
		m_uSampleMask(0xFFFFFFFF),
		m_uStencilRef(0),
		m_BlendFactor(0.0f),
		Manage::IManagedObject<COGLAdapter, COGLDevice>(pAdapter)
	{
		Log::Write(L"Initializing OpenGL Device.");

		if(Desc.bFullScreen){
			m_pOutput->SetCurrentMode(Desc.BackBuffer);
		}

		{
			auto pWinManager = this->m_pParent->GetParent()->GetWindowManager();
			auto pTempWindow = pWinManager->CreateWindow(L"TempGLContextWindow", Window::Style::Pure);
			this->m_pOutput->AdjustWindowRect(pTempWindow);

			CWindowDeviceContext tempWinDC(pTempWindow);

			PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 24;
			pfd.cStencilBits = 8;
			pfd.iPixelType = PFD::TYPE_RGBA;
			pfd.dwFlags = PFD::DRAW_TO_WINDOW | PFD::SUPPORT_OPENGL | PFD::DOUBLEBUFFER;

			int32 iPixelFormat = tempWinDC.ChoosePixelFormat(pfd);
			if(iPixelFormat == 0){
				CR_THROWWIN(GetLastError(), L"Failed to choose temp pixel format.");
			}
			tempWinDC.SetPixelFormat(iPixelFormat);

			CGLRenderContext tempRC(tempWinDC);
			tempRC.Bind(tempWinDC);

			const bool bCorePixelFormat = tempRC.Load(WGLExtension::PixelFormat);

			if(bCorePixelFormat){
				Collection::CList<int32> Attribs;

				Attribs.Add(WGL::WGL_ACCELERATION);
				Attribs.Add(WGL::WGL_FULL_ACCELERATION);

				Attribs.Add(WGL::WGL_PIXEL_TYPE);
				Attribs.Add(WGL::WGL_TYPE_RGBA);

				Attribs.Add(WGL::WGL_DRAW_TO_WINDOW);
				Attribs.Add(GL::GL_TRUE);

				Attribs.Add(WGL::WGL_DOUBLE_BUFFER);
				Attribs.Add(GL::GL_TRUE);

				Attribs.Add(WGL::WGL_SUPPORT_OPENGL);
				Attribs.Add(GL::GL_TRUE);

				GLUtils::SetPixelFormat(Attribs, Desc.BackBuffer.uFormat);
				GLUtils::SetPixelFormat(Attribs, Desc.uDepthStencilFormat);

				int32 iFormat = tempRC.ChoosePixelFormat(this->m_WindowDC, Attribs);
				if(iFormat < 1){
					CR_THROWWIN(GetLastError(), L"Failed to choose pixel format.");
				}

				this->m_WindowDC.SetPixelFormat(iFormat);
			}
			else{
				Memory::SetZero(pfd);

				pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
				pfd.nVersion = 1;
				pfd.iPixelType = PFD::TYPE_RGBA;
				pfd.dwFlags = PFD::SUPPORT_OPENGL | PFD::DOUBLEBUFFER | PFD::DRAW_TO_WINDOW;

				GLUtils::SetPixelFormat(pfd, Desc.BackBuffer.uFormat);
				GLUtils::SetPixelFormat(pfd, Desc.uDepthStencilFormat);

				int32 iFormat = this->m_WindowDC.ChoosePixelFormat(pfd);
				if(iFormat < 1){
					CR_THROWWIN(GetLastError(), L"Failed to choose pixel format.");
				}

				this->m_WindowDC.SetPixelFormat(iFormat);
			}

			bool bCoreCreate = tempRC.Load(WGLExtension::CreateContext);
			bool bFound = false;
			for(uint32 uFLIndex = 0; uFLIndex < FeatureLevels.GetLength(); uFLIndex++){
				Log::Write(L"Loading feature level: " + String::ToString(FeatureLevels[uFLIndex]));
				if(this->LoadFeatureLevel(tempRC, FeatureLevels[uFLIndex], bCoreCreate)){
					this->m_uFeatureLevel = FeatureLevels[uFLIndex];
					bFound = true;
					break;
				}
			}

			if(!bFound){
				CR_THROW(L"Failed to load any suggested feature level.");
			}
			else{
				Log::Write(L"Selected feature level: " + String::ToString(this->m_uFeatureLevel));
			}
			
		}
		this->m_pRenderContext->Bind(this->m_WindowDC);

		this->m_pCGContext = new CCGContext();
		cgSetErrorCallback(ErrorCallback);
		this->m_pVertexStream.Resize(this->GetNumberOfStreams());

		//	Setting state mashine to default values
		this->SetGLState(Graphic::CBlendStateDesc());
		this->SetGLState(Graphic::CRasterizerStateDesc());
		this->SetGLState(Graphic::CDepthStencilStateDesc());

		{
			GLint iViewport[4];
			this->m_pRenderContext->glGetIntegerv(GL::GL_VIEWPORT, iViewport);
			this->m_Viewport.Set(iViewport[0], iViewport[1], (uint32)iViewport[2], (uint32)iViewport[3]);
		}
		{
			GLint iScissors[4];
			this->m_pRenderContext->glGetIntegerv(GL::GL_SCISSOR_BOX, iScissors);
			this->m_ScissorRect.Set(iScissors[0], iScissors[1], (uint32)iScissors[2], (uint32)iScissors[3]);
		}		
	}

	COGLDevice::~COGLDevice(){
		Log::Write(L"Deinitializing OpenGL Device...");
	}

	CWindowDeviceContext&	COGLDevice::GetDC() const{
		return this->m_WindowDC;
	}

	CGLRenderContext&	COGLDevice::GetRC() const{
		return *this->m_pRenderContext;
	}

	CCGContext&	COGLDevice::GetCGC() const{
		return *this->m_pCGContext;
	}

	CGprofile	COGLDevice::GetCGProfile(const Graphic::ShaderVersion uVersion, const Graphic::ShaderType uType) const{
		switch (uType){
		case Graphic::ShaderType::Vertex:
			switch (uVersion){
			case Graphic::ShaderVersion::ShaderModel_2:	return CG_PROFILE_ARBVP1;
			case Graphic::ShaderVersion::ShaderModel_3:	return CG_PROFILE_GLSLV;
			case Graphic::ShaderVersion::ShaderModel_4:	return CG_PROFILE_GP4VP;
			case Graphic::ShaderVersion::ShaderModel_5:	return CG_PROFILE_GP5VP;
			case Graphic::ShaderVersion::Latest:		return cgGLGetLatestProfile(CG_GL_VERTEX);

			default:
				throw Exception::CInvalidArgumentException(L"uVersion", String::ToString(uVersion),
					L"Unknown vertex shader version.", CR_INFO());
			}

		case Graphic::ShaderType::Fragment:
			switch (uVersion){
			case Graphic::ShaderVersion::ShaderModel_2:	return CG_PROFILE_ARBFP1;
			case Graphic::ShaderVersion::ShaderModel_3:	return CG_PROFILE_GLSLF;
			case Graphic::ShaderVersion::ShaderModel_4:	return CG_PROFILE_GP4FP;
			case Graphic::ShaderVersion::ShaderModel_5:	return CG_PROFILE_GP5FP;
			case Graphic::ShaderVersion::Latest:		return cgGLGetLatestProfile(CG_GL_FRAGMENT);

			default:
				throw Exception::CInvalidArgumentException(L"uVersion", String::ToString(uVersion),
					L"Unknown fragment shader version.", CR_INFO());
			}

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Unknown shader type.", CR_INFO());
		}
	}

	//	OVERRIDES	==========================================================================

	/*
		WARNING
		At this level objects passed to RemoveObject methods, technically don't exist anymore.
		This makes it crucial to DO NOT invoke ANY methods of those objects, because data is
		probably invalid in them, and this can lead to an undefined behaviour (like pure virtual 
		call exception).

		DO NOT INVOKE METHODS OF PASSED OBJECTS.
	*/

	void	COGLDevice::RemoveObject(CPtr<IOGLBaseBuffer> pBuffer){
		if(this->m_pIndexStream == pBuffer){
			this->FreeIndexBuffer();
		}
		for(uint32 uStream = 0; uStream < this->m_pVertexStream.GetLength(); uStream++){
			if(this->m_pVertexStream[uStream] == pBuffer){
				this->FreeVertexBuffer(uStream);
			}
		}
		Manage::IObjectManager<COGLDevice, IOGLBaseBuffer>::RemoveObject(pBuffer);
	}

	void	COGLDevice::RemoveObject(CPtr<IOGLBaseShader> pShader){
		if(this->m_pVertexShader == pShader){
			this->m_pVertexShader.Reset();
			this->UnbindAllStreams();
		}
		if(this->m_pFragmentShader == pShader){
			this->m_pFragmentShader.Reset();
		}
		Manage::IObjectManager<COGLDevice, IOGLBaseShader>::RemoveObject(pShader);
	}

	void	COGLDevice::RemoveObject(CPtr<IOGLBaseState> pState){
		if(this->m_pRasterizerState == pState){
			this->FreeState(Graphic::DeviceStateType::Rasterizer);
		}
		if(this->m_pDepthStencilState == pState){
			this->FreeState(Graphic::DeviceStateType::DepthStencil);
		}
		if(this->m_pBlendState == pState){
			this->FreeState(Graphic::DeviceStateType::Blend);
		}
		Manage::IObjectManager<COGLDevice, IOGLBaseState>::RemoveObject(pState);
	}

	void	COGLDevice::RemoveObject(CPtr<IOGLBaseTexture> pTexture){
		for(uint32 uIndex = 0; uIndex < Manage::IObjectManager<COGLDevice, IOGLBaseShader>::m_pObjectList.GetLength(); uIndex++){
			Manage::IObjectManager<COGLDevice, IOGLBaseShader>::m_pObjectList[uIndex]->RemoveSampler(pTexture);
		}
		Manage::IObjectManager<COGLDevice, IOGLBaseTexture>::RemoveObject(pTexture);
	}

	void	COGLDevice::RemoveObject(CPtr<COGLVertexDeclaration> pDeclaration){
		if(this->m_pVertexDeclaration == pDeclaration){
			this->FreeVertexDeclaration();
		}
		Manage::IObjectManager<COGLDevice, COGLVertexDeclaration>::RemoveObject(pDeclaration);
	}

	//	END OF OVERRIDES	==================================================================

	//	INTERFACE IMPLEMENTATION	==========================================================

	const uint32	COGLDevice::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IAdapter>	COGLDevice::GetAdapter() const{
		return this->m_pParent.Cast<Graphic::IAdapter>();
	}

	CRefPtr<Graphic::IOutput>	COGLDevice::GetOutput() const{
		return this->m_pOutput.Cast<Graphic::IOutput>();
	}

	CRefPtr<Window::IWindow>	COGLDevice::GetOutputWindow() const{
		return this->m_pOutputWindow;
	}

	void	COGLDevice::SetOutputWindow(CRefPtr<Window::IWindow> pWindow){
		this->m_pRenderContext->Unbind();
		this->m_pOutput->AdjustWindowRect(pWindow);
		this->m_pOutputWindow = pWindow;

		auto pixelFormat = this->m_WindowDC.GetPixelFormat();
		this->m_WindowDC.SetWindow(this->m_pOutputWindow);
		if(this->m_WindowDC.GetPixelFormat() != pixelFormat){
			this->m_WindowDC.SetPixelFormat(pixelFormat);
		}

		this->m_pRenderContext->Bind(this->m_WindowDC);
	}



	CRefPtr<Graphic::IVertexDeclaration>	COGLDevice::CreateVertexDeclaration(CRefPtr<Graphic::IShader> pVertexShader, const Collection::ICountable<Graphic::CVertexElement>& Elements){
		CR_APICHECK(this, pVertexShader);

		if(pVertexShader->GetType() != Graphic::ShaderType::Vertex){
			throw Exception::CInvalidArgumentException(L"pVertexShader", String::ToString(pVertexShader->GetType()),
				L"Invalid shader type.", CR_INFO());
		}

		return new COGLVertexDeclaration(this, Elements);
	}

	CRefPtr<Graphic::IBuffer>	COGLDevice::CreateBuffer(const Graphic::BufferType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength){
		return this->CreateBuffer(uType, uUsage, uAccess, uLength, 0);
	}

	CRefPtr<Graphic::IBuffer>	COGLDevice::CreateBuffer(const Graphic::BufferType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength, const void* pData){
		switch (uType)
		{
		case Graphic::BufferType::Vertex:	return new COGLVertexBuffer(this, uUsage, uAccess, uLength, pData);
		case Graphic::BufferType::Index:	return new COGLIndexBuffer(this, uUsage, uAccess, uLength, pData);

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Unknown buffer type.", CR_INFO());
		}
	}

	CRefPtr<Graphic::ITexture2D>	COGLDevice::CreateTexture2D(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat){
		return this->CreateTexture2D(Size, uUsage, uAccess, uFormat, Graphic::BufferFormat::Unknown, 0, 0);
	}

	CRefPtr<Graphic::ITexture2D>	COGLDevice::CreateTexture2D(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat, const Graphic::BufferFormat uInputFormat, const uint32 uLength, const void* pData){
		return new COGLTexture2D(this, Size, uAccess, uUsage, uFormat, uInputFormat, pData);
	}

	CRefPtr<Graphic::IRasterizerState>	COGLDevice::CreateState(const Graphic::CRasterizerStateDesc& Desc){
		return new COGLRasterizerState(this, Desc);
	}

	CRefPtr<Graphic::IBlendState>	COGLDevice::CreateState(const Graphic::CBlendStateDesc& Desc){
		return new COGLBlendState(this, Desc);
	}

	CRefPtr<Graphic::IDepthStencilState>	COGLDevice::CreateState(const Graphic::CDepthStencilStateDesc& Desc){
		return new COGLDepthStencilState(this, Desc);
	}



	CRefPtr<Graphic::IShader>	COGLDevice::Compile(const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, const CString& strSource){
		return this->Compile(uType, uVersion, strSource, L"main");
	}

	CRefPtr<Graphic::IShader>	COGLDevice::Compile(const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint){
		switch (uType)
		{
		case Graphic::ShaderType::Vertex:	return new COGLVertexShader(this, uVersion, strSource, strEntryPoint);
		case Graphic::ShaderType::Fragment:	return new COGLFragmentShader(this, uVersion, strSource, strEntryPoint);
			
		case Graphic::ShaderType::Geometry:	CR_THROWNOTIMPLEMENTED();

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Invalid shader type.", CR_INFO());
		}
	}



	void	COGLDevice::SetVertexDeclaration(CRefPtr<Graphic::IVertexDeclaration> pDeclaration){
		CR_APICHECK(this, pDeclaration);

		auto pOGLDeclaration = pDeclaration.Cast<COGLVertexDeclaration>();

		this->FreeVertexDeclaration();
		this->m_pVertexDeclaration = pOGLDeclaration;

		this->BindAllStreams();
	}

	void	COGLDevice::SetIndexBuffer(CRefPtr<Graphic::IBuffer> pBuffer){
		CR_APICHECK(this, pBuffer);

		if(pBuffer->GetType() != Graphic::BufferType::Index){
			throw Exception::CInvalidArgumentException(L"pBuffer", String::ToString(pBuffer->GetType()),
				L"Invalid buffer type for index buffer.", CR_INFO());
		}

		this->m_pIndexStream = pBuffer.GetCast<COGLIndexBuffer>();
	}

	void	COGLDevice::SetVertexBuffer(const uint32 uStream, CRefPtr<Graphic::IBuffer> pBuffer){
		CR_APICHECK(this, pBuffer);

		if(pBuffer->GetType() != Graphic::BufferType::Vertex){
			throw Exception::CInvalidArgumentException(L"pBuffer", String::ToString(pBuffer->GetType()),
				L"Invalid buffer type for vertex buffer.", CR_INFO());
		}

		this->FreeVertexBuffer(uStream);
		this->m_pVertexStream[uStream] = pBuffer.GetCast<COGLVertexBuffer>();
		this->BindStream(uStream);
	}

	void	COGLDevice::SetShader(CRefPtr<Graphic::IShader> pShader){
		CR_APICHECK(this, pShader);

		auto pOGLShader = pShader.Cast<IOGLBaseShader>();

		this->FreeShader(pOGLShader->GetType());
		pOGLShader->Bind();
		pOGLShader->BindSamplers();
		switch (pOGLShader->GetType()){
		case Graphic::ShaderType::Vertex:	
			this->m_pVertexShader = pOGLShader;		
			this->BindAllStreams();
			break;

		case Graphic::ShaderType::Fragment:	
			this->m_pFragmentShader = pOGLShader;	
			break;

		default:
			throw Exception::CInvalidVarValueException(L"pOGLShader->GetType()", String::ToString(pOGLShader->GetType()),
				L"Invalid shader type.", CR_INFO());
		}
	}

	void	COGLDevice::SetState(CRefPtr<Graphic::IDeviceState> pState){
		CR_APICHECK(this, pState);
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		switch (pState->GetType())
		{
		case Graphic::DeviceStateType::Rasterizer:	
			this->m_pRasterizerState = pState.Cast<IOGLBaseState>();
			this->SetGLState(this->m_pRasterizerState.GetCast<COGLRasterizerState>()->GetDesc());
			break;

		case Graphic::DeviceStateType::Blend:
			this->m_pBlendState = pState.Cast<IOGLBaseState>();
			this->SetGLState(this->m_pBlendState.GetCast<COGLBlendState>()->GetDesc());
			break;

		case Graphic::DeviceStateType::DepthStencil:
			this->m_pDepthStencilState = pState.Cast<IOGLBaseState>();
			this->SetGLState(this->m_pDepthStencilState.GetCast<COGLDepthStencilState>()->GetDesc());
			break;

		default:
			throw Exception::CInvalidArgumentException(L"pState->GetType()", String::ToString(pState->GetType()),
				L"Unknown device state type.", CR_INFO());
		}
	}

	void	COGLDevice::SetState(CRefPtr<Graphic::IBlendState> pState, const Math::CColor& BlendFactor, const uint32 uSampleMask){
		CR_APICHECK(this, pState);
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		this->m_BlendFactor = BlendFactor;
		this->m_uSampleMask = uSampleMask;
		this->m_pBlendState = pState.Cast<IOGLBaseState>();
		this->SetGLState(this->m_pBlendState.GetCast<COGLBlendState>()->GetDesc());
	}

	void	COGLDevice::SetState(CRefPtr<Graphic::IDepthStencilState> pState, const uint32 uStencilRef){
		CR_APICHECK(this, pState);
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		this->m_uStencilRef = uStencilRef;
		this->m_pDepthStencilState = pState.Cast<IOGLBaseState>();
		this->SetGLState(this->m_pDepthStencilState.GetCast<COGLDepthStencilState>()->GetDesc());
	}

	void	COGLDevice::SetRenderPrimitive(const Graphic::PrimitiveType uType){
		switch (uType){
		case Graphic::PrimitiveType::Points:	this->m_uPrimitiveMode = GL::GL_POINTS;	break;
		case Graphic::PrimitiveType::Lines:		this->m_uPrimitiveMode = GL::GL_LINES;	break;
		case Graphic::PrimitiveType::Triangles:	this->m_uPrimitiveMode = GL::GL_TRIANGLES;	break;
		default:
			throw Exception::CInvalidArgumentException(L"uType", String::FromUInt32((uint32)uType),
				L"Unknown primitive type.", CR_INFO());
		}
	}

	void	COGLDevice::SetScissorRect(const Math::CRectangle& Rect){
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		this->GetRC().glScissor(Rect.Position.X, Rect.Position.Y, Rect.Size.Width, Rect.Size.Height);	CR_GLCHECK();
	}
	
	void	COGLDevice::SetViewport(const Math::CRectangle& Viewport){
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		this->GetRC().glViewport(Viewport.Position.X, Viewport.Position.Y, Viewport.Size.Width, Viewport.Size.Height);	CR_GLCHECK();
	}


	CRefPtr<Graphic::IVertexDeclaration>	COGLDevice::GetVertexDeclaration() const{
		return this->m_pVertexDeclaration.Get();
	}

	CRefPtr<Graphic::IBuffer>	COGLDevice::GetIndexBuffer() const{
		if(this->m_pIndexStream.IsValid())
			return this->m_pIndexStream.GetCast<Graphic::IBuffer>();
		return CRefPtr<Graphic::IBuffer>();
	}

	CRefPtr<Graphic::IBuffer>	COGLDevice::GetVertexBuffer(const uint32 uStream) const{
		auto& pBuffer = this->m_pVertexStream[uStream];
		if(pBuffer.IsValid())
			return pBuffer.GetCast<Graphic::IBuffer>();
		return CRefPtr<Graphic::IBuffer>();
	}

	CRefPtr<Graphic::IShader>	COGLDevice::GetShader(const Graphic::ShaderType uType) const{
		CB::CPtr<IOGLBaseShader> pShader;
		switch (uType)
		{
		case Graphic::ShaderType::Vertex:	pShader = this->m_pVertexShader; break;
		case Graphic::ShaderType::Fragment:	pShader = this->m_pFragmentShader; break;
		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Invalid shader type.", CR_INFO());
		}
		if(pShader.IsValid())
			return pShader.Get();
		return CRefPtr<Graphic::IShader>();
	}

	CRefPtr<Graphic::IDeviceState>	COGLDevice::GetState(const Graphic::DeviceStateType uType) const{
		switch (uType)
		{
		case Graphic::DeviceStateType::Blend:
			if(this->m_pBlendState.IsNull())
				return new COGLBlendState(this, Graphic::CBlendStateDesc());
			else
				return this->m_pBlendState.Get();
			break;

		case Graphic::DeviceStateType::DepthStencil:
			if(this->m_pDepthStencilState.IsNull())
				return new COGLDepthStencilState(this, Graphic::CDepthStencilStateDesc());
			else
				return this->m_pDepthStencilState.Get();
			break;

		case Graphic::DeviceStateType::Rasterizer:
			if(this->m_pRasterizerState.IsNull())
				return new COGLRasterizerState(this, Graphic::CRasterizerStateDesc());
			else
				return this->m_pRasterizerState.Get();
			break;

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Unknown state type.", CR_INFO());
		}
	}



	//=======================================================================================================
	//	INFO GETTERS
	//=======================================================================================================

	const Graphic::PrimitiveType	COGLDevice::GetRenderPrimitive() const{
		switch (this->m_uPrimitiveMode)
		{
		case GL::GL_POINTS:		return Graphic::PrimitiveType::Points;
		case GL::GL_LINES:		return Graphic::PrimitiveType::Lines;
		case GL::GL_TRIANGLES:	return Graphic::PrimitiveType::Triangles;
		default:
			throw Exception::CInvalidVarValueException(L"m_uPrimitiveType", String::ToString(this->m_uPrimitiveMode),
				L"Unimplemented primitive type.", CR_INFO());
		}
	}

	const Graphic::FeatureLevel	COGLDevice::GetFeatureLevel() const{
		return this->m_uFeatureLevel;
	}

	const CString	COGLDevice::GetLastCompilationLog() const{
		const char* szLog = cgGetLastListing(this->GetCGC().Get());
		if(szLog == 0){
			return CString();
		}
		return String::FromANSI(reinterpret_cast<const int8*>(szLog));
	}

	const uint32	COGLDevice::GetNumberOfStreams() const{
		return 16;
	}

	const Math::CRectangle	COGLDevice::GetScissorRect() const{
		return this->m_ScissorRect;
	}

	const Math::CRectangle	COGLDevice::GetViewport() const{
		return this->m_Viewport;
	}

	const uint32	COGLDevice::GetMaxAnisotropy() const{
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		GLint val = 0;
		this->GetRC().glGetIntegerv(GL::GL_MAX_TEXTURE_MAX_ANISOTROPY, &val);	CR_GLCHECK();
		return (uint32)val;
	}

	const uint32	COGLDevice::GetMaxTextureSize(const Graphic::TextureType uType) const{
		GLint val = 0;
		CGLRenderContext& GL(this->GetRC());

		switch (uType){
		case Graphic::TextureType::Texture1D:	
		case Graphic::TextureType::Texture2D:
			GL.glGetIntegerv(GL::GL_MAX_TEXTURE_SIZE, &val);	
			break;

		case Graphic::TextureType::Texture3D:
			GL.glGetIntegerv(GL::GL_MAX_3D_TEXTURE_SIZE, &val);
			break;

		case Graphic::TextureType::TextureCube:
			GL.glGetIntegerv(GL::GL_MAX_CUBE_MAP_TEXTURE_SIZE, &val);
			break;

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Invalid texture type for size query.", CR_INFO());
		}

		return (uint32)val;
	}

	//=======================================================================================================
	//	END OF INFO GETTERS
	//=======================================================================================================



	//=======================================================================================================
	//	OBJECT FREEING
	//=======================================================================================================

	void	COGLDevice::FreeVertexDeclaration(){
		this->UnbindAllStreams();
		this->m_pVertexDeclaration.Reset();
	}

	void	COGLDevice::FreeIndexBuffer(){
		this->m_pIndexStream.Reset();
	}

	void	COGLDevice::FreeVertexBuffer(const uint32 uStream){
		if(this->m_pVertexStream[uStream].IsValid()){
			this->UnbindStream(uStream);
			this->m_pVertexStream[uStream].Reset();
		}
	}

	void	COGLDevice::FreeShader(const Graphic::ShaderType uType){
		switch (uType){
		case Graphic::ShaderType::Vertex:
			this->UnbindAllStreams();
			if(this->m_pVertexShader.IsValid()){
				this->m_pVertexShader->UnbindSamplers();
				this->m_pVertexShader->Unbind();
			}
			this->m_pVertexShader.Reset();
			break;

		case Graphic::ShaderType::Fragment:
			if(this->m_pFragmentShader.IsValid()){
				this->m_pFragmentShader->UnbindSamplers();
				this->m_pFragmentShader->Unbind();
			}
			this->m_pFragmentShader.Reset();
			break;

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Invalid shader type.", CR_INFO());
		}
	}

	void	COGLDevice::FreeState(const Graphic::DeviceStateType uType){
		switch (uType)
		{
		case Graphic::DeviceStateType::Blend:
			this->m_pBlendState.Reset();
			this->SetGLState(Graphic::CBlendStateDesc());
			break;

		case Graphic::DeviceStateType::DepthStencil:
			this->m_pDepthStencilState.Reset();
			this->SetGLState(Graphic::CDepthStencilStateDesc());
			break;

		case Graphic::DeviceStateType::Rasterizer:
			this->m_pRasterizerState.Reset();
			this->SetGLState(Graphic::CRasterizerStateDesc());
			break;

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Unknown state type for clearing.", CR_INFO());
		}
	}

	//=================================================================================================
	//	END OF OBJECT FREEING
	//=================================================================================================



	void	COGLDevice::Render(const uint32 uPrimitiveCount){
		this->Render(uPrimitiveCount, 0);
	}

	void	COGLDevice::Render(const uint32 uPrimitiveCount, const uint32 uStartVertex){
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		uint32 uVertexCount = 0;
		switch (this->m_uPrimitiveMode)
		{
		case GL::GL_POINTS:		uVertexCount = uPrimitiveCount;	break;
		case GL::GL_LINES:		uVertexCount = uPrimitiveCount * 2; break;
		case GL::GL_TRIANGLES:	uVertexCount = uPrimitiveCount * 3; break;
		default:
			throw Exception::CInvalidVarValueException(L"m_uPrimitiveMode", String::FromUInt32(this->m_uPrimitiveMode),
				L"Unknown primitive mode.", CR_INFO());
		}

		GetRC().glDrawArrays(this->m_uPrimitiveMode, uStartVertex, uVertexCount);	CR_GLCHECK();
	}
	
	void	COGLDevice::RenderIndexed(const uint32 uPrimitiveCount){
		this->RenderIndexed(uPrimitiveCount, 0, 0);
	}

	void	COGLDevice::RenderIndexed(const uint32 uPrimitiveCount, const uint32 uStartVertex){
		this->RenderIndexed(uPrimitiveCount, uStartVertex, 0);
	}

	void	COGLDevice::RenderIndexed(const uint32 uPrimitiveCount, const uint32 uStartVertex, const uint32 uStartIndex){
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());

		if(this->m_pIndexStream.IsNull()){
			CR_THROW(L"Index buffer not set.");
		}

		uint32 uVertexCount = 0;
		switch (this->m_uPrimitiveMode)
		{
		case GL::GL_POINTS:		uVertexCount = uPrimitiveCount;	break;
		case GL::GL_LINES:		uVertexCount = uPrimitiveCount * 2; break;
		case GL::GL_TRIANGLES:	uVertexCount = uPrimitiveCount * 3; break;
		}

		this->m_pIndexStream->Bind();
		GetRC().glDrawRangeElements(this->m_uPrimitiveMode, uStartVertex, uStartVertex + uVertexCount, uVertexCount, GL::GL_UNSIGNED_SHORT, reinterpret_cast<const void*>(uStartIndex));
		this->m_pIndexStream->Unbind();
	}

	void	COGLDevice::RenderInstanced(const uint32 uInstanceCount, const uint32 uPrimitiveCount){
		this->RenderInstanced(uInstanceCount, uPrimitiveCount, 0);
	}

	void	COGLDevice::RenderInstanced(const uint32 uInstanceCount, const uint32 uPrimitiveCount, const uint32 uStartVertex){
		//if(this->m_pCurrentDeclaration.IsNull()){
		//	throw Exception::CNullPointerException(L"m_pCurrentDeclaration", 
		//		L"Vertex declaration must be set for instanced rendering.", CR_INFO());
		//}
		//
		//HRESULT hResult = S_OK;

		//for(uint32 uIndex = 0; uIndex < this->m_pVertexBufferList.GetLength(); uIndex++){
		//	if(this->m_pVertexBufferList[uIndex].IsValid()){
		//		switch (this->m_pCurrentDeclaration->GetInstanceData()[uIndex])
		//		{
		//		case Graphic::InstanceDataType::PerVertexData:
		//			hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, uInstanceCount);
		//			break;

		//		case Graphic::InstanceDataType::PerInstanceData:
		//			hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, 1);
		//			break;
		//		}

		//		if(hResult != S_OK){
		//			throw Exception::CCOMException(hResult,
		//				L"Failed to set instance number for stream " + String::FromUInt32(uIndex) + L".", CR_INFO());
		//		}
		//	}
		//}
		//try{
		//	this->Render(uPrimitiveCount, uStartVertex);
		//}
		//catch(Exception::CException& Exception){
		//	throw Exception::CException(
		//		L"Failed to render instanced data.", CR_INFO(), Exception);
		//}

		//for(uint32 uIndex = 0; uIndex < this->m_pVertexBufferList.GetLength(); uIndex++){
		//	if(this->m_pVertexBufferList[uIndex].IsValid()){
		//		hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, 1);
		//		if(hResult != S_OK){
		//			throw Exception::CCOMException(hResult,
		//				L"Failed to free instance number for stream " + String::FromUInt32(uIndex) + L".", CR_INFO());
		//		}
		//	}
		//}
		CR_THROWNOTIMPLEMENTED();
	}
	
	void	COGLDevice::RenderInstancedIndexed(const uint32 uInstanceCount, const uint32 uPrimitiveCount){
		this->RenderInstancedIndexed(uInstanceCount, uPrimitiveCount, 0, 0);
	}

	void	COGLDevice::RenderInstancedIndexed(const uint32 uInstanceCount, const uint32 uPrimitiveCount, const uint32 uStartVertex){
		this->RenderInstancedIndexed(uInstanceCount, uPrimitiveCount, uStartVertex, 0);
	}

	void	COGLDevice::RenderInstancedIndexed(const uint32 uInstanceCount, const uint32 uPrimitiveCount, const uint32 uStartVertex, const uint32 uStartIndex){
		//if(this->m_pCurrentDeclaration.IsNull()){
		//	throw Exception::CNullPointerException(L"m_pCurrentDeclaration", 
		//		L"Vertex declaration must be set for instanced rendering.", CR_INFO());
		//}
		//
		//HRESULT hResult = S_OK;

		//for(uint32 uIndex = 0; uIndex < this->m_pVertexBufferList.GetLength(); uIndex++){
		//	if(this->m_pVertexBufferList[uIndex].IsValid()){
		//		switch (this->m_pCurrentDeclaration->GetInstanceData()[uIndex])
		//		{
		//		case Graphic::InstanceDataType::PerVertexData:
		//			hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, (D3DSTREAMSOURCE_INDEXEDDATA | uInstanceCount));
		//			break;

		//		case Graphic::InstanceDataType::PerInstanceData:
		//			hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, (D3DSTREAMSOURCE_INSTANCEDATA | 1));
		//			break;
		//		}

		//		if(hResult != S_OK){
		//			throw Exception::CCOMException(hResult,
		//				L"Failed to set instance number for stream " + String::FromUInt32(uIndex) + L".", CR_INFO());
		//		}
		//	}
		//}
		//try{
		//	this->RenderIndexed(uPrimitiveCount, uStartVertex, uStartIndex);
		//}
		//catch(Exception::CException& Exception){
		//	throw Exception::CException(
		//		L"Failed to render instanced data.", CR_INFO(), Exception);
		//}

		//for(uint32 uIndex = 0; uIndex < this->m_pVertexBufferList.GetLength(); uIndex++){
		//	if(this->m_pVertexBufferList[uIndex].IsValid()){
		//		hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, 1);
		//		if(hResult != S_OK){
		//			throw Exception::CCOMException(hResult,
		//				L"Failed to free instance number for stream " + String::FromUInt32(uIndex) + L".", CR_INFO());
		//		}
		//	}
		//}
		CR_THROWNOTIMPLEMENTED();
	}


	void	COGLDevice::BeginRender(){

	}

	void	COGLDevice::EndRender(){

	}


	void	COGLDevice::Clear(const Math::CColor& Color){
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());
		CGLRenderContext& GL(GetRC());
		
		GL.glClearColor(Color.Red, Color.Green, Color.Blue, Color.Alpha);	CR_GLCHECK();
		GL.glClear(GL::GL_COLOR_BUFFER_BIT);	CR_GLCHECK();
	}

	void	COGLDevice::Clear(const float fZDepth, const uint32 uStencil){
		CR_GLBINDCHECK(this->GetDC(), this->GetRC());
		CGLRenderContext& GL(GetRC());

		GL.glClearDepth(fZDepth);		CR_GLCHECK();
		GL.glClearStencil(uStencil);	CR_GLCHECK();
		GL.glClear(GL::GL_DEPTH_BUFFER_BIT | GL::GL_STENCIL_BUFFER_BIT);	CR_GLCHECK();
	}

	void	COGLDevice::Swap(){
		this->m_WindowDC.SwapBuffers();
	}

	//	END OF IMPLEMENTATION	===================================================================

	void	COGLDevice::BindStream(const uint32 uStream){
		if(this->m_pVertexDeclaration.IsNull()){
			return;
		}
		if(this->m_pVertexStream[uStream].IsNull()){
			return;
		}
		if(this->m_pVertexShader.IsNull()){
			return;
		}

		const CStreamDefinition& stream = this->m_pVertexDeclaration->GetStream(uStream);

		this->m_pVertexStream[uStream]->Bind();
		for(uint32 uIndex = 0; uIndex < stream.Elements.GetLength(); uIndex++){
			const CStreamElement& element = stream.Elements[uIndex];

			this->m_pVertexShader->BindParameter(element.strParamName, element.uType, element.uNumber, stream.uStride, element.uOffset);
		}
	}

	void	COGLDevice::BindAllStreams(){
		for(uint32 uIndex = 0; uIndex < this->GetNumberOfStreams(); uIndex++){
			this->BindStream(uIndex);
		}
	}

	void	COGLDevice::UnbindStream(const uint32 uStream){
		if(this->m_pVertexStream[uStream].IsValid()){
			this->m_pVertexStream[uStream]->Unbind();
		}

		if(this->m_pVertexShader.IsValid() && this->m_pVertexDeclaration.IsValid()){
			const CStreamDefinition& stream = this->m_pVertexDeclaration->GetStream(uStream);
			for(uint32 uIndex = 0; uIndex < stream.Elements.GetLength(); uIndex++){
				const CStreamElement& element = stream.Elements[uIndex];

				this->m_pVertexShader->UnbindParameter(element.strParamName);
			}
		}
	}

	void	COGLDevice::UnbindAllStreams(){
		for(uint32 uIndex = 0; uIndex < this->GetNumberOfStreams(); uIndex++){
			if(this->m_pVertexStream[uIndex].IsValid()){
				this->m_pVertexStream[uIndex]->Unbind();
			}
		}
		if(this->m_pVertexShader.IsValid()){
			this->m_pVertexShader->UnbindParameters();
		}
	}

	const bool	COGLDevice::LoadFeatureLevel(CGLRenderContext& tempRC,const Graphic::FeatureLevel uLevel, const bool bCoreCreate){
		CRCBindGuard bind;	//	current device and render context guard.

		switch (uLevel)
		{
		case Graphic::FeatureLevel::Level_1:
			if(!this->CreateRenderContext(tempRC, GLVersion::V_1_4, bCoreCreate))
				return false;

			this->m_pRenderContext->Bind(this->m_WindowDC);

			if(!this->m_pRenderContext->Load(GLVersion::V_1_2))
				return false;
			if(!this->m_pRenderContext->Load(GLVersion::V_1_3))
				return false;
			if(!this->m_pRenderContext->Load(GLVersion::V_1_4))
				return false;
			if(!this->m_pRenderContext->Load(GLExtension::VertexBufferObjects))
				return false;
			if(!this->m_pRenderContext->Load(GLExtension::AnisotropicFiltering))
				return false;
			if(!this->m_pRenderContext->Load(GLExtension::MipMapGeneration))
				return false;
			if(!this->m_pRenderContext->Load(GLExtension::StencilTwoSide))
				return false;
			if(!this->m_pRenderContext->Load(WGLExtension::PixelBuffer))
				return false;
			if(!this->m_pRenderContext->Load(WGLExtension::MakeCurrentRead))
				return false;

			return true;

		case Graphic::FeatureLevel::Level_2:
			CR_THROWNOTIMPLEMENTED();
			return true;

		case Graphic::FeatureLevel::Level_3:
			if(!bCoreCreate){
				return false;
			}

			CR_THROWNOTIMPLEMENTED();
			return true;

		case Graphic::FeatureLevel::Level_4:
			if(!bCoreCreate){
				return false;
			}

			CR_THROWNOTIMPLEMENTED();
			return true;

		default:
			return false;
		}
	}

	const bool	COGLDevice::CreateRenderContext(CGLRenderContext& tempRC, const GLVersion uVersion, const bool bCoreCreate){
		uint32 uMaj = 0;
		uint32 uMin = 0;
		switch (uVersion)
		{
		case GLVersion::V_1_2:	uMaj = 1, uMin = 2; break;
		case GLVersion::V_1_3:	uMaj = 1, uMin = 3; break;
		case GLVersion::V_1_4:	uMaj = 1, uMin = 4; break;
		case GLVersion::V_1_5:	uMaj = 1, uMin = 5; break;
		case GLVersion::V_2_0:	uMaj = 2, uMin = 0; break;
		case GLVersion::V_2_1:	uMaj = 2, uMin = 1; break;
		case GLVersion::V_3_0:	uMaj = 3, uMin = 0; break;
		case GLVersion::V_3_1:	uMaj = 3, uMin = 1; break;
		case GLVersion::V_3_2:	uMaj = 3, uMin = 2; break;
		case GLVersion::V_3_3:	uMaj = 3, uMin = 3; break;
		default:
			uMaj = 1, uMin = 1;
		}

		if(bCoreCreate){
			Collection::CList<int32> attribs;

			attribs.Add(WGL::WGL_CONTEXT_MAJOR_VERSION);
			attribs.Add(uMaj);

			attribs.Add(WGL::WGL_CONTEXT_MINOR_VERSION);
			attribs.Add(uMin);

			if(tempRC.IsSupported(WGLExtension::CreateContextProfile) && uMaj >= 3 && uMin >= 0){
				attribs.Add(WGL::WGL_CONTEXT_PROFILE_MASK);
				attribs.Add(WGL::WGL_CONTEXT_CORE_PROFILE_BIT);
			}

			this->m_pRenderContext = new CGLRenderContext(this->m_WindowDC, attribs);
			return true;
		}
		else{
			this->m_pRenderContext = new CGLRenderContext(this->m_WindowDC);
		}
		return this->m_pRenderContext->IsSupported(uVersion);
	}

	void	COGLDevice::SetGLState(const Graphic::CRasterizerStateDesc& Desc){
		CGLRenderContext& GL(GetRC());

		if(Desc.bFrontCounterClockWise){
			GL.glFrontFace(GL::GL_CCW);	CR_GLCHECK();
		}
		else{
			GL.glFrontFace(GL::GL_CW);		CR_GLCHECK();
		}

		if(Desc.uCullMode != Graphic::CullMode::None){
			GL.glEnable(GL::GL_CULL_FACE);	CR_GLCHECK();
			switch (Desc.uCullMode)
			{
			case Graphic::CullMode::Front:	
				GL.glCullFace(GL::GL_FRONT);	CR_GLCHECK();	
				break;

			case Graphic::CullMode::Back:
				GL.glCullFace(GL::GL_BACK);	CR_GLCHECK();
				break;

			default:
				throw Exception::CInvalidVarValueException(L"Desc.uCullMode", String::ToString(Desc.uCullMode),
					L"Unknown culling mode.", CR_INFO());
			}
		}
		else{
			GL.glDisable(GL::GL_CULL_FACE);	CR_GLCHECK();
		}
		
		switch (Desc.uFillMode)
		{
		case Graphic::FillMode::Solid:	
			GL.glPolygonMode(GL::GL_FRONT_AND_BACK, GL::GL_FILL);	CR_GLCHECK();
			break;

		case Graphic::FillMode::WireFrame:
			GL.glPolygonMode(GL::GL_FRONT_AND_BACK, GL::GL_LINE);	CR_GLCHECK();

		default:
			throw Exception::CInvalidArgumentException(L"Desc.uFillMode", String::ToString(Desc.uFillMode),
				L"Unknown fill mode.", CR_INFO());
		}

		if(Desc.bScissorEnabled){
			GL.glEnable(GL::GL_SCISSOR_TEST);	CR_GLCHECK();
		}
		else{
			GL.glDisable(GL::GL_SCISSOR_TEST);	CR_GLCHECK();
		}
	}

	void	COGLDevice::SetGLState(const Graphic::CDepthStencilStateDesc& Desc){
		CGLRenderContext& GL(GetRC());

		if(Desc.bDepthTestEnabled){
			GL.glEnable(GL::GL_DEPTH_TEST);	CR_GLCHECK();
		}
		else{
			GL.glDisable(GL::GL_DEPTH_TEST);	CR_GLCHECK();
		}

		GL.glDepthMask(Desc.bDepthWrite);
		GL.glDepthFunc(GLUtils::ToCompareFunc(Desc.uDepthFunction));	CR_GLCHECK();

		if(GL.IsSupported(GLExtension::StencilTwoSide)){
			if(Desc.bStencilTestEnabled){
				GL.glEnable(GL::GL_STENCIL_TEST_TWO_SIDE);	CR_GLCHECK();
				this->SetGLStateStencilFace(Desc, Desc.StencilFront, GL::GL_FRONT);
				this->SetGLStateStencilFace(Desc, Desc.StencilBack, GL::GL_BACK);
			}
			else{
				GL.glDisable(GL::GL_STENCIL_TEST_TWO_SIDE);	CR_GLCHECK();
			}
		}
	}

	void	COGLDevice::SetGLState(const Graphic::CBlendStateDesc& Desc){
		CGLRenderContext& GL(GetRC());

		if(Desc.bEnabled[0]){
			GL.glEnable(GL::GL_BLEND);		CR_GLCHECK();
		}
		else{
			GL.glDisable(GL::GL_BLEND);	CR_GLCHECK();
		}

		GL.glBlendColor(this->m_BlendFactor.Red, this->m_BlendFactor.Green, this->m_BlendFactor.Blue, this->m_BlendFactor.Alpha);	CR_GLCHECK();

		GL.glBlendEquation(GLUtils::ToBlendEquation(Desc.ColorBlend.uOperation));	CR_GLCHECK();
		GL.glBlendFuncSeparate(
			GLUtils::ToBlendOption(Desc.ColorBlend.uSourceOperand), GLUtils::ToBlendOption(Desc.ColorBlend.uDestOperand),
			GLUtils::ToBlendOption(Desc.AlphaBlend.uSourceOperand), GLUtils::ToBlendOption(Desc.AlphaBlend.uDestOperand)
			);	CR_GLCHECK();

		auto bR = (Desc.uWriteMask[0] & 0x1) > 0;
		auto bG = (Desc.uWriteMask[0] & 0x2) > 0;
		auto bB = (Desc.uWriteMask[0] & 0x4) > 0;
		auto bA = (Desc.uWriteMask[0] & 0x8) > 0;

		GL.glColorMask(bR, bG, bB, bA);	CR_GLCHECK();
	}

	void	COGLDevice::SetGLStateStencilFace(const Graphic::CDepthStencilStateDesc& StencilDesc, const Graphic::CStencilInstDesc& Desc, const GLenum uFace){
		CGLRenderContext& GL(GetRC());

		if(GL.IsSupported(GLExtension::StencilTwoSide)){
			GL.glActiveStencilFace(uFace);	CR_GLCHECK();

			GL.glStencilFunc(GLUtils::ToCompareFunc(Desc.uStencilFunc), this->m_uStencilRef, StencilDesc.uStencilReadMask);	CR_GLCHECK();
			GL.glStencilOp(GLUtils::ToStencilOp(Desc.uStencilFail), GLUtils::ToStencilOp(Desc.uDepthTestFail), GLUtils::ToStencilOp(Desc.uStencilPass));	CR_GLCHECK();
			GL.glStencilMask(StencilDesc.uStencilWriteMask);	CR_GLCHECK();
		}
	}
}