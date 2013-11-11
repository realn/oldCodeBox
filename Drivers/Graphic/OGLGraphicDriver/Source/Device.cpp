#include "../Internal/Device.h"
#include <CBStringEx.h>

#include "../Internal/VertexBuffer.h"
#include "../Internal/IndexBuffer.h"
#include "../Internal/VertexShader.h"
#include "../Internal/FragmentShader.h"
#include "../Internal/VertexDeclaration.h"
#include "../Internal/Utils.h"

#include "../Internal/OpenGL_WGL.h"

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

	COGLDevice::COGLDevice(CRefPtr<COGLAdapter> pAdapter, CRefPtr<Window::IWindow> pWindow, Graphic::CDeviceDesc& Desc, CRefPtr<COGLOutput> pOutput) :
		m_pOutputWindow(pWindow),
		m_pOutput(pOutput),
		m_uPrimitiveMode(GL::GL_TRIANGLES),
		Manage::IManagedObject<COGLAdapter, COGLDevice>(pAdapter)
	{
		Log::Write(L"OpenGL Device initialization...");

		if(Desc.bFullScreen){
			m_pOutput->SetCurrentMode(Desc.BackBuffer);
		}

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
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

		int iPixelFormat = ChoosePixelFormat(tempWinDC.Get(), &pfd);
		if(iPixelFormat == 0){
			CR_THROWWIN(GetLastError(), L"Failed to choose temp pixel format.");
		}

		if(!SetPixelFormat(tempWinDC.Get(), iPixelFormat, &pfd)){
			CR_THROWWIN(GetLastError(), L"Failed to set temp pixel format to temp window.");
		}

		CRenderContext tempRC;
		tempRC.CreateContext(tempWinDC);
		tempRC.Bind(tempWinDC);

		if(!WGL::Loader::Load(WGL::Loader::Extension::ExtensionsString)){
			CR_THROW(L"Failed to load extension string extension (WTF!?).");
		}

		const bool bCoreCreate = WGL::Loader::Load(WGL::Loader::Extension::CreateContext);
		const bool bCorePixelFormat = WGL::Loader::Load(WGL::Loader::Extension::PixelFormat);

		//this->m_DC = pOutput->CreateDeviceContext();
		this->m_WindowDC = this->m_pOutputWindow;

		int iFormat = ChoosePixelFormat(this->m_WindowDC.Get(), &pfd);
		if(iFormat < 1){
			CR_THROWWIN(GetLastError(), L"Failed to choose pixel format.");
		}

		//if(!SetPixelFormat(this->m_DC.Get(), iFormat, &pfd)){
		//	CR_THROWWIN(GetLastError(), L"Failed to set pixel format.");
		//}

		if(!SetPixelFormat(this->m_WindowDC.Get(), iFormat, &pfd)){
			CR_THROWWIN(GetLastError(), L"Failed to set pixel format.");
		}

		this->m_GLRC.CreateContext(this->m_WindowDC);
		this->m_GLRC.Bind(this->m_WindowDC);

		this->m_CGContext = cgCreateContext();
		if(this->m_CGContext == 0){
			CR_THROW(L"Failed to create CG context");
		}

		cgSetErrorCallback(ErrorCallback);

		this->m_pVertexStream.Resize(this->GetNumberOfStreams());

		if(!Load_Version_1_2())
			CR_THROW(L"Failed to load GL version 1.2");
		if(!Load_Version_1_3())
			CR_THROW(L"Failed to load GL version 1.3");
		if(!Load_VertexBufferObjects())
			CR_THROW(L"Failed to load Vertex Buffer Objects GL Extension.");

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
	}

	COGLDevice::~COGLDevice(){
		Log::Write(L"Destroing OpenGL Device...");
		if(this->m_CGContext){
			cgDestroyContext(this->m_CGContext);
			this->m_CGContext = 0;
		}
	}

	HDC	COGLDevice::GetWindowContext() const{
		return this->m_WindowDC.Get();
	}

	HGLRC	COGLDevice::GetRenderContext() const{
		return this->m_GLRC.Get();
	}

	CGcontext	COGLDevice::GetCGContext() const{
		return this->m_CGContext;
	}

	CGprofile	COGLDevice::GetCGProfile(const Graphic::ShaderVersion uVersion, const Graphic::ShaderType uType) const{
		switch (uType)
		{
		case Graphic::ShaderType::Vertex:
			switch (uVersion)
			{
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
			switch (uVersion)
			{
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

	void	COGLDevice::RemoveObject(CPtr<IOGLBaseBuffer> pBuffer){
		switch (pBuffer->GetType())
		{
		case Graphic::BufferType::Index:
			if(this->m_pIndexStream == pBuffer){
				this->FreeIndexBuffer();
			}
			break;

		case Graphic::BufferType::Vertex:
			for(uint32 uStream = 0; uStream < this->m_pVertexStream.GetLength(); uStream++){
				if(this->m_pVertexStream[uStream] == pBuffer){
					this->FreeVertexBuffer(uStream);
				}
			}
			break;

		default:
			throw Exception::CInvalidArgumentException(L"pBuffer", String::ToString(pBuffer->GetType()),
				L"Unknown buffer type for removal.", CR_INFO());
		}
		Manage::IObjectManager<IOGLBaseBuffer>::RemoveObject(pBuffer);
	}

	void	COGLDevice::RemoveObject(CPtr<IOGLBaseShader> pShader){
		switch (pShader->GetType())
		{
		case Graphic::ShaderType::Vertex:
			if(this->m_pVertexShader == pShader){
				this->FreeShader(Graphic::ShaderType::Vertex);
			}
			break;

		case Graphic::ShaderType::Fragment:
			if(this->m_pFragmentShader == pShader){
				this->FreeShader(Graphic::ShaderType::Fragment);
			}
			break;

		default:
			throw Exception::CInvalidArgumentException(L"pShader", String::ToString(pShader->GetType()),
				L"Unknown shader type for removal.", CR_INFO());
		}
		Manage::IObjectManager<IOGLBaseShader>::RemoveObject(pShader);
	}

	void	COGLDevice::RemoveObject(CPtr<COGLVertexDeclaration> pDeclaration){
		if(this->m_pVertexDeclaration == pDeclaration){
			this->FreeVertexDeclaration();
		}
		Manage::IObjectManager<COGLVertexDeclaration>::RemoveObject(pDeclaration);
	}

	//	END OF OVERRIDES	==================================================================

	//	INTERFACE IMPLEMENTATION	==========================================================

	const uint32	COGLDevice::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IAdapter>	COGLDevice::GetAdapter() const{
		return this->m_pParent.Cast<Graphic::IAdapter>();
	}

	CRefPtr<Graphic::IVertexDeclaration>	COGLDevice::CreateVertexDeclaration(CRefPtr<Graphic::IShader> pVertexShader, const Collection::ICountable<Graphic::CVertexElement>& Elements){
		CR_APICHECK(this, pVertexShader);

		if(pVertexShader->GetType() != Graphic::ShaderType::Vertex){
			throw Exception::CInvalidArgumentException(L"pVertexShader", String::ToString(pVertexShader->GetType()),
				L"Invalid shader type.", __FUNCTIONW__, __FILEW__, __LINE__);
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

	CRefPtr<Graphic::ITexture2D>	COGLDevice::CreateTexture(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat){
		return this->CreateTexture(Size, uUsage, uAccess, uFormat, 0, 0);
	}

	CRefPtr<Graphic::ITexture2D>	COGLDevice::CreateTexture(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat, const uint32 uLength, const void* pData){
		//CRefPtr<Graphic::ITexture2D> pTexture = new CDX9Texture2D(this, Size, bDynamic, uFormat);
		//if(pData != 0){
		//	auto pStream = pTexture->Map(false, true, true);
		//	pStream->Write(pData, uDataLength);
		//}
		//return pTexture;
		CR_THROWNOTIMPLEMENTED();
	}

	CRefPtr<Graphic::IRasterizerState>	COGLDevice::CreateState(const Graphic::CRasterizerStateDesc& Desc){
		//return new CDX9RasterizerState(this, Desc);
		CR_THROWNOTIMPLEMENTED();
	}

	CRefPtr<Graphic::IBlendState>	COGLDevice::CreateState(const Graphic::CBlendStateDesc& Desc){
		//return new CDX9BlendState(this, Desc);
		CR_THROWNOTIMPLEMENTED();
	}

	CRefPtr<Graphic::IDepthStencilState>	COGLDevice::CreateState(const Graphic::CDepthStencilStateDesc& Desc){
		//return new CDX9DepthStencilState(this, Desc);
		CR_THROWNOTIMPLEMENTED();
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
				L"Invalid shader type.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	const CString	COGLDevice::GetLastCompilationLog() const{
		const char* szLog = cgGetLastListing(this->m_CGContext);
		if(szLog == 0){
			return CString();
		}
		return String::FromANSI(szLog);
	}

	void	COGLDevice::SetVertexDeclaration(CRefPtr<Graphic::IVertexDeclaration> pDeclaration){
		CR_APICHECK(this, pDeclaration);

		auto pOGLDeclaration = pDeclaration.Cast<COGLVertexDeclaration>();

		this->FreeVertexDeclaration();
		this->m_pVertexDeclaration = pOGLDeclaration;

		this->BindAllStreams();
	}

	void	COGLDevice::FreeVertexDeclaration(){
		this->m_pVertexDeclaration.Reset();
		this->UnbindAllStreams();
	}

	CRefPtr<Graphic::IVertexDeclaration>	COGLDevice::GetVertexDeclaration() const{
		return this->m_pVertexDeclaration.Get();
	}

	void	COGLDevice::SetIndexBuffer(CRefPtr<Graphic::IBuffer> pBuffer){
		CR_APICHECK(this, pBuffer);

		if(pBuffer->GetType() != Graphic::BufferType::Index){
			throw Exception::CInvalidArgumentException(L"pBuffer", String::ToString(pBuffer->GetType()),
				L"Invalid buffer type for index buffer.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		this->m_pIndexStream = pBuffer.GetCast<COGLIndexBuffer>();
	}

	void	COGLDevice::FreeIndexBuffer(){
		this->m_pIndexStream.Reset();
	}

	CRefPtr<Graphic::IBuffer>	COGLDevice::GetIndexBuffer() const{
		//LPDIRECT3DINDEXBUFFER9 pBuffer = 0;
		//HRESULT hResult = this->GetDX()->GetIndices(&pBuffer);
		//if(hResult != S_OK){
		//	throw Exception::CCOMException(hResult,
		//		L"Failed to retrieve current index buffer.", __FUNCTIONW__, __FILEW__, __LINE__);
		//}
		//if(this->m_pIndexBuffer.IsNull() && pBuffer == 0){
		//	return CRefPtr<Graphic::IBuffer>();
		//}

		//if(this->m_pIndexBuffer->GetDX() != pBuffer){
		//	throw Exception::CException(
		//		L"Index buffer mismatch from DX api.", __FUNCTIONW__, __FILEW__, __LINE__);
		//}

		//pBuffer->Release();
		//return this->m_pIndexBuffer.Get();
		CR_THROWNOTIMPLEMENTED();
	}

	void	COGLDevice::SetVertexBuffer(const uint32 uStream, CRefPtr<Graphic::IBuffer> pBuffer){
		CR_APICHECK(this, pBuffer);

		if(this->m_pVertexDeclaration.IsNull()){
			throw Exception::CNullPointerException(L"m_pVertexDeclaration",
				L"Vertex declaration must be set before attaching vertex buffer.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		if(pBuffer->GetType() != Graphic::BufferType::Vertex){
			throw Exception::CInvalidArgumentException(L"pBuffer", String::ToString(pBuffer->GetType()),
				L"Invalid buffer type for vertex buffer.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		this->FreeVertexBuffer(uStream);
		this->m_pVertexStream[uStream] = pBuffer.GetCast<COGLVertexBuffer>();
		this->BindStream(uStream);
	}

	void	COGLDevice::FreeVertexBuffer(const uint32 uStream){
		if(this->m_pVertexStream[uStream].IsValid()){
			this->UnbindStream(uStream);
			this->m_pVertexStream[uStream].Reset();
		}
	}

	CRefPtr<Graphic::IBuffer>	COGLDevice::GetVertexBuffer(const uint32 uStream) const{
		return this->m_pVertexStream[uStream].GetCast<Graphic::IBuffer>();
	}

	void	COGLDevice::SetShader(CRefPtr<Graphic::IShader> pShader){
		CR_APICHECK(this, pShader);

		auto pOGLShader = pShader.Cast<IOGLBaseShader>();

		this->FreeShader(pOGLShader->GetType());
		pOGLShader->Bind();
		switch (pOGLShader->GetType())
		{
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

	void	COGLDevice::FreeShader(const Graphic::ShaderType uType){
		switch (uType)
		{
		case Graphic::ShaderType::Vertex:
			this->UnbindAllStreams();
			if(this->m_pVertexShader.IsValid()){
				this->m_pVertexShader->Unbind();
			}
			this->m_pVertexShader.Reset();
			break;

		case Graphic::ShaderType::Fragment:
			if(this->m_pFragmentShader.IsValid()){
				this->m_pFragmentShader->Unbind();
			}
			this->m_pFragmentShader.Reset();
			break;

		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Invalid shader type.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	CRefPtr<Graphic::IShader>	COGLDevice::GetShader(const Graphic::ShaderType uType) const{
		switch (uType)
		{
		case Graphic::ShaderType::Vertex:	return this->m_pVertexShader.Get();
		case Graphic::ShaderType::Fragment:	return this->m_pFragmentShader.Get();
		default:
			throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
				L"Invalid shader type.", CR_INFO());
		}
	}

	void	COGLDevice::SetRenderPrimitive(const Graphic::PrimitiveType uType){
		switch (uType)
		{
		case Graphic::PrimitiveType::Points:	this->m_uPrimitiveMode = GL_POINTS;	break;
		case Graphic::PrimitiveType::Lines:		this->m_uPrimitiveMode = GL_LINES;	break;
		case Graphic::PrimitiveType::Triangles:	this->m_uPrimitiveMode = GL_TRIANGLES;	break;
		default:
			throw Exception::CInvalidArgumentException(L"uType", String::FromUInt32((uint32)uType),
				L"Unknown primitive type.", CR_INFO());
		}
	}

	const Graphic::PrimitiveType	COGLDevice::GetRenderPrimitive() const{
		switch (this->m_uPrimitiveMode)
		{
		case GL_POINTS:		return Graphic::PrimitiveType::Points;
		case GL_LINES:		return Graphic::PrimitiveType::Lines;
		case GL_TRIANGLES:	return Graphic::PrimitiveType::Triangles;
		default:
			throw Exception::CInvalidVarValueException(L"m_uPrimitiveType", String::FromUInt32(this->m_uPrimitiveMode),
				L"Unimplemented primitive type.", CR_INFO());
		}
	}

	void	COGLDevice::SetState(CRefPtr<Graphic::IDeviceState> pState){
		//CR_APICHECK(this, pState);

		//switch (pState->GetType())
		//{
		//case Graphic::DeviceStateType::Rasterizer:	
		//	this->SetStateRasterizer(pState.Cast<CDX9RasterizerState>());
		//	break;

		//case Graphic::DeviceStateType::Blend:
		//	this->SetStateBlend(pState.Cast<CDX9BlendState>());
		//	break;

		//case Graphic::DeviceStateType::DepthStencil:
		//	this->SetStateDepthStencil(pState.Cast<CDX9DepthStencilState>());
		//	break;

		//default:
		//	throw Exception::CInvalidArgumentException(L"pState->GetType()", String::ToString(pState->GetType()),
		//		L"Unknown device state type.", CR_INFO());
		//}
	}

	void	COGLDevice::FreeState(const Graphic::DeviceStateType uType){
		//switch (uType)
		//{
		//case Graphic::DeviceStateType::Blend:
		//	{
		//		CRefPtr<CDX9BlendState> pBlend = new CDX9BlendState(this, Graphic::CBlendStateDesc());
		//		this->SetStateBlend(pBlend);
		//		this->m_pStateBlend.Reset();
		//	}
		//	break;

		//case Graphic::DeviceStateType::DepthStencil:
		//	{
		//		CRefPtr<CDX9DepthStencilState> pDepth = new CDX9DepthStencilState(this, Graphic::CDepthStencilStateDesc());
		//		this->SetStateDepthStencil(pDepth);
		//		this->m_pStateDepthStencil.Reset();
		//	}
		//	break;

		//case Graphic::DeviceStateType::Rasterizer:
		//	{
		//		CRefPtr<CDX9RasterizerState> pRasterizer = new CDX9RasterizerState(this, Graphic::CRasterizerStateDesc());
		//		this->SetStateRasterizer(pRasterizer);
		//		this->m_pStateRasterizer.Reset();
		//	}
		//	break;

		//default:
		//	throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
		//		L"Unknown state type for clearing.", __FUNCTIONW__, __FILEW__, __LINE__);
		//}
	}

	CRefPtr<Graphic::IDeviceState>	COGLDevice::GetState(const Graphic::DeviceStateType uType) const{
		//switch (uType)
		//{
		//case Graphic::DeviceStateType::Blend:
		//	if(this->m_pStateBlend.IsNull())
		//		return new CDX9BlendState(this, Graphic::CBlendStateDesc());
		//	else
		//		return this->m_pStateBlend.Get();
		//	break;

		//case Graphic::DeviceStateType::DepthStencil:
		//	if(this->m_pStateDepthStencil.IsNull())
		//		return new CDX9DepthStencilState(this, Graphic::CDepthStencilStateDesc());
		//	else
		//		return this->m_pStateDepthStencil.Get();
		//	break;

		//case Graphic::DeviceStateType::Rasterizer:
		//	if(this->m_pStateRasterizer.IsNull())
		//		return new CDX9RasterizerState(this, Graphic::CRasterizerStateDesc());
		//	else
		//		return this->m_pStateRasterizer.Get();
		//	break;

		//default:
		//	throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
		//		L"Unknown state type.", __FUNCTIONW__, __FILEW__, __LINE__);
		//}
		CR_THROWNOTIMPLEMENTED();
	}

	void	COGLDevice::Render(const uint32 uPrimitiveCount){
		this->Render(uPrimitiveCount, 0);
	}

	void	COGLDevice::Render(const uint32 uPrimitiveCount, const uint32 uStartVertex){
		CR_GLBINDCHECK(this->m_WindowDC.Get(), this->m_GLRC.Get());

		uint32 uVertexCount = 0;
		switch (this->m_uPrimitiveMode)
		{
		case GL_POINTS:	uVertexCount = uPrimitiveCount;	break;
		case GL_LINES:	uVertexCount = uPrimitiveCount * 2; break;
		case GL_TRIANGLES:	uVertexCount = uPrimitiveCount * 3; break;
		default:
			throw Exception::CInvalidVarValueException(L"m_uPrimitiveMode", String::FromUInt32(this->m_uPrimitiveMode),
				L"Unknown primitive mode.", CR_INFO());
		}

		glDrawArrays(this->m_uPrimitiveMode, uStartVertex, uVertexCount);	CR_GLCHECK();
	}
	
	void	COGLDevice::RenderIndexed(const uint32 uPrimitiveCount){
		this->RenderIndexed(uPrimitiveCount, 0, 0);
	}

	void	COGLDevice::RenderIndexed(const uint32 uPrimitiveCount, const uint32 uStartVertex){
		this->RenderIndexed(uPrimitiveCount, uStartVertex, 0);
	}

	void	COGLDevice::RenderIndexed(const uint32 uPrimitiveCount, const uint32 uStartVertex, const uint32 uStartIndex){
		CR_GLBINDCHECK(this->m_WindowDC.Get(), this->m_GLRC.Get());

		if(this->m_pIndexStream.IsNull()){
			CR_THROW(L"Index buffer not set.");
		}

		uint32 uVertexCount = 0;
		switch (this->m_uPrimitiveMode)
		{
		case GL_POINTS:		uVertexCount = uPrimitiveCount;	break;
		case GL_LINES:		uVertexCount = uPrimitiveCount * 2; break;
		case GL_TRIANGLES:	uVertexCount = uPrimitiveCount * 3; break;
		}

		this->m_pIndexStream->Bind();
		glDrawRangeElements(this->m_uPrimitiveMode, uStartVertex, uStartVertex + uVertexCount, uPrimitiveCount, GL_UNSIGNED_SHORT, reinterpret_cast<const void*>(uStartIndex));
		this->m_pIndexStream->Unbind();
	}

	void	COGLDevice::RenderInstanced(const uint32 uInstanceCount, const uint32 uPrimitiveCount){
		this->RenderInstanced(uInstanceCount, uPrimitiveCount, 0);
	}

	void	COGLDevice::RenderInstanced(const uint32 uInstanceCount, const uint32 uPrimitiveCount, const uint32 uStartVertex){
		//if(this->m_pCurrentDeclaration.IsNull()){
		//	throw Exception::CNullPointerException(L"m_pCurrentDeclaration", 
		//		L"Vertex declaration must be set for instanced rendering.", __FUNCTIONW__, __FILEW__, __LINE__);
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
		//				L"Failed to set instance number for stream " + String::FromUInt32(uIndex) + L".", __FUNCTIONW__, __FILEW__, __LINE__);
		//		}
		//	}
		//}
		//try{
		//	this->Render(uPrimitiveCount, uStartVertex);
		//}
		//catch(Exception::CException& Exception){
		//	throw Exception::CException(
		//		L"Failed to render instanced data.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		//}

		//for(uint32 uIndex = 0; uIndex < this->m_pVertexBufferList.GetLength(); uIndex++){
		//	if(this->m_pVertexBufferList[uIndex].IsValid()){
		//		hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, 1);
		//		if(hResult != S_OK){
		//			throw Exception::CCOMException(hResult,
		//				L"Failed to free instance number for stream " + String::FromUInt32(uIndex) + L".", __FUNCTIONW__, __FILEW__, __LINE__);
		//		}
		//	}
		//}
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
		//		L"Vertex declaration must be set for instanced rendering.", __FUNCTIONW__, __FILEW__, __LINE__);
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
		//				L"Failed to set instance number for stream " + String::FromUInt32(uIndex) + L".", __FUNCTIONW__, __FILEW__, __LINE__);
		//		}
		//	}
		//}
		//try{
		//	this->RenderIndexed(uPrimitiveCount, uStartVertex, uStartIndex);
		//}
		//catch(Exception::CException& Exception){
		//	throw Exception::CException(
		//		L"Failed to render instanced data.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		//}

		//for(uint32 uIndex = 0; uIndex < this->m_pVertexBufferList.GetLength(); uIndex++){
		//	if(this->m_pVertexBufferList[uIndex].IsValid()){
		//		hResult = this->m_pDXObject->SetStreamSourceFreq(uIndex, 1);
		//		if(hResult != S_OK){
		//			throw Exception::CCOMException(hResult,
		//				L"Failed to free instance number for stream " + String::FromUInt32(uIndex) + L".", __FUNCTIONW__, __FILEW__, __LINE__);
		//		}
		//	}
		//}
	}

	void	COGLDevice::BeginRender(){

	}

	void	COGLDevice::EndRender(){

	}

	void	COGLDevice::Clear(const Math::CColor& Color){
		CR_GLBINDCHECK(this->m_WindowDC.Get(), this->m_GLRC.Get());
		
		glClearColor(Color.Red, Color.Green, Color.Blue, Color.Alpha);	CR_GLCHECK();
		glClear(GL_COLOR_BUFFER_BIT);	CR_GLCHECK();
	}

	void	COGLDevice::Clear(const float fZDepth, const uint32 uStencil){
		CR_GLBINDCHECK(this->m_WindowDC.Get(), this->m_GLRC.Get());

		glClearDepth(fZDepth);		CR_GLCHECK();
		glClearStencil(uStencil);	CR_GLCHECK();
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	CR_GLCHECK();
	}

	void	COGLDevice::SetOutputWindow(CRefPtr<Window::IWindow> pWindow){
		this->m_pOutputWindow = pWindow;
		this->m_WindowDC = this->m_pOutputWindow;
		this->m_GLRC.Bind(this->m_WindowDC);
	}

	CRefPtr<Window::IWindow>	COGLDevice::GetOutputWindow() const{
		return this->m_pOutputWindow;
	}

	void	COGLDevice::Swap(){
		if(!SwapBuffers(this->m_WindowDC.Get())){
			CR_THROWWIN(GetLastError(), L"Failed to swap buffer.");
		}
	}

	const uint32	COGLDevice::GetNumberOfStreams() const{
		return 16;
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
			this->UnbindStream(uIndex);
		}
	}
}