#pragma once

#include "Macros.h"
#include <Types.h>
#include <Ref.h>
#include <SmartPointers_RefPtr.h>
#include <Collection_List.h>
#include <Math_Size.h>
#include <Math_Color.h>
#include <Math_Matrix.h>
#include <Math_Rectangle.h>
#include <IO_Stream.h>
#include <ApiObject.h>
#include <WindowDriver.h>

#include "GraphicDriver_Consts.h"
#include "GraphicDriver_Structs.h"
#include "GraphicDriver_Strings.h"

namespace CB{
	namespace Graphic{
		class IShader;
		class IDevice;
		class IManager;
		class IAdapter;
		class IOutput;

		//==========================================================================
		//	Represents a per vertex definition
		//==========================================================================
		class IVertexDeclaration : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IDevice>	GetDevice() const = 0;

			virtual const Collection::CList<CVertexElement>	GetElements(CRefPtr<IShader> pVertexShader) const = 0;
		};

		//==========================================================================
		//	Resource in GPU memory, most of the time a vertex buffer, index buffer
		//	or a texture.
		//==========================================================================
		class IBuffer : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IDevice>	GetDevice() const = 0;
			virtual const uint32		GetLength() const = 0;
			virtual const BufferType	GetType() const = 0;
			virtual const BufferAccess	GetAccess() const = 0;
			virtual const BufferUsage	GetUsage() const = 0;

			virtual	void	LoadData(const void* pData, const uint32 uLength) = 0;
			virtual void	LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength) = 0;

			virtual CRefPtr<IO::IStream>	Map(const BufferAccess uAccess) = 0;
			virtual CRefPtr<IO::IStream>	Map(const BufferAccess uAccess, const bool bDiscard) = 0;
			virtual CRefPtr<IO::IStream>	Map(const BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) = 0;

			template<typename _Type>	
			void	LoadData(const Collection::IPacked<_Type>& Data){
				this->LoadData(Data.GetPointer(), Data.GetSizeInBytes());
			}
			template<typename _Type>
			void	LoadSubData(const Collection::IPacked<_Type>& Data, const uint32 uOffset){
				this->LoadSubData(Data.GetPointer(), uOffset, Data.GetSizeInBytes());
			}
		};

		//===========================================================================
		//	A spiecial kind of buffer used for color sampling in shaders.
		//===========================================================================
		class IBaseTexture : 
			public IApiObject
		{
		public:
			virtual void	SetFilters(const TextureFilter uMin, const TextureFilter uMag) = 0;
			virtual void	SetFilters(const TextureFilter uMin, const TextureFilter uMag, TextureFilter uMipMap) = 0;
			virtual void	SetAnisotropy(const uint32 uMaxAnisotropy) = 0;

			virtual CRefPtr<IDevice>	GetDevice() const = 0;
			virtual const BufferAccess	GetAccess() const = 0;
			virtual const BufferUsage	GetUsage() const = 0;
			virtual const BufferFormat	GetFormat() const = 0;
			virtual const TextureType	GetTextureType() const = 0;
			virtual const TextureFilter	GetMinFilter() const = 0;
			virtual const TextureFilter GetMaxFilter() const = 0;
			virtual const TextureFilter	GetMipmapFilter() const = 0;
			virtual const uint32		GetAnisotropy() const = 0;
		};

		//===========================================================================
		//	A 2-dimensional texture.
		//===========================================================================
		class ITexture2D :
			public virtual IBaseTexture
		{
		public:
			virtual void	SetCoordWrap(const TextureWrap uRCoord, const TextureWrap uSCoord) = 0;

			virtual const Math::CSize	GetSize() const = 0;

			virtual void	LoadData(const BufferFormat uInputFormat, const void* pData, const uint32 uWidth, const uint32 uHeight) = 0;
			virtual void	LoadSubData(const BufferFormat uInputFormat, const void* pData, const uint32 uXOffset, const uint32 uYOffset, const uint32 uWidth, const uint32 uHeight) = 0;

			template<typename _Type>
			void	LoadData(const Collection::IPacked<_Type>& Data, const uint32 uWidth, const uint32 uHeight){
				this->LoadData(Data.GetPointer(), uWidth, uHeight);
			}
			template<typename _Type>
			void	LoadSubData(const Collection::IPacked<_Type>& Data, const uint32 uXOffset, const uint32 uYOffset, const uint32 uWidth, const uint32 uHeight){
				this->LoadSubData(Data.GetPointer(), uXOffset, uYOffset, uWidth, uHeight);
			}
		};

		//===========================================================================
		//	Represents an compiled and ready to use shader object.
		//===========================================================================
		class IShader : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IDevice>	GetDevice() const = 0;

			virtual const ShaderType	GetType() const = 0;
			virtual const ShaderVersion	GetVersion() const = 0;

			virtual void	SetUniform(const CString& strName, const float fValue) = 0;
			virtual void	SetUniform(const CString& strName, const Math::CVector2D& vValue) = 0;
			virtual void	SetUniform(const CString& strName, const Math::CVector3D& vValue) = 0;
			virtual void	SetUniform(const CString& strName, const Math::CVector4D& vValue) = 0;
			virtual void	SetUniform(const CString& strName, const Math::CMatrix& mValue) = 0;
			
			virtual void	SetSampler(const CString& strName, CRefPtr<IBaseTexture> pTexture) = 0;
			virtual void	FreeSampler(const CString& strName) = 0;
			virtual CRefPtr<IBaseTexture>	GetSampler(const CString& strName) const = 0;
		};

		//===========================================================================
		//	A state representing options on some stage in GPU pipeline. Used as an
		//	easy setup for many device states.
		//===========================================================================
		class IDeviceState : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IDevice>		GetDevice() const = 0;

			virtual const DeviceStateType	GetType() const = 0;	
		};

		//=========================================================================
		//	Color blending state representing its options and arguments.
		//=========================================================================
		class IBlendState : 
			public virtual IDeviceState
		{
		public:
			virtual const CBlendStateDesc	GetDesc() const = 0;
		};

		//=========================================================================
		//	Depth and Stencil stage representing its options and arguments.
		//=========================================================================
		class IDepthStencilState : 
			public virtual IDeviceState
		{
		public:
			virtual const CDepthStencilStateDesc	GetDesc() const = 0;
		};

		//=========================================================================
		//	Rasterization stage reprezenting many selecting and culling options.
		//=========================================================================
		class IRasterizerState : 
			public virtual IDeviceState
		{
		public:
			virtual const CRasterizerStateDesc	GetDesc() const = 0;
		};

		//=========================================================================
		//	Specific rendering "device" - interface to gpu functionality, by specific graphic API.
		//=========================================================================
		class IDevice : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IAdapter>			GetAdapter() const = 0;
			virtual CRefPtr<IOutput>			GetOutput() const = 0;
			virtual CRefPtr<Window::IWindow>	GetOutputWindow() const = 0;

			virtual	void	SetOutputWindow(CRefPtr<Window::IWindow> pWindow) = 0;

			virtual CRefPtr<IVertexDeclaration>	CreateVertexDeclaration(CRefPtr<IShader> pVertexShader, const Collection::ICountable<CVertexElement>& Elements) = 0;
			virtual CRefPtr<IBuffer>			CreateBuffer(const BufferType uType, const BufferUsage uUsage, const BufferAccess uAccess, const uint32 uLength) = 0;
			virtual CRefPtr<IBuffer>			CreateBuffer(const BufferType uType, const BufferUsage uUsage, const BufferAccess uAccess, const uint32 uLength, const void* pData) = 0;
			virtual CRefPtr<ITexture2D>			CreateTexture2D(const Math::CSize& Size, const BufferUsage uUsage, const BufferAccess uAccess, const BufferFormat uFormat) = 0;
			virtual CRefPtr<ITexture2D>			CreateTexture2D(const Math::CSize& Size, const BufferUsage uUsage, const BufferAccess uAccess, const BufferFormat uFormat, const BufferFormat uInputFormat, const uint32 uLength, const void* pData) = 0;
			virtual CRefPtr<IBlendState>		CreateState(const CBlendStateDesc& Desc) = 0;
			virtual CRefPtr<IDepthStencilState>	CreateState(const CDepthStencilStateDesc& Desc) = 0;
			virtual CRefPtr<IRasterizerState>	CreateState(const CRasterizerStateDesc& Desc) = 0;

			virtual CRefPtr<IShader>			Compile(const ShaderType uType, const ShaderVersion uVersion, const CString& strSource) = 0;
			virtual CRefPtr<IShader>			Compile(const ShaderType uType, const ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint) = 0;

			virtual void	SetVertexDeclaration(CRefPtr<IVertexDeclaration> pDeclaration) = 0;
			virtual void	SetIndexBuffer(CRefPtr<IBuffer> pBuffer) = 0;
			virtual void	SetVertexBuffer(const uint32 uStream, CRefPtr<IBuffer> pBuffer) = 0;
			virtual void	SetShader(CRefPtr<IShader> pShader) = 0;
			virtual void	SetState(CRefPtr<IDeviceState> pState) = 0;
			virtual void	SetState(CRefPtr<IBlendState> pState, const Math::CColor& BlendFactor, const uint32 uSampleMask) = 0;
			virtual void	SetState(CRefPtr<IDepthStencilState> pState, const uint32 uStencilRef) = 0;
			virtual void	SetRenderPrimitive(const PrimitiveType uType) = 0;
			virtual void	SetScissorRect(const Math::CRectangle& Rect) = 0;
			virtual void	SetViewport(const Math::CRectangle& Rect) = 0;

			virtual void	FreeVertexDeclaration() = 0;
			virtual void	FreeIndexBuffer() = 0;
			virtual void	FreeVertexBuffer(const uint32 uStream) = 0;
			virtual void	FreeShader(const ShaderType uType) = 0;
			virtual void	FreeState(const DeviceStateType uType) = 0;

			virtual CRefPtr<IVertexDeclaration>	GetVertexDeclaration() const = 0;
			virtual CRefPtr<IBuffer>			GetIndexBuffer() const = 0;
			virtual CRefPtr<IBuffer>			GetVertexBuffer(const uint32 uStream) const = 0;
			virtual CRefPtr<IShader>			GetShader(const ShaderType uType) const = 0;
			virtual CRefPtr<IDeviceState>		GetState(const DeviceStateType uType) const = 0;
			
			virtual const FeatureLevel			GetFeatureLevel() const = 0;
			virtual const PrimitiveType			GetRenderPrimitive() const = 0;
			virtual const uint32				GetNumberOfStreams() const = 0;
			virtual const CString				GetLastCompilationLog() const = 0;
			virtual const Math::CRectangle		GetScissorRect() const = 0;
			virtual const Math::CRectangle		GetViewport() const = 0;

			virtual	void	Render(const uint32 uPrimitiveCount) = 0;
			virtual void	Render(const uint32 uPrimitiveCount, const uint32 uStartVertex) = 0;
			virtual void	RenderIndexed(const uint32 uPrimitiveCount) = 0;
			virtual void	RenderIndexed(const uint32 uPrimitiveCount, const uint32 uStartVertex) = 0;
			virtual void	RenderIndexed(const uint32 uPrimitiveCount, const uint32 uStartVertex, const uint32 uStartIndex) = 0;
			
			virtual void	RenderInstanced(const uint32 uInstanceCount, const uint32 uPrimitiveCount) = 0;
			virtual void	RenderInstanced(const uint32 uInstanceCount, const uint32 uPrimitiveCount, const uint32 uStartVertex) = 0;
			virtual void	RenderInstancedIndexed(const uint32 uInstanceCount, const uint32 uPrimitiveCount) = 0;
			virtual void	RenderInstancedIndexed(const uint32 uInstanceCount, const uint32 uPrimitiveCount, const uint32 uStartVertex) = 0;
			virtual void	RenderInstancedIndexed(const uint32 uInstanceCount, const uint32 uPrimitiveCount, const uint32 uStartVertex, const uint32 uStartIndex) = 0;

			virtual void	BeginRender() = 0;
			virtual void	EndRender()  = 0;

			virtual void	Clear(const Math::CColor& Color) = 0;
			virtual void	Clear(const float fZDepth, const uint32 uStencil) = 0;
			
			virtual void	Swap() = 0;

			template<typename _T>
			CRefPtr<IBuffer>	CreateBuffer(const BufferType uType, const BufferUsage uUsage, const BufferAccess uAccess, const Collection::IPacked<_T>& Array){
				return this->CreateBuffer(uType, uUsage, uAccess, Array.GetSizeInBytes(), Array.GetPointer());
			}
			template<typename _T>
			CRefPtr<ITexture2D>	CreateTexture2D(const Math::CSize& Size, const BufferUsage uUsage, const BufferAccess uAccess, const BufferFormat uFormat, const BufferFormat uInputFormat, const Collection::IPacked<_T>& Array){
				return this->CreateTexture2D(Size, uUsage, uAccess, uFormat, uInputFormat, Array.GetSizeInBytes(), Array.GetPointer());
			}
		};

		//======================================================================
		//	Represents diffrent displays - like monitors.
		//======================================================================
		class IOutput : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IAdapter>	GetAdapter() const = 0;

			virtual const uint32	GetIndex() const = 0;
			virtual const CString	GetName() const = 0;

			virtual const uint32							GetNumberOfDisplayModes(BufferFormat uDisplayFormat) const = 0;
			virtual const Collection::CList<CDisplayMode>	GetDisplayModes(const BufferFormat uDisplayFormat) const = 0;
		};

		//=========================================================================
		//	Represents an specific rendering device - like a graphic card.
		//	Each graphic card can have multiple outputs (dual monitors anyone?)
		//	=======================================================================
		class IAdapter : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IManager>	GetManager() const = 0;

			virtual const uint32	GetIndex() const = 0;
			virtual const CString	GetName() const = 0;

			virtual const uint32		GetNumberOfOutputs() const = 0;
			virtual CRefPtr<IOutput>	GetOutput(const uint32 uIndex) = 0;
			virtual CRefPtr<IOutput>	GetDefaultOutput() = 0;
			virtual CRefPtr<IOutput>	GetOutputForWindow(CRefPtr<Window::IWindow> pWindow) = 0;

			virtual CRefPtr<IDevice>	CreateDevice(CRefPtr<Window::IWindow> pFocusWindow, const CDeviceDesc& DeviceDesc, const Collection::ICountable<FeatureLevel>& FeatureLevels) = 0;
			virtual CRefPtr<IDevice>	CreateDevice(CRefPtr<Window::IWindow> pFocusWindow, const CDeviceDesc& DeviceDesc, const Collection::ICountable<FeatureLevel>& FeatureLevels, CRefPtr<IOutput> pOutput) = 0;
		};

		//==========================================================================
		//	Manager is responible for listing avaible adapters. There can be multpile managers,
		//	but it makes little sense, because each will present the same adapters.
		//==========================================================================
		class IManager : 
			public IApiObject
		{
		public:
			virtual const uint32		GetNumberOfAdapters() const = 0;
			virtual CRefPtr<IAdapter>	GetAdapter(const uint32 uIndex) = 0;
			virtual CRefPtr<IAdapter>	GetDefaultAdapter() = 0;
		};

		//==========================================================================
		//	Driver is an currently loaded abstract layer for rendering. (like DirectX or OpenGL).
		//==========================================================================
		class IDriver : 
			public IRef
		{
		public:
			virtual CRefPtr<IManager>	CreateManager(CRefPtr<Window::IManager> pWindowManager) = 0;
		};

		//==========================================================================
		//	Main point of loading rendering drivers. In theory can load multiple diffrent drivers,
		//	but not tested. On failure throws ModuleExceptions.
		//==========================================================================
		extern GRAPHICDRVINTERFACE_API	CRefPtr<IDriver>	LoadDriver(const CString& strDriver);
	}
}