#pragma once

#include "Output.h"
#include "Adapter.h"
#include "DeviceContext.h"
#include "WindowDeviceContext.h"
#include "CGContext.h"

#include "OpenGL.h"

namespace CB{
	class IOGLBaseBuffer;
	class IOGLBaseShader;
	class COGLVertexDeclaration;

	class COGLDevice : 
		public Graphic::IDevice,
		public Manage::IManagedObject<COGLAdapter, COGLDevice>,
		public Manage::IObjectManager<IOGLBaseBuffer>,
		public Manage::IObjectManager<IOGLBaseShader>,
		public Manage::IObjectManager<COGLVertexDeclaration>
	{
	private:
		CRefPtr<Window::IWindow>	m_pOutputWindow;
		CDeviceContext				m_DC;
		CGLContext					m_GLRC;
		CWindowDeviceContext		m_WindowDC;
		CCGContext					m_CGContext;

		GLenum	m_uPrimitiveMode;

		Collection::CList<CPtr<IOGLBaseBuffer>>	m_pVertexStream;
		CPtr<IOGLBaseBuffer>		m_pIndexStream;
		CPtr<IOGLBaseShader>		m_pVertexShader;
		CPtr<IOGLBaseShader>		m_pFragmentShader;
		CPtr<COGLVertexDeclaration>	m_pVertexDeclaration;

	public:
		COGLDevice(CRefPtr<COGLAdapter> pAdapter, const PIXELFORMATDESCRIPTOR& pfc, CRefPtr<Window::IWindow> pOutputWindow, CRefPtr<COGLOutput> pOutput);
		~COGLDevice();

		HDC		GetWindowContext() const;
		HGLRC	GetRenderContext() const;

		CGcontext	GetCGContext() const;
		CGprofile	GetCGProfile(const Graphic::ShaderVersion uVersion, const Graphic::ShaderType uType) const;

		//	OVERRIDES	====================================================

		void	RemoveObject(CPtr<IOGLBaseBuffer> pBuffer) override;
		void	RemoveObject(CPtr<IOGLBaseShader> pShader) override;
		void	RemoveObject(CPtr<COGLVertexDeclaration> pDeclaration) override;

		//	END OF OVERRIDES	============================================

		//	INTERFACE IMPLEMENTATION	====================================

		const unsigned	GetApiId() const override;

		CRefPtr<Graphic::IAdapter>	GetAdapter() const override;

		CRefPtr<Graphic::IVertexDeclaration>	CreateVertexDeclaration(CRefPtr<Graphic::IShader> pVertexShader, const Collection::ICountable<Graphic::CVertexElement>& Elements) override;
		CRefPtr<Graphic::IBuffer>		CreateBuffer(const Graphic::BufferType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const unsigned uLength) override;
		CRefPtr<Graphic::IBuffer>		CreateBuffer(const Graphic::BufferType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const unsigned uLength, const void* pData) override;

		CRefPtr<Graphic::ITexture2D>	CreateTexture(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat) override;
		CRefPtr<Graphic::ITexture2D>	CreateTexture(const Math::CSize& Size, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat, const unsigned uLength, const void* pData) override;

		CRefPtr<Graphic::IBlendState>			CreateState(const Graphic::CBlendStateDesc& Desc) override;
		CRefPtr<Graphic::IRasterizerState>		CreateState(const Graphic::CRasterizerStateDesc& Desc) override;
		CRefPtr<Graphic::IDepthStencilState>	CreateState(const Graphic::CDepthStencilStateDesc& Desc) override;

		CRefPtr<Graphic::IShader>	Compile(const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, const CString& strSource) override;
		CRefPtr<Graphic::IShader>	Compile(const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint) override;

		const CString				GetLastCompilationLog() const override;

		void	SetVertexDeclaration(CRefPtr<Graphic::IVertexDeclaration> pDeclaration) override;
		void	FreeVertexDeclaration() override;
		CRefPtr<Graphic::IVertexDeclaration>	GetVertexDeclaration() const override;

		void	SetIndexBuffer(CRefPtr<Graphic::IBuffer> pBuffer) override;
		void	FreeIndexBuffer() override;
		CRefPtr<Graphic::IBuffer>	GetIndexBuffer() const override;

		void	SetVertexBuffer(const unsigned uStream, CRefPtr<Graphic::IBuffer> pBuffer) override;
		void	FreeVertexBuffer(const unsigned uStream) override;
		CRefPtr<Graphic::IBuffer>	GetVertexBuffer(const unsigned uStream) const override;

		void	SetShader(CRefPtr<Graphic::IShader> pShader) override;
		void	FreeShader(const Graphic::ShaderType uType) override;
		CRefPtr<Graphic::IShader>	GetShader(const Graphic::ShaderType uType) const override;

		void	SetRenderPrimitive(const Graphic::PrimitiveType uType) override;
		const Graphic::PrimitiveType	GetRenderPrimitive() const override;

		void	SetState(CRefPtr<Graphic::IDeviceState> pState) override;
		void	FreeState(const Graphic::DeviceStateType uType) override;
		CRefPtr<Graphic::IDeviceState>	GetState(const Graphic::DeviceStateType uType) const override;

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

		void	SetOutputWindow(CRefPtr<Window::IWindow> pWindow) override;
		CRefPtr<Window::IWindow>	GetOutputWindow() const override;
		void	Swap() override;

		const uint32	GetNumberOfStreams() const override;

		//	END OF INTERFACE IMPLEMENTATION	================================

	private:
		void BindStream(const uint32 uStream);
		void BindAllStreams();
		void UnbindStream(const uint32 uStream);
		void UnbindAllStreams();
	};

	extern void	ReportGLError(GLenum uError, const CString& strFunction, const CString& strFile, const uint32 uLine);
	extern void	ReportGLBindMismatch(const CString& strFunction, const CString& strFile, const uint32 uLine);
}

#define CR_GLCHECK()	{ GLenum __uError = glGetError(); if(__uError != GL_NO_ERROR){ CB::ReportGLError(__uError, CR_INFO()); } }
#define CR_GLBINDCHECK(DC,RC)	{ HDC __hDC = wglGetCurrentDC(); HGLRC __hRC = wglGetCurrentContext(); if(__hDC != (DC) || __hRC != (RC)){ CB::ReportGLBindMismatch(CR_INFO()); } } 