#include "../Internal/Utils.h"
#include "../../GraphicMngInterface/Include/GraphicDriver_Strings.h"

namespace CB{
	namespace GLUtils{
		const uint32	GetBitsPerPixel(const Graphic::BufferFormat uFormat){
			switch(uFormat){
			case Graphic::BufferFormat::R1:			
				return 1;

			case Graphic::BufferFormat::R8:			
			case Graphic::BufferFormat::A8:			
				return 8;

			case Graphic::BufferFormat::R16:
			case Graphic::BufferFormat::R16F:		
				return 16;

			case Graphic::BufferFormat::R32:		
			case Graphic::BufferFormat::R32F:		
				return 32;

			case Graphic::BufferFormat::R8G8:				
				return 16;

			case Graphic::BufferFormat::R16G16:		
			case Graphic::BufferFormat::R16G16F:	
				return 32;

			case Graphic::BufferFormat::R32G32:		
			case Graphic::BufferFormat::R32G32F:		
				return 64;

			case Graphic::BufferFormat::B8G8R8A8:		
			case Graphic::BufferFormat::B8G8R8A8_sRGB:	
			case Graphic::BufferFormat::B8G8R8X8:		
			case Graphic::BufferFormat::B8G8R8X8_sRGB:	
			case Graphic::BufferFormat::R8G8B8A8:		
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	
				return 32;

			case Graphic::BufferFormat::R16G16B16A16:	
			case Graphic::BufferFormat::R16G16B16A16F:
				return 64;

			case Graphic::BufferFormat::R32G32B32A32:	
			case Graphic::BufferFormat::R32G32B32A32F:
				return 128;

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
						//
					}
					if(CheckSeq(uShift, 3, uBits, B, G, R, A)){
						return Graphic::BufferFormat::B8G8R8X8;
					}
				}
				break;

			case 24:
				if(CheckSize(uBits, 3, 8, 8, 8, 0)){
					if(CheckSeq(uShift, 3, uBits, R, G, B, A)){
						//
					}
					if(CheckSeq(uShift, 3, uBits, B, G, R, A)){
						return Graphic::BufferFormat::B8G8R8X8;
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
			case Graphic::BufferFormat::D16:		SetPixelFormat(pfd, 16, 0);	break;
			case Graphic::BufferFormat::D24X8:		SetPixelFormat(pfd, 24, 0); break;
			case Graphic::BufferFormat::D24S8:		SetPixelFormat(pfd, 24, 8);	break;
			case Graphic::BufferFormat::D32F:		
			case Graphic::BufferFormat::D32FS8X24U:
				throw Exception::CException(L"Cannot set float pixel format: " + String::ToString(uFormat), CR_INFO());

			case Graphic::BufferFormat::R1:			SetPixelFormat(pfd, 1, 1, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R8:			SetPixelFormat(pfd, 8, 8, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::A8:			SetPixelFormat(pfd, 8, 0, 0, 0, 8, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R16:		SetPixelFormat(pfd, 16, 16, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R32:		SetPixelFormat(pfd, 32, 32, 0, 0, 0, 0, 0, 0, 0);	break;
			case Graphic::BufferFormat::R8G8:		SetPixelFormat(pfd, 16, 8, 0, 8, 0, 0, 8, 0, 0);	break;
			case Graphic::BufferFormat::R16G16:		SetPixelFormat(pfd, 32, 16, 0, 16, 0, 0, 16, 0, 0);	break;
			case Graphic::BufferFormat::R32G32:		SetPixelFormat(pfd, 64, 32, 0, 32, 0, 0, 32, 0, 0);	break;
			case Graphic::BufferFormat::B8G8R8A8:		SetPixelFormat(pfd, 32, 8, 8, 8, 8, 16, 8, 0, 24);	break;
			case Graphic::BufferFormat::B8G8R8A8_sRGB:	SetPixelFormat(pfd, 32, 8, 8, 8, 8, 16, 8, 0, 24);	break;
			case Graphic::BufferFormat::B8G8R8X8:		SetPixelFormat(pfd, 32, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::B8G8R8X8_sRGB:	SetPixelFormat(pfd, 32, 8, 8, 8, 0, 16, 8, 0, 0);	break;
			case Graphic::BufferFormat::R8G8B8A8:		SetPixelFormat(pfd, 32, 8, 8, 8, 8, 0, 8, 16, 24);	break;
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	SetPixelFormat(pfd, 32, 8, 8, 8, 8, 0, 8, 16, 24);	break;
			case Graphic::BufferFormat::R16G16B16A16:	SetPixelFormat(pfd, 64, 16, 16, 16, 16, 0, 16, 32, 48);	break;
			case Graphic::BufferFormat::R32G32B32A32:	SetPixelFormat(pfd, 128, 32, 32, 32, 32, 0, 32, 64, 96);	break;

			case Graphic::BufferFormat::R16F:		
			case Graphic::BufferFormat::R32F:		
			case Graphic::BufferFormat::R16G16F:	
			case Graphic::BufferFormat::R32G32F:		
			case Graphic::BufferFormat::R16G16B16A16F:	
			case Graphic::BufferFormat::R32G32B32A32F:	
				throw Exception::CException(L"Cannot set float pixel format: " + String::ToString(uFormat), CR_INFO());
			}
		}

		const GLenum	ToBufferUsage(const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess){
			switch(uUsage)
			{
			case Graphic::BufferUsage::Static:
				switch (uAccess)
				{
				case Graphic::BufferAccess::Read:	return GL_STATIC_READ;
				case Graphic::BufferAccess::Write:	return GL_STATIC_DRAW;
				case Graphic::BufferAccess::ReadAndWrite:	return GL_STATIC_COPY;
				}
				break;

			case Graphic::BufferUsage::Stream:
				switch (uAccess)
				{
				case Graphic::BufferAccess::Read:	return GL_STREAM_READ;
				case Graphic::BufferAccess::Write:	return GL_STREAM_DRAW;
				case Graphic::BufferAccess::ReadAndWrite:	return GL_STATIC_COPY;
				}
				break;

			case Graphic::BufferUsage::Dynamic:
				switch (uAccess)
				{
				case Graphic::BufferAccess::Read:	return GL_DYNAMIC_READ;
				case Graphic::BufferAccess::Write:	return GL_DYNAMIC_DRAW;
				case Graphic::BufferAccess::ReadAndWrite:	return GL_DYNAMIC_COPY;
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
			case Graphic::VertexType::Float:	return GL_FLOAT;
			case Graphic::VertexType::Color32b:	return GL_UNSIGNED_INT;

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

		const uint32	GetTypeSize(const GLenum uType){
			switch (uType)
			{
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:	return 1;

			case GL_SHORT:
			case GL_UNSIGNED_SHORT:	return 2;

			case GL_INT:
			case GL_UNSIGNED_INT:
			case GL_FLOAT:	return 4;

			default:
				throw Exception::CInvalidArgumentException(L"uType", String::FromUInt32(uType),
					L"Unknown opengl data type.", CR_INFO());
			}
		}
	}
}