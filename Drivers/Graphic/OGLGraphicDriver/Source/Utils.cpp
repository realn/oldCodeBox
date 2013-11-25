#include "../Internal/Utils.h"

namespace CB{
	namespace GLUtils{
		const uint32	GetBitsPerPixel(const Graphic::BufferFormat uFormat){
			switch(uFormat){

				//	Depth Component
			case Graphic::BufferFormat::D16:	return 16;
			case Graphic::BufferFormat::D24:	return 24;				
			case Graphic::BufferFormat::D24S8:	return 32;
			case Graphic::BufferFormat::D24X8:	return 32;
			case Graphic::BufferFormat::D32:	return 32;
			case Graphic::BufferFormat::D32F:	return 32;
			case Graphic::BufferFormat::D32S8X24:	return 64;
			case Graphic::BufferFormat::D32FS8X24U:	return 64;

				//	One Component
			case Graphic::BufferFormat::R8:		return 8;
			case Graphic::BufferFormat::A8:		return 8;
			case Graphic::BufferFormat::R16:	return 16;
			case Graphic::BufferFormat::R16F:	return 16;
			case Graphic::BufferFormat::R32:	return 32;
			case Graphic::BufferFormat::R32F:	return 32;

				//	Two Components
			case Graphic::BufferFormat::R8G8:		return 16;
			case Graphic::BufferFormat::R16G16:		return 32;
			case Graphic::BufferFormat::R16G16F:	return 32;
			case Graphic::BufferFormat::R32G32:		return 64;
			case Graphic::BufferFormat::R32G32F:	return 64;

				//	Three Components
			case Graphic::BufferFormat::R8G8B8:		return 24;
			case Graphic::BufferFormat::B8G8R8:		return 24;
			case Graphic::BufferFormat::R8G8B8_sRGB:	return 24;
			case Graphic::BufferFormat::R16G16B16:	return 48;
			case Graphic::BufferFormat::R16G16B16F:	return 48;
			case Graphic::BufferFormat::R32G32B32:	return 96;
			case Graphic::BufferFormat::R32G32B32F:	return 96;

				//	Four Components
			case Graphic::BufferFormat::B8G8R8A8:		return 32;
			case Graphic::BufferFormat::B8G8R8A8_sRGB:	return 32;
			case Graphic::BufferFormat::B8G8R8X8:		return 32;
			case Graphic::BufferFormat::B8G8R8X8_sRGB:	return 32;
			case Graphic::BufferFormat::R8G8B8A8:		return 32;
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	return 32;
			case Graphic::BufferFormat::R16G16B16A16:	return 64;
			case Graphic::BufferFormat::R16G16B16A16F:	return 64;
			case Graphic::BufferFormat::R32G32B32A32:	return 128;
			case Graphic::BufferFormat::R32G32B32A32F:	return 128;

			default:
				return 0;
			}
		}

		const bool CheckSize(const uint8 uBits[], const uint8 uElements, const uint8 uA, const uint8 uB, const uint8 uC, const uint8 uD){
			switch (uElements)
			{
			case 4:
				return uBits[0] == uA && uBits[1] == uB && uBits[2] == uC && uBits[3] == uD;
			case 3:
				return uBits[0] == uA && uBits[1] == uB && uBits[2] == uC;
			case 2:
				return uBits[0] == uA && uBits[1] == uB;
			case 1:
				return uBits[0] == uA;
			default:
				return false;
			}
		}

		const bool CheckSeq(const uint8 uShift[], const uint8 uElements, const uint8 uBits[], const uint8 uA, const uint8 uB, const uint8 uC, const uint8 uD){
			switch (uElements)
			{
			case 4:
				return 
					uShift[uA] == 0 && uBits[uA] != 0 &&
					uShift[uB] == uBits[uA] &&
					uShift[uC] == uBits[uB] + uBits[uA] &&
					uShift[uD] == uBits[uC] + uBits[uB] + uBits[uA];

			case 3:
				return 
					uShift[uA] == 0 && uBits[uA] != 0 &&
					uShift[uB] == uBits[uA] &&
					uShift[uC] == uBits[uB] + uBits[uA];

			case 2:
				return 
					uShift[uA] == 0 && uBits[uA] != 0 &&
					uShift[uB] == uBits[uA];
			
			case 1:
				return 
					uShift[uA] == 0 && uBits[uA] != 0;

			default:
				return false;
			}
		}

		const uint8 R = 0;
		const uint8 G = 1;
		const uint8 B = 2;
		const uint8 A = 3;

		const Graphic::BufferFormat ToColorBufferFormat(const uint8 uBits[], const uint8 uShift[], const uint32 uColorBits){
			switch (uColorBits)
			{
			case 32:
				if(CheckSize(uBits, 4, 8, 8, 8, 8)){
					if(CheckSeq(uShift, 4, uBits, R, G, B, A)){
						return Graphic::BufferFormat::R8G8B8A8;
					}
					if(CheckSeq(uShift, 4, uBits, B, G, R, A)){
						return Graphic::BufferFormat::B8G8R8A8;
					}
				}
				if(CheckSize(uBits, 3, 8, 8, 8, 0)){
					if(CheckSeq(uShift, 3, uBits, R, G, B, A)){
						return Graphic::BufferFormat::R8G8B8;
					}
					if(CheckSeq(uShift, 3, uBits, B, G, R, A)){
						return Graphic::BufferFormat::B8G8R8X8;
					}
				}
				break;

			case 24:
				if(CheckSize(uBits, 3, 8, 8, 8, 0)){
					if(CheckSeq(uShift, 3, uBits, R, G, B, A)){
						return Graphic::BufferFormat::R8G8B8;
					}
					if(CheckSeq(uShift, 3, uBits, B, G, R, A)){
						return Graphic::BufferFormat::B8G8R8;
					}
				}
				break;
				
			default:
				return Graphic::BufferFormat::Unknown;
			}
			return Graphic::BufferFormat::Unknown;
		}

		const Graphic::BufferFormat	ToColorBufferFormat(const PIXELFORMATDESCRIPTOR& pfd){
			const uint8 uBits[] = {
				pfd.cRedBits,
				pfd.cGreenBits,
				pfd.cBlueBits,
				pfd.cAlphaBits
			};
			const uint8 uShift[] = {
				pfd.cRedShift,
				pfd.cGreenShift,
				pfd.cBlueShift,
				pfd.cAlphaShift
			};

			return ToColorBufferFormat(uBits, uShift, pfd.cColorBits);
		}

		void	SetPixelFormat(PIXELFORMATDESCRIPTOR& pfd, const uint32 uDepthBits, const uint32 uStencilBits){
			pfd.cDepthBits = uDepthBits;
			pfd.cStencilBits = uStencilBits;
		}

		void	SetPixelFormat(PIXELFORMATDESCRIPTOR& pfd, const uint32 uColorBits, const uint32 uR, const uint32 uG, const uint32 uB, const uint32 uA, const uint32 uRS, const uint32 uGS, const uint32 uBS, const uint32 uAS){
			pfd.cColorBits = uColorBits;
			pfd.cRedBits = uR;
			pfd.cRedShift = uRS;
			pfd.cGreenBits = uG;
			pfd.cGreenShift = uGS;
			pfd.cBlueBits = uB;
			pfd.cBlueShift = uBS;
			pfd.cAlphaBits = uA;
			pfd.cAlphaShift = uAS;
		}

		void	SetPixelFormat(PIXELFORMATDESCRIPTOR& pfd, const Graphic::BufferFormat uFormat){
			switch(uFormat){
				
				//	Depth Components
			case Graphic::BufferFormat::D16:		SetPixelFormat(pfd, 16, 0);	break;
			case Graphic::BufferFormat::D24:		SetPixelFormat(pfd, 24, 0);	break;
			case Graphic::BufferFormat::D24X8:		SetPixelFormat(pfd, 24, 0); break;
			case Graphic::BufferFormat::D24S8:		SetPixelFormat(pfd, 24, 8);	break;
			case Graphic::BufferFormat::D32:		SetPixelFormat(pfd, 32, 0);	break;
			case Graphic::BufferFormat::D32S8X24:	SetPixelFormat(pfd, 32, 8);	break;

			case Graphic::BufferFormat::D32F:		
			case Graphic::BufferFormat::D32FS8X24U:
				CR_THROW(L"Cannot set to float an legacy pixel format: " + String::ToString(uFormat));

			case Graphic::BufferFormat::R8:			SetPixelFormat(pfd, 8, 8, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::A8:			SetPixelFormat(pfd, 8, 0, 0, 0, 8, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R16:		SetPixelFormat(pfd, 16, 16, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R32:		SetPixelFormat(pfd, 32, 32, 0, 0, 0, 0, 0, 0, 0);	break;

			case Graphic::BufferFormat::R16F:		
			case Graphic::BufferFormat::R32F:		
				CR_THROW(L"Cannot set to float an legacy pixel format: " + String::ToString(uFormat));
			
			case Graphic::BufferFormat::R8G8:		SetPixelFormat(pfd, 16, 8, 0, 8, 0, 0, 8, 0, 0);	break;
			case Graphic::BufferFormat::R16G16:		SetPixelFormat(pfd, 32, 16, 0, 16, 0, 0, 16, 0, 0);	break;
			case Graphic::BufferFormat::R32G32:		SetPixelFormat(pfd, 64, 32, 0, 32, 0, 0, 32, 0, 0);	break;

			case Graphic::BufferFormat::R16G16F:	
			case Graphic::BufferFormat::R32G32F:		
				CR_THROW(L"Cannot set to float an legacy pixel format: " + String::ToString(uFormat));
				
			case Graphic::BufferFormat::B8G8R8:			SetPixelFormat(pfd, 24, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::R8G8B8:			SetPixelFormat(pfd, 24, 8, 8, 8, 0, 0, 8, 16, 0);	break;
			case Graphic::BufferFormat::R8G8B8_sRGB:	SetPixelFormat(pfd, 24, 8, 8, 8, 0, 0, 8, 16, 0);	break;
			case Graphic::BufferFormat::R16G16B16:		SetPixelFormat(pfd, 48, 16, 16, 16, 0, 0, 16, 32, 0);	break;
			case Graphic::BufferFormat::R32G32B32:		SetPixelFormat(pfd, 96, 32, 32, 32, 0, 0, 32, 64, 96);	break;

			case Graphic::BufferFormat::R16G16B16F:	
			case Graphic::BufferFormat::R32G32B32F:	
				CR_THROW(L"Cannot set to float an legacy pixel format: " + String::ToString(uFormat));				

			case Graphic::BufferFormat::B8G8R8A8:		SetPixelFormat(pfd, 32, 8, 8, 8, 8, 16, 8, 0, 24);	break;
			case Graphic::BufferFormat::B8G8R8A8_sRGB:	SetPixelFormat(pfd, 32, 8, 8, 8, 8, 16, 8, 0, 24);	break;
			case Graphic::BufferFormat::B8G8R8X8:		SetPixelFormat(pfd, 32, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::B8G8R8X8_sRGB:	SetPixelFormat(pfd, 32, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::R8G8B8A8:		SetPixelFormat(pfd, 32, 8, 8, 8, 8, 0, 8, 16, 24);	break;
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	SetPixelFormat(pfd, 32, 8, 8, 8, 8, 0, 8, 16, 24);	break;
			case Graphic::BufferFormat::R16G16B16A16:	SetPixelFormat(pfd, 64, 16, 16, 16, 16, 0, 16, 32, 48);	break;
			case Graphic::BufferFormat::R32G32B32A32:	SetPixelFormat(pfd, 128, 32, 32, 32, 32, 0, 32, 64, 96);	break;

			case Graphic::BufferFormat::R16G16B16A16F:	
			case Graphic::BufferFormat::R32G32B32A32F:	
				CR_THROW(L"Cannot set to float an legacy pixel format: " + String::ToString(uFormat));				

			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Unknown buffer format to pixel format.", CR_INFO());
			}
		}

		void	SetPixelFormat(Collection::CList<int32>& Attribs, const uint32 uDepthBits, const uint32 uStencilBits){
			Attribs.Add(WGL::WGL_DEPTH_BITS);
			Attribs.Add(uDepthBits);

			Attribs.Add(WGL::WGL_STENCIL_BITS);
			Attribs.Add(uStencilBits);
		}

		void	SetPixelFormat(Collection::CList<int32>& Attribs, const uint32 uColorBits, const uint32 uR, const uint32 uG, const uint32 uB, const uint32 uA, const uint32 uRS, const uint32 uGS, const uint32 uBS, const uint32 uAS){
			Attribs.Add(WGL::WGL_COLOR_BITS);
			Attribs.Add(uColorBits);

			Attribs.Add(WGL::WGL_RED_SHIFT);
			Attribs.Add(uRS);

			Attribs.Add(WGL::WGL_GREEN_SHIFT);
			Attribs.Add(uGS);

			Attribs.Add(WGL::WGL_BLUE_SHIFT);
			Attribs.Add(uBS);

			Attribs.Add(WGL::WGL_ALPHA_SHIFT);
			Attribs.Add(uAS);

			Attribs.Add(WGL::WGL_RED_BITS);
			Attribs.Add(uR);

			Attribs.Add(WGL::WGL_GREEN_BITS);
			Attribs.Add(uG);

			Attribs.Add(WGL::WGL_BLUE_BITS);
			Attribs.Add(uB);

			Attribs.Add(WGL::WGL_ALPHA_BITS);
			Attribs.Add(uA);
		}

		void	SetPixelFormat(Collection::CList<int32>& Attribs, const Graphic::BufferFormat uFormat){
			switch(uFormat){
				//	Depth Components
			case Graphic::BufferFormat::D16:		SetPixelFormat(Attribs, 16, 0);	break;
			case Graphic::BufferFormat::D24:		SetPixelFormat(Attribs, 24, 0);	break;
			case Graphic::BufferFormat::D24X8:		SetPixelFormat(Attribs, 24, 0); break;
			case Graphic::BufferFormat::D24S8:		SetPixelFormat(Attribs, 24, 8);	break;
			case Graphic::BufferFormat::D32:		SetPixelFormat(Attribs, 32, 0);	break;
			case Graphic::BufferFormat::D32S8X24:	SetPixelFormat(Attribs, 32, 8);	break;

			case Graphic::BufferFormat::D32F:		
			case Graphic::BufferFormat::D32FS8X24U:
				CR_THROW(L"Cannot set to float an pixel format: " + String::ToString(uFormat));

			case Graphic::BufferFormat::R8:			SetPixelFormat(Attribs, 8, 8, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::A8:			SetPixelFormat(Attribs, 8, 0, 0, 0, 8, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R16:		SetPixelFormat(Attribs, 16, 16, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R32:		SetPixelFormat(Attribs, 32, 32, 0, 0, 0, 0, 0, 0, 0);	break;

			case Graphic::BufferFormat::R16F:		
			case Graphic::BufferFormat::R32F:		
				CR_THROW(L"Cannot set to float an pixel format: " + String::ToString(uFormat));
			
			case Graphic::BufferFormat::R8G8:		SetPixelFormat(Attribs, 16, 8, 0, 8, 0, 0, 8, 0, 0);	break;
			case Graphic::BufferFormat::R16G16:		SetPixelFormat(Attribs, 32, 16, 0, 16, 0, 0, 16, 0, 0);	break;
			case Graphic::BufferFormat::R32G32:		SetPixelFormat(Attribs, 64, 32, 0, 32, 0, 0, 32, 0, 0);	break;

			case Graphic::BufferFormat::R16G16F:	
			case Graphic::BufferFormat::R32G32F:		
				CR_THROW(L"Cannot set to float an pixel format: " + String::ToString(uFormat));
				
			case Graphic::BufferFormat::B8G8R8:			SetPixelFormat(Attribs, 24, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::R8G8B8:			SetPixelFormat(Attribs, 24, 8, 8, 8, 0, 0, 8, 16, 0);	break;
			case Graphic::BufferFormat::R8G8B8_sRGB:	SetPixelFormat(Attribs, 24, 8, 8, 8, 0, 0, 8, 16, 0);	break;
			case Graphic::BufferFormat::R16G16B16:		SetPixelFormat(Attribs, 48, 16, 16, 16, 0, 0, 16, 32, 0);	break;
			case Graphic::BufferFormat::R32G32B32:		SetPixelFormat(Attribs, 96, 32, 32, 32, 0, 0, 32, 64, 96);	break;

			case Graphic::BufferFormat::R16G16B16F:	
			case Graphic::BufferFormat::R32G32B32F:	
				CR_THROW(L"Cannot set to float an pixel format: " + String::ToString(uFormat));				

			case Graphic::BufferFormat::B8G8R8A8:		SetPixelFormat(Attribs, 32, 8, 8, 8, 8, 16, 8, 0, 24);	break;
			case Graphic::BufferFormat::B8G8R8A8_sRGB:	SetPixelFormat(Attribs, 32, 8, 8, 8, 8, 16, 8, 0, 24);	break;
			case Graphic::BufferFormat::B8G8R8X8:		SetPixelFormat(Attribs, 32, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::B8G8R8X8_sRGB:	SetPixelFormat(Attribs, 32, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::R8G8B8A8:		SetPixelFormat(Attribs, 32, 8, 8, 8, 8, 0, 8, 16, 24);	break;
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	SetPixelFormat(Attribs, 32, 8, 8, 8, 8, 0, 8, 16, 24);	break;
			case Graphic::BufferFormat::R16G16B16A16:	SetPixelFormat(Attribs, 64, 16, 16, 16, 16, 0, 16, 32, 48);	break;
			case Graphic::BufferFormat::R32G32B32A32:	SetPixelFormat(Attribs, 128, 32, 32, 32, 32, 0, 32, 64, 96);	break;

			case Graphic::BufferFormat::R16G16B16A16F:	
			case Graphic::BufferFormat::R32G32B32A32F:	
				CR_THROW(L"Cannot set to float an pixel format: " + String::ToString(uFormat));				

			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Unknown buffer format to pixel format.", CR_INFO());
			}
		}


		const GLenum	ToBufferUsage(const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess){
			switch(uUsage)
			{
			case Graphic::BufferUsage::Static:
				switch (uAccess)
				{
				case Graphic::BufferAccess::Read:			return GL::GL_STATIC_READ;
				case Graphic::BufferAccess::Write:			return GL::GL_STATIC_DRAW;
				case Graphic::BufferAccess::ReadAndWrite:	return GL::GL_STATIC_COPY;
				}
				break;

			case Graphic::BufferUsage::Stream:
				switch (uAccess)
				{
				case Graphic::BufferAccess::Read:			return GL::GL_STREAM_READ;
				case Graphic::BufferAccess::Write:			return GL::GL_STREAM_DRAW;
				case Graphic::BufferAccess::ReadAndWrite:	return GL::GL_STATIC_COPY;
				}
				break;

			case Graphic::BufferUsage::Dynamic:
				switch (uAccess)
				{
				case Graphic::BufferAccess::Read:			return GL::GL_DYNAMIC_READ;
				case Graphic::BufferAccess::Write:			return GL::GL_DYNAMIC_DRAW;
				case Graphic::BufferAccess::ReadAndWrite:	return GL::GL_DYNAMIC_COPY;
				}
				break;
			}

			throw Exception::CInvalidArgumentException(L"uUsage & uAccess", 
				String::ToString(uUsage) + L" & " + String::ToString(uAccess),
				L"Invalid combination for buffer usage conversion.", CR_INFO());
		}

		const GLenum	ToVertexType(const Graphic::VertexType uType){
			switch (uType)
			{
			case Graphic::VertexType::Float:	return GL::GL_FLOAT;
			case Graphic::VertexType::Color32b:	return GL::GL_UNSIGNED_INT;

			default:
				throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
					L"Invalid vertex type.", CR_INFO());
			}
		}

		const uint32	ToVertexTypeNumber(const Graphic::VertexType uType){
			switch (uType)
			{
			case Graphic::VertexType::Float:	return 1;
			case Graphic::VertexType::Color32b:	return 4;

			default:
				throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
					L"Invalid vertex type.", CR_INFO());				
			}
		}

		const Graphic::VertexType	ToVertexType(const GLenum uType, const uint32 uNumber){
			CR_THROWNOTIMPLEMENTED();
		}

		const GLenum ToCompareFunc(const Graphic::CompareFunc uFunc){
			switch (uFunc)
			{
			case Graphic::CompareFunc::Always:		return GL::GL_ALWAYS;
			case Graphic::CompareFunc::Equal:		return GL::GL_EQUAL;
			case Graphic::CompareFunc::Greater:		return GL::GL_GREATER;
			case Graphic::CompareFunc::GreaterEqual:	return GL::GL_GEQUAL;
			case Graphic::CompareFunc::Less:		return GL::GL_LESS;
			case Graphic::CompareFunc::LessEqual:	return GL::GL_LEQUAL;
			case Graphic::CompareFunc::Never:		return GL::GL_NEVER;
			case Graphic::CompareFunc::NotEqual:	return GL::GL_NOTEQUAL;
			default:
				throw Exception::CInvalidArgumentException(L"uFunc", String::ToString(uFunc),
					L"Unknown compare func value.", CR_INFO());
			}
		}

		const GLenum	ToStencilOp(const Graphic::StencilOperation uOp){
			switch (uOp)
			{
			case Graphic::StencilOperation::Decr:		return GL::GL_DECR;
			case Graphic::StencilOperation::Decr_Wrap:	return GL::GL_DECR_WRAP;
			case Graphic::StencilOperation::Incr:		return GL::GL_INCR;
			case Graphic::StencilOperation::Incr_Wrap:	return GL::GL_INCR_WRAP;
			case Graphic::StencilOperation::Invert:		return GL::GL_INVERT;
			case Graphic::StencilOperation::Keep:		return GL::GL_KEEP;
			case Graphic::StencilOperation::Replace:	return GL::GL_REPLACE;
			case Graphic::StencilOperation::Zero:		return GL::GL_ZERO;

			default:
				throw Exception::CInvalidArgumentException(L"uOp", String::ToString(uOp),
					L"Unknwon stencil operation.", CR_INFO());
			}
		}

		const GLenum	ToBlendEquation(const Graphic::BlendOperation uOp){
			switch (uOp){
			case Graphic::BlendOperation::Add:	return GL::GL_FUNC_ADD;
			case Graphic::BlendOperation::Max:	return GL::GL_MAX;
			case Graphic::BlendOperation::Min:	return GL::GL_MIN;
			case Graphic::BlendOperation::Sub:	return GL::GL_FUNC_SUBTRACT;
			case Graphic::BlendOperation::Sub_Reverse:	return GL::GL_FUNC_REVERSE_SUBTRACT;

			default:
				throw Exception::CInvalidArgumentException(L"uOp", String::ToString(uOp),
					L"Unknown blend operation.", CR_INFO());
			}
		}

		const GLenum ToBlendOption(const Graphic::BlendOption uOption){
			switch (uOption){
			case Graphic::BlendOption::DestAlpha:			return GL::GL_DST_ALPHA;
			case Graphic::BlendOption::DestColor:			return GL::GL_DST_COLOR;
			case Graphic::BlendOption::One:					return GL::GL_ONE;
			case Graphic::BlendOption::OneMinusDestAlpha:	return GL::GL_ONE_MINUS_DST_ALPHA;
			case Graphic::BlendOption::OneMinusDestColor:	return GL::GL_ONE_MINUS_DST_COLOR;
			case Graphic::BlendOption::OneMinusSourceAlpha:	return GL::GL_ONE_MINUS_SRC_ALPHA;
			case Graphic::BlendOption::OneMinusSourceColor:	return GL::GL_ONE_MINUS_SRC_COLOR;
			case Graphic::BlendOption::SourceAlpha:			return GL::GL_SRC_ALPHA;
			case Graphic::BlendOption::SourceColor:			return GL::GL_SRC_COLOR;
			case Graphic::BlendOption::Zero:				return GL::GL_ZERO;
				
			default:
				throw Exception::CInvalidArgumentException(L"uOption", String::ToString(uOption),
					L"Unknown blending operator.", CR_INFO());
			}
		}


		const GLenum	ToInternalFormat(const Graphic::BufferFormat uFormat, const Graphic::FeatureLevel uLevel){
			switch (uLevel){
			case Graphic::FeatureLevel::Level_1:
			case Graphic::FeatureLevel::Level_2:
				switch (uFormat){
					//	One Component
				case Graphic::BufferFormat::A8:				return GL::GL_ALPHA8;		// 1.1
				case Graphic::BufferFormat::R8:				return GL::GL_LUMINANCE8;	// 1.1	
				case Graphic::BufferFormat::R16:			return GL::GL_LUMINANCE16;	// 1.1

					// Two Components
				case Graphic::BufferFormat::R8G8:			return GL::GL_LUMINANCE8_ALPHA8;		// 1.1
				case Graphic::BufferFormat::R16G16:			return GL::GL_LUMINANCE16_ALPHA16;		// 1.1
				}
				break;

			case Graphic::FeatureLevel::Level_3:
			case Graphic::FeatureLevel::Level_4:
				switch (uFormat){
					//	One Component
				case Graphic::BufferFormat::A8:				return GL::GL_ALPHA;	// 1.0
				case Graphic::BufferFormat::R8:				return GL::GL_R8;		// 3.0	
				case Graphic::BufferFormat::R16:			return GL::GL_R16;		// 3.0
				case Graphic::BufferFormat::R16F:			return GL::GL_R16F;		// 3.0
				case Graphic::BufferFormat::R32:			return GL::GL_R32UI;	// 3.0
				case Graphic::BufferFormat::R32F:			return GL::GL_R32F;		// 3.0

					// Two Components
				case Graphic::BufferFormat::R8G8:			return GL::GL_RG8;		// 3.0
				case Graphic::BufferFormat::R16G16:			return GL::GL_RG16;		// 3.0
				case Graphic::BufferFormat::R16G16F:		return GL::GL_RG16F;	// 3.0
				case Graphic::BufferFormat::R32G32:			return GL::GL_RG32UI;	// 3.0
				case Graphic::BufferFormat::R32G32F:		return GL::GL_RG32F;	// 3.0
				}
				break;
			}
			switch (uFormat)
			{
				//	Depth Components
			case Graphic::BufferFormat::D16:	return GL::GL_DEPTH_COMPONENT16;	// 1.4
			case Graphic::BufferFormat::D24:	return GL::GL_DEPTH_COMPONENT24;	// 1.4
			case Graphic::BufferFormat::D32:	return GL::GL_DEPTH_COMPONENT32;	// 1.4

				// Three Components
			case Graphic::BufferFormat::B8G8R8:			return GL::GL_BGR;		// 1.2
			case Graphic::BufferFormat::R8G8B8:			return GL::GL_RGB8;		// 1.1
			case Graphic::BufferFormat::R8G8B8_sRGB:	return GL::GL_SRGB8;	// 2.1
			case Graphic::BufferFormat::R16G16B16:		return GL::GL_RGB16;	// 1.1
			case Graphic::BufferFormat::R16G16B16F:		return GL::GL_RGB16F;	// 3.0
			case Graphic::BufferFormat::R32G32B32:		return GL::GL_RGB32UI;	// 3.0
			case Graphic::BufferFormat::R32G32B32F:		return GL::GL_RGB32F;	// 3.0

				//	Four Components
			case Graphic::BufferFormat::B8G8R8A8:		return GL::GL_BGRA;		// 1.2
			case Graphic::BufferFormat::R8G8B8A8:		return GL::GL_RGBA8;	// 1.1
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	return GL::GL_SRGB8_ALPHA8;	// 2.1;
			case Graphic::BufferFormat::R16G16B16A16:	return GL::GL_RGBA16;	// 1.1
			case Graphic::BufferFormat::R16G16B16A16F:	return GL::GL_RGBA16F;	// 3.0
			case Graphic::BufferFormat::R32G32B32A32:	return GL::GL_RGBA32UI;	// 3.0
			case Graphic::BufferFormat::R32G32B32A32F:	return GL::GL_RGBA32F;	// 3.0

			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Unsupported buffor format.", CR_INFO());
			}
		}

		const GLenum	ToTransferFormat(const Graphic::BufferFormat uFormat, const Graphic::FeatureLevel uLevel){
			switch (uLevel){
			case Graphic::FeatureLevel::Level_1:
			case Graphic::FeatureLevel::Level_2:
				switch (uFormat){
					//	One Component
				case Graphic::BufferFormat::A8:				return GL::GL_ALPHA;		// 1.1
				case Graphic::BufferFormat::R8:				return GL::GL_LUMINANCE;	// 1.1	
				case Graphic::BufferFormat::R16:			return GL::GL_LUMINANCE;	// 1.1

					// Two Components
				case Graphic::BufferFormat::R8G8:			return GL::GL_LUMINANCE_ALPHA;		// 1.1
				case Graphic::BufferFormat::R16G16:			return GL::GL_LUMINANCE_ALPHA;		// 1.1
				}
				break;

			case Graphic::FeatureLevel::Level_3:
			case Graphic::FeatureLevel::Level_4:
				switch (uFormat){
					//	One Component
				case Graphic::BufferFormat::A8:				return GL::GL_ALPHA;	// 1.1
				case Graphic::BufferFormat::R8:				return GL::GL_RED;	// 1.1	
				case Graphic::BufferFormat::R16:			return GL::GL_RED;	// 1.1
				case Graphic::BufferFormat::R16F:			return GL::GL_RED;	// 1.1
				case Graphic::BufferFormat::R32:			return GL::GL_RED;	// 1.1
				case Graphic::BufferFormat::R32F:			return GL::GL_RED;	// 1.1

					// Two Components
				case Graphic::BufferFormat::R8G8:			return GL::GL_RG;	// 3.0
				case Graphic::BufferFormat::R16G16:			return GL::GL_RG;	// 3.0
				case Graphic::BufferFormat::R16G16F:		return GL::GL_RG;	// 3.0
				case Graphic::BufferFormat::R32G32:			return GL::GL_RG;	// 3.0
				case Graphic::BufferFormat::R32G32F:		return GL::GL_RG;	// 3.0
				}
				break;
			}
			switch(uFormat){
				//	Depth Components
			case Graphic::BufferFormat::D16:	return GL::GL_DEPTH_COMPONENT;	// 1.4
			case Graphic::BufferFormat::D24:	return GL::GL_DEPTH_COMPONENT;	// 1.4
			case Graphic::BufferFormat::D32:	return GL::GL_DEPTH_COMPONENT;	// 1.4

				// Three Components
			case Graphic::BufferFormat::B8G8R8:			return GL::GL_BGR;	// 1.2
			case Graphic::BufferFormat::R8G8B8:			return GL::GL_RGB;	// 1.1
			case Graphic::BufferFormat::R8G8B8_sRGB:	return GL::GL_RGB;	// 1.1
			case Graphic::BufferFormat::R16G16B16:		return GL::GL_RGB;	// 1.1
			case Graphic::BufferFormat::R16G16B16F:		return GL::GL_RGB;	// 1.1
			case Graphic::BufferFormat::R32G32B32:		return GL::GL_RGB;	// 1.1
			case Graphic::BufferFormat::R32G32B32F:		return GL::GL_RGB;	// 1.1

				//	Four Components
			case Graphic::BufferFormat::B8G8R8A8:		return GL::GL_BGRA;	// 1.2
			case Graphic::BufferFormat::R8G8B8A8:		return GL::GL_RGBA;	// 1.1
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	return GL::GL_RGBA;	// 1.1
			case Graphic::BufferFormat::R16G16B16A16:	return GL::GL_RGBA;	// 1.1
			case Graphic::BufferFormat::R16G16B16A16F:	return GL::GL_RGBA;	// 1.1
			case Graphic::BufferFormat::R32G32B32A32:	return GL::GL_RGBA;	// 1.1
			case Graphic::BufferFormat::R32G32B32A32F:	return GL::GL_RGBA;	// 1.1

			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Unsupported buffor format.", CR_INFO());
			}
		}

		const GLenum	ToTransferType(const Graphic::BufferFormat uFormat, const Graphic::FeatureLevel uLevel){
			switch (uLevel){
			case Graphic::FeatureLevel::Level_1:
			case Graphic::FeatureLevel::Level_2:
				switch (uFormat){
					//	One Component
				case Graphic::BufferFormat::A8:				return GL::GL_UNSIGNED_BYTE;	// 1.1
				case Graphic::BufferFormat::R8:				return GL::GL_UNSIGNED_BYTE;	// 1.1	
				case Graphic::BufferFormat::R16:			return GL::GL_UNSIGNED_SHORT;	// 1.1

					// Two Components
				case Graphic::BufferFormat::R8G8:			return GL::GL_LUMINANCE_ALPHA;		// 1.1
				case Graphic::BufferFormat::R16G16:			return GL::GL_LUMINANCE_ALPHA;		// 1.1
				}
				break;

			case Graphic::FeatureLevel::Level_3:
			case Graphic::FeatureLevel::Level_4:
				switch (uFormat){
					//	One Component
				case Graphic::BufferFormat::A8:				return GL::GL_UNSIGNED_BYTE;	// 1.1
				case Graphic::BufferFormat::R8:				return GL::GL_UNSIGNED_BYTE;	// 1.1	
				case Graphic::BufferFormat::R16:			return GL::GL_UNSIGNED_SHORT;	// 1.1
				case Graphic::BufferFormat::R16F:			return GL::GL_HALF_FLOAT;	// 3.0
				case Graphic::BufferFormat::R32:			return GL::GL_UNSIGNED_INT;	// 1.1
				case Graphic::BufferFormat::R32F:			return GL::GL_FLOAT;	// 1.1

					// Two Components
				case Graphic::BufferFormat::R8G8:			return GL::GL_UNSIGNED_BYTE;	// 1.1
				case Graphic::BufferFormat::R16G16:			return GL::GL_UNSIGNED_SHORT;	// 1.1
				case Graphic::BufferFormat::R16G16F:		return GL::GL_HALF_FLOAT;	// 3.0
				case Graphic::BufferFormat::R32G32:			return GL::GL_UNSIGNED_INT;	// 1.1
				case Graphic::BufferFormat::R32G32F:		return GL::GL_FLOAT;	// 1.1
				}
				break;
			}
			switch(uFormat){
				//	Depth Components
			case Graphic::BufferFormat::D16:	return GL::GL_UNSIGNED_SHORT;	// 1.1
			case Graphic::BufferFormat::D24:	return GL::GL_UNSIGNED_INT;	// 1.1
			case Graphic::BufferFormat::D32:	return GL::GL_UNSIGNED_INT;	// 1.1

				// Three Components
			case Graphic::BufferFormat::B8G8R8:			return GL::GL_UNSIGNED_BYTE;	// 1.1
			case Graphic::BufferFormat::R8G8B8:			return GL::GL_UNSIGNED_BYTE;	// 1.1
			case Graphic::BufferFormat::R8G8B8_sRGB:	return GL::GL_UNSIGNED_BYTE;	// 1.1
			case Graphic::BufferFormat::R16G16B16:		return GL::GL_UNSIGNED_SHORT;	// 1.1
			case Graphic::BufferFormat::R16G16B16F:		return GL::GL_HALF_FLOAT;		// 3.0
			case Graphic::BufferFormat::R32G32B32:		return GL::GL_UNSIGNED_INT;	// 1.1
			case Graphic::BufferFormat::R32G32B32F:		return GL::GL_FLOAT;	// 1.1

				//	Four Components
			case Graphic::BufferFormat::B8G8R8A8:		return GL::GL_UNSIGNED_BYTE;	// 1.1
			case Graphic::BufferFormat::R8G8B8A8:		return GL::GL_UNSIGNED_BYTE;	// 1.1
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	return GL::GL_UNSIGNED_BYTE;	// 1.1
			case Graphic::BufferFormat::R16G16B16A16:	return GL::GL_UNSIGNED_SHORT;	// 1.1
			case Graphic::BufferFormat::R16G16B16A16F:	return GL::GL_HALF_FLOAT;	// 3.0
			case Graphic::BufferFormat::R32G32B32A32:	return GL::GL_UNSIGNED_INT;	// 1.1
			case Graphic::BufferFormat::R32G32B32A32F:	return GL::GL_FLOAT;	// 1.1

			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Unsupported buffor format.", CR_INFO());
			}
		}


		const GLenum	ToTargetBinding(const GLenum uTarget){
			switch (uTarget){
			case GL::GL_TEXTURE_1D:			return GL::GL_TEXTURE_BINDING_1D;
			case GL::GL_TEXTURE_2D:			return GL::GL_TEXTURE_BINDING_2D;
			case GL::GL_TEXTURE_3D:			return GL::GL_TEXTURE_BINDING_3D;
			case GL::GL_TEXTURE_CUBE_MAP:	return GL::GL_TEXTURE_BINDING_CUBE_MAP;

			case GL::GL_ELEMENT_ARRAY_BUFFER:	return GL::GL_ELEMENT_ARRAY_BUFFER_BINDING;
			case GL::GL_ARRAY_BUFFER:		return GL::GL_ARRAY_BUFFER_BINDING;

			case GL::GL_FRAMEBUFFER:		return GL::GL_FRAMEBUFFER_BINDING;
			default:
				throw Exception::CInvalidArgumentException(L"uTarget", String::ToString((uint32)uTarget),
					L"Unknown target for binding mapping.", CR_INFO());
			}
		}

		const GLenum ToTextureMinFilter(const Graphic::TextureFilter uFilter){
			switch (uFilter){
			case Graphic::TextureFilter::Nearest:	return GL::GL_NEAREST;
			case Graphic::TextureFilter::Linear:	return GL::GL_LINEAR;
			default:
				throw Exception::CInvalidArgumentException(L"uFilter", String::ToString(uFilter),
					L"Unknown filter value.", CR_INFO());
			}
		}
		
		const GLenum ToTextureMagFilter(const Graphic::TextureFilter uFilter, const Graphic::TextureFilter uMipmap){
			if(uMipmap == Graphic::TextureFilter::None){
				return ToTextureMinFilter(uFilter);
			}

			switch (uFilter)
			{
			case Graphic::TextureFilter::Nearest:	
				switch (uMipmap)
				{
				case Graphic::TextureFilter::Nearest:	return GL::GL_NEAREST_MIPMAP_NEAREST;
				case Graphic::TextureFilter::Linear:	return GL::GL_NEAREST_MIPMAP_LINEAR;
				default:
					throw Exception::CInvalidArgumentException(L"uMipmap", String::ToString(uMipmap),
						L"Unknown mipmap filter value.", CR_INFO());
				}

			case Graphic::TextureFilter::Linear:	
				switch (uMipmap)
				{
				case Graphic::TextureFilter::Nearest:	return GL::GL_LINEAR_MIPMAP_NEAREST;
				case Graphic::TextureFilter::Linear:	return GL::GL_LINEAR_MIPMAP_LINEAR;
				default:
					throw Exception::CInvalidArgumentException(L"uMipmap", String::ToString(uMipmap),
						L"Unknown mipmap filter value.", CR_INFO());
				}

			default:
				throw Exception::CInvalidArgumentException(L"uFilter", String::ToString(uFilter),
					L"Unknown filter value.", CR_INFO());
			}
		}

		const GLenum ToTextureWrap(const Graphic::TextureWrap uWrap){
			switch (uWrap){
			case Graphic::TextureWrap::Clamp:		return GL::GL_CLAMP_TO_BORDER;
			case Graphic::TextureWrap::ClampToEdge:	return GL::GL_CLAMP_TO_EDGE;
			case Graphic::TextureWrap::Repeat:		return GL::GL_REPEAT;
			case Graphic::TextureWrap::Mirror:		return GL::GL_MIRRORED_REPEAT;
			default:
				throw Exception::CInvalidArgumentException(L"uWrap", String::ToString(uWrap),
					L"Invalid texture wrap coord value.", CR_INFO());
			}
		}


		const uint32	GetTypeSize(const GLenum uType){
			switch (uType)
			{
			case GL::GL_BYTE:
			case GL::GL_UNSIGNED_BYTE:	return 1;

			case GL::GL_SHORT:
			case GL::GL_UNSIGNED_SHORT:	return 2;

			case GL::GL_INT:
			case GL::GL_UNSIGNED_INT:
			case GL::GL_FLOAT:	return 4;

			default:
				throw Exception::CInvalidArgumentException(L"uType", String::FromUInt32(uType),
					L"Unknown opengl data type.", CR_INFO());
			}
		}

		const bool	GetVersion(const CString& strVersion, uint32& uOutMajorVersion, uint32& uOutMinorVersion){
			uint32 uDotPos = 0;
			if(strVersion.Find(L".", uDotPos)){
				uint32 uDot2Pos = 0;
				uint32 uWPos = 0;

				if(strVersion.Find(L".", uDotPos + 1, uDot2Pos) && strVersion.Find(L" ", uDotPos + 1, uWPos)){
					if(uDot2Pos < uWPos){
						if(String::ToUInt32(strVersion.SubString(0, uDotPos), uOutMajorVersion) && 
							String::ToUInt32(strVersion.SubStringIndexed(uDotPos+1, uDot2Pos), uOutMinorVersion)){
							return true;
						}
					}
					else{
						if(String::ToUInt32(strVersion.SubString(0, uDotPos), uOutMajorVersion) && 
							String::ToUInt32(strVersion.SubStringIndexed(uDotPos+1, uWPos), uOutMinorVersion)){
							return true;
						}
					}
				}
				else if(strVersion.Find(L".", uDotPos + 1, uDot2Pos)){
					if(String::ToUInt32(strVersion.SubString(0, uDotPos), uOutMajorVersion) && 
						String::ToUInt32(strVersion.SubStringIndexed(uDotPos+1, uDot2Pos), uOutMinorVersion)){
						return true;
					}
				}
				else if(strVersion.Find(L" ", uDotPos + 1, uWPos)){
					if(String::ToUInt32(strVersion.SubString(0, uDotPos), uOutMajorVersion) && 
						String::ToUInt32(strVersion.SubStringIndexed(uDotPos+1, uWPos), uOutMinorVersion)){
						return true;
					}
				}
				else{
					if(String::ToUInt32(strVersion.SubString(0, uDotPos), uOutMajorVersion) && 
						String::ToUInt32(strVersion.SubString(uDotPos+1), uOutMinorVersion)){
						return true;
					}
				}
			}
			return false;
		}
	}
}