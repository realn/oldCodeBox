#pragma once

#include "Output.h"
#include "Adapter.h"
#include "DeviceContext.h"
#include "WindowDeviceContext.h"
#include "CGContext.h"
#include "RenderContext.h"

#include "OpenGL_Core.h"

namespace CB{
	class IOGLBaseBuffer;
	class IOGLBaseShader;
	class IOGLBaseState;
	class IOGLBaseTexture;
	class COGLVertexDeclaration;

	class COGLDevice : 
		public Graphic::IDevice,
		public Manage::IManagedObject<COGLAdapter, COGLDevice>,
		public Manage::IObjectManager<IOGLBaseBuffer>,
		public Manage::IObjectManager<IOGLBaseShader>,
		public Manage::IObjectManager<IOGLBaseState>,
		public Manage::IObjectManager<IOGLBaseTexture>,
		public Manage::IObjectManager<COGLVertexDeclaration>
	{
	private:
		CRefPtr<Window::IWindow>	m_pOutputWindow;
		CRefPtr<COGLOutput>			m_pOutput;

		CRenderContext				m_RenderContext;
		CWindowDeviceContext		m_WindowDC;
		CCGContext					m_CGContext;

		Math::CColor			m_BlendFactor;
		uint32					m_uSampleMask;
		uint32					m_uStencilRef;
		GLenum					m_uPrimitiveMode;
		Graphic::FeatureLevel	m_uFeatureLevel;
		Math::CRectangle		m_ScissorRect;
		Math::CRectangle		m_Viewport;

		Collection::CList<CPtr<IOGLBaseBuffer>>	m_pVertexStream;
		CPtr<IOGLBaseBuffer>	m_pIndexStream;
		
		CPtr<IOGLBaseShader>	m_pVertexShader;
		CPtr<IOGLBaseShader>	m_pFragmentShader;

		CPtr<IOGLBaseState>		m_pDepthStencilState;
		CPtr<IOGLBaseState>		m_pBlendState;
		CPtr<IOGLBaseState>		m_pRasterizerState;

		CPtr<COGLVertexDeclaration>	m_pVertexDeclaration;

	public:
		COGLDevice(CRefPtr<COGLAdapter> pAdapter, CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc, const Collection::ICountable<Graphic::FeatureLevel>& FeatureLevels, CRefPtr<COGLOutput> pOutput);
		~COGLDevice();

		HDC		GetWindowContext() const;
		HGLRC	GetRenderContext() const;

		CGcontext	GetCGContext() const;
		CGprofile	GetCGProfile(const Graphic::ShaderVersion uVersion, const Graphic::ShaderType uType) const;

		//	OVERRIDES	====================================================

		void	RemoveObject(CPtr<IOGLBaseBuffer> pBuffer) override;
		void	RemoveObject(CPtr<IOGLBaseShader> pShader) override;
		void	RemoveObject(CPtr<IOGLBaseState> pState) override;
		void	RemoveObject(CPtr<IOGLBaseTexture> pTexture) override;
		void	RemoveObject(CPtr<COGLVertexDeclaration> pDeclaration) override;

		//	END OF OVERRIDES	============================================

		//	INTERFACE IMPLEMENTATION	====================================

		const unsigned	GetApiId() const override;

		CRefPtr<Graphic::IAdapter>	GetAdapter() const override;
		CRefPtr<Graphic::IOutput>	GetOutput() const override;
		CRefPtr<Window::IWindow>	GetOutputWindow() const override;

		void	SetOutputWindow(CRefPtr<Window::IWindow> pWindow) override;

		CRefPtr<Graphic::IVertexDeclaration>	CreateVertexDeclaration(CRefPtr<Graphic::IShader> pVertexShader, const Collection::ICountable<Graphic::CVertexElement>& Elements) override;
		CRefPtr<Graphic::IBuffer>				CreateBuffer(const Graphic::BufferType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const unsigned uLength) override;
		CRefPtr<Graphic::IBuffer>				CreateBuffer(const Graphic::BufferType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const unsigned uLength, const void* pData) override;
		CRefPtr<Graphic::ITexture2D>			CreateTexture2D(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat) override;
		CRefPtr<Graphic::ITexture2D>			CreateTexture2D(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat, const Graphic::BufferFormat uInputFormat, const unsigned uLength, const void* pData) override;
		CRefPtr<Graphic::IBlendState>			CreateState(const Graphic::CBlendStateDesc& Desc) override;
		CRefPtr<Graphic::IRasterizerState>		CreateState(const Graphic::CRasterizerStateDesc& Desc) override;
		CRefPtr<Graphic::IDepthStencilState>	CreateState(const Graphic::CDepthStencilStateDesc& Desc) override;

		CRefPtr<Graphic::IShader>	Compile(const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, const CString& strSource) override;
		CRefPtr<Graphic::IShader>	Compile(const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint) override;

		void	SetVertexDeclaration(CRefPtr<Graphic::IVertexDeclaration> pDeclaration) override;
		void	SetIndexBuffer(CRefPtr<Graphic::IBuffer> pBuffer) override;
		void	SetVertexBuffer(const unsigned uStream, CRefPtr<Graphic::IBuffer> pBuffer) override;
		void	SetShader(CRefPtr<Graphic::IShader> pShader) override;
		void	SetState(CRefPtr<Graphic::IDeviceState> pState) override;
		void	SetState(CRefPtr<Graphic::IBlendState> pState, const Math::CColor& BlendFactor, const uint32 uSampleMask) override;
		void	SetState(CRefPtr<Graphic::IDepthStencilState> pState, const uint32 uStencilRef) override;
		void	SetRenderPrimitive(const Graphic::PrimitiveType uType) override;
		void	SetScissorRect(const Math::CRectangle& Rect) override;
		void	SetViewport(const Math::CRectangle& Viewport) override;

		CRefPtr<Graphic::IVertexDeclaration>	GetVertexDeclaration() const override;
		CRefPtr<Graphic::IBuffer>				GetIndexBuffer() const override;
		CRefPtr<Graphic::IBuffer>				GetVertexBuffer(const unsigned uStream) const override;
		CRefPtr<Graphic::IShader>				GetShader(const Graphic::ShaderType uType) const override;
		CRefPtr<Graphic::IDeviceState>			GetState(const Graphic::DeviceStateType uType) const override;

		const Graphic::FeatureLevel				GetFeatureLevel() const override;
		const Graphic::PrimitiveType			GetRenderPrimitive() const override;
		const CString							GetLastCompilationLog() const override;
		const uint32							GetNumberOfStreams() const override;
		const Math::CRectangle					GetScissorRect() const override;
		const Math::CRectangle					GetViewport() const override;


		void	FreeVertexDeclaration() override;
		void	FreeIndexBuffer() override;
		void	FreeVertexBuffer(const unsigned uStream) override;
		void	FreeShader(const Graphic::ShaderType uType) override;
		void	FreeState(const Graphic::DeviceStateType uType) override;


		void	Render(const unsigned uPrimitiveCount) override;
		void	Render(const unsigned uPrimitiveCount, const unsigned uStartVertex) override;
		void	RenderIndexed(const unsigned uPrimitiveCount) override;
		void	RenderIndexed(const unsigned uPrimitiveCount, const unsigned uStartVertex) override;
		void	RenderIndexed(const unsigned uPrimitiveCount, const unsigned uStartVertex, const unsigned uStartIndex) override;

		void	RenderInstanced(const unsigned uInstanceCount, const unsigned uPrimitiveCount) override;
		void	RenderInstanced(const unsigned uInstanceCount, const unsigned uPrimitiveCount, const unsigned uStartVertex) override;
		void	RenderInstancedIndexed(const unsigned uInstanceCount, const unsigned uPrimitiveCount) override;
		void	RenderInstancedIndexed(const unsigned uInstanceCount, const unsigned uPrimitiveCount, const unsigned uStartVertex) override;
		void	RenderInstancedIndexed(const unsigned uInstanceCount, const unsigned uPrimitiveCount, const unsigned uStartVertex, const unsigned uStartIndex) override;

		void	BeginRender() override;
		void	EndRender() override;
		void	Clear(const Math::CColor& Color) override;
		void	Clear(const float fZDepth, const unsigned uStencil) override;

		void	Swap() override;

		//	END OF INTERFACE IMPLEMENTATION	================================

	private:
		void BindStream(const uint32 uStream);
		void BindAllStreams();
		void UnbindStream(const uint32 uStream);
		void UnbindAllStreams();

		const bool	LoadFeatureLevel(const Graphic::FeatureLevel uLevel, const bool bCoreCreate);
		const bool	CreateRenderContext(const uint32 uMajorVersion, const uint32 uMinorVersion, const bool bCoreCreate);

		void	SetGLState(const Graphic::CDepthStencilStateDesc& Desc);
		void	SetGLState(const Graphic::CRasterizerStateDesc& Desc);
		void	SetGLState(const Graphic::CBlendStateDesc& Desc);

		void	SetGLStateStencilFace(const Graphic::CDepthStencilStateDesc& StencilDesc, const Graphic::CStencilInstDesc& Desc, const GLenum uFace);
	};
}