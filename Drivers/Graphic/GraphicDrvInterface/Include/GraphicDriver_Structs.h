#pragma once

#include "Macros.h"
#include "GraphicDriver_Consts.h"
#include "../../Common/Include/Math.h"
#include "../../Common/Include/SmartPointers_RefPtr.h"
#include "../../WindowDrvInterface/Include/WindowDriver.h"

namespace CB{
	namespace Graphic{
		//==============================
		//	Class representing outputs display modes. Can be used to define 
		//	a device back buffer.
		//==============================
		class GRAPHICDRVINTERFACE_API CDisplayMode{
		public:
			Math::CSize		Size;
			uint32		uRefreshRate;
			BufferFormat	uFormat;

			CDisplayMode();
			CDisplayMode(const CDisplayMode& Mode);
			CDisplayMode(const Math::CSize& Size, const uint32 uRefreshRate, const BufferFormat uFormat);

			void Set(const Math::CSize& Size, const uint32 uRefreshRate, const BufferFormat uFormat);

			const CDisplayMode& operator=(const CDisplayMode& Mode);

			const bool operator==(const CDisplayMode& mode) const;
			const bool operator!=(const CDisplayMode& mode) const;

			const CString	ToString() const;
		};

		//===============================
		//	Class describing device configuration.
		//===============================
		class GRAPHICDRVINTERFACE_API CDeviceDesc{
		public:
			CRefPtr<Window::IWindow>	OutputWindow;
			CDisplayMode				BackBuffer;
			BufferFormat				uDepthStencilFormat;
			bool						bFullScreen;

			CDeviceDesc();
			CDeviceDesc(const CDeviceDesc& Desc);
			CDeviceDesc(CRefPtr<Window::IWindow> pOutputWindow, const CDisplayMode& Mode, const BufferFormat uDepthStencilFormat);
			CDeviceDesc(CRefPtr<Window::IWindow> pOutputWindow, const CDisplayMode& Mode, const BufferFormat uDepthStencilFormat, const bool bFullScreen);

			const CDeviceDesc&	operator=(const CDeviceDesc& Desc);

			const CString	ToString() const;
		};

		class GRAPHICDRVINTERFACE_API CVertexElement{
		public:
			uint32				uStream;
			CString				strParam;
			uint32				uOffset;
			VertexType			uType;
			uint32				uTypeNumber;
			InstanceDataType	uInstanceUsage;

			CVertexElement();
			CVertexElement(const CVertexElement& Element);
			CVertexElement(const uint32 uStream, const CString strParam, const uint32 uOffset, const VertexType uType, const uint32 uTypeNumber);
			CVertexElement(const uint32 uStream, const CString strParam, const uint32 uOffset, const VertexType uType, const uint32 uTypeNumber, const InstanceDataType uInstance);

			void Set(const uint32 uStream, const CString strParam, const uint32 uOffset, const VertexType uType, const uint32 uTypeNumber);
			void Set(const uint32 uStream, const CString strParam, const uint32 uOffset, const VertexType uType, const uint32 uTypeNumber, const InstanceDataType uInstance);

			const CVertexElement&	operator=(const CVertexElement& Element);

			const CString	ToString() const;
		};

		class GRAPHICDRVINTERFACE_API CStencilInstDesc{
		public:
			StencilOperation	uStencilPass;
			StencilOperation	uDepthTestFail;
			StencilOperation	uStencilFail;
			CompareFunc			uStencilFunc;

			CStencilInstDesc();
			CStencilInstDesc(const CStencilInstDesc& Desc);
			CStencilInstDesc(const StencilOperation uPass, const StencilOperation uDepthFail, const StencilOperation uFail, const CompareFunc uFunc);

			void	Set(const StencilOperation uPass, const StencilOperation uDepthFail, const StencilOperation uFail, const CompareFunc uFunc);

			const CStencilInstDesc&	operator=(const CStencilInstDesc& Desc);

			const CString	ToString() const;
		};

		class GRAPHICDRVINTERFACE_API CDepthStencilStateDesc{
		public:
			bool		bDepthTestEnabled;
			bool		bDepthWrite;
			CompareFunc	uDepthFunction;
			bool		bStencilTestEnabled;
			uint32	uStencilReadMask;
			uint32	uStencilWriteMask;
			CStencilInstDesc	StencilFront;
			CStencilInstDesc	StencilBack;

			CDepthStencilStateDesc();
			CDepthStencilStateDesc(const CDepthStencilStateDesc& State);
			CDepthStencilStateDesc(const bool bDepthEnabled, const bool bDepthWrite, const CompareFunc uDepthFunction, const bool bStencilEnabled, const uint32 uStencilWriteMask, const uint32 uStencilReadMask, const CStencilInstDesc& FrondDesc, const CStencilInstDesc& BackDesc);
		
			void	SetDepth(const bool bEnabled, const CompareFunc uFunction);
			void	SetDepth(const bool bEnabled, const bool bDepthWrite, const CompareFunc uFunction);
			void	SetStencil(const bool bEnabled, const CStencilInstDesc& FrontDesc);
			void	SetStencil(const bool bEnabled, const CStencilInstDesc& FrontDesc, const CStencilInstDesc& BackDesc);
			void	SetStencil(const bool bEnabled, const uint32 uWriteMask, const uint32 uReadMask, const CStencilInstDesc& FrontDesc);
			void	SetStencil(const bool bEnabled, const uint32 uWriteMask, const uint32 uReadMask, const CStencilInstDesc& FrontDesc, const CStencilInstDesc& BackDesc);
		
			const CDepthStencilStateDesc&	operator=(const CDepthStencilStateDesc& State);

			const CString	ToString() const;
		};

		class GRAPHICDRVINTERFACE_API CBlendInstDesc{
		public:
			BlendOption		uSourceOperand;
			BlendOperation	uOperation;
			BlendOption		uDestOperand;

			CBlendInstDesc();
			CBlendInstDesc(const CBlendInstDesc& Desc);
			CBlendInstDesc(const BlendOption uSourceOperand, const BlendOperation uOperation, const BlendOption uDestOperand);

			void	Set(const BlendOption uSourceOperand, const BlendOperation uOperation, const BlendOption uDestOperand);

			const CBlendInstDesc&	operator=(const CBlendInstDesc& Dest);

			const CString	ToString() const;
		};

		class GRAPHICDRVINTERFACE_API CBlendStateDesc{
		public:
			bool			bEnabled[8];
			CBlendInstDesc	ColorBlend;
			CBlendInstDesc	AlphaBlend;
			uint8			uWriteMask[8];

			CBlendStateDesc();
			CBlendStateDesc(const CBlendStateDesc& Desc);
			CBlendStateDesc(const bool bEnabled, const CBlendInstDesc& ColorBelnd, const CBlendInstDesc& AlphaBlend, const uint8 uWriteMask);

			void Set(const bool bEnabled, const CBlendInstDesc& ColorBelnd, const CBlendInstDesc& AlphaBlend, const uint8 uWriteMask);

			const CBlendStateDesc& operator=(const CBlendStateDesc& Desc);

			const CString	ToString() const;
		};

		class GRAPHICDRVINTERFACE_API CRasterizerStateDesc{
		public:
			CullMode	uCullMode;
			FillMode	uFillMode;
			bool		bFrontCounterClockWise;
			bool		bDepthClipEnabled;
			bool		bScissorEnabled;

			CRasterizerStateDesc();
			CRasterizerStateDesc(const CRasterizerStateDesc& Desc);
			CRasterizerStateDesc(const CullMode uCull, const FillMode uFill, const bool bFrontCCW, const bool bDepthClipEnabled, const bool bScissorEnabled);

			void Set(const CullMode uCull, const FillMode uFill, const bool bFrontCCW, const bool bDepthClipEnabled, const bool bScissorEnabled);

			const CRasterizerStateDesc&	operator=(const CRasterizerStateDesc& Desc);

			const CString	ToString() const;
		};
	}
}