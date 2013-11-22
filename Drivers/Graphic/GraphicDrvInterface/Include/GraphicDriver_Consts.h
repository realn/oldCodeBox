#pragma once

namespace CB{
	namespace Graphic{
		enum class FeatureLevel{
			/*
				Generation 1 level hardware:
				Direct3D 9, SM 2 (asm)
				OpenGL 1.4 + VBO + MipMap Gen + Anisotropy, ARB Shader (asm)
			*/
			Level_1,	// DX9 (SM2, ASM) / OGL1.4-1.5 (SM2, ARB Program/ASM)

			/*
				Generation 2 level hardware:
				Direct3D 9, SM 3 (HLSL)
				OpenGL 2.0-2.1, GLSL Shader
			*/
			Level_2,	// DX9 (SM3, HLSL) / OGL2.0-2.1 (SM3, GLSL)

			//	SM:	3
			//	RT:	8
			Level_3,	// DX10 (SM4, HLSL) / OGL3.0-3.3 (SM4, GLSL)

			//	SM: 4
			//	RT: 8
			Level_4,	// DX11 (SM5, HLSL) / OGL4.0-4.4 (SM5, GLSL)
		};

		enum class DeviceStateType{
			Rasterizer,
			DepthStencil,
			Blend,
		};

		//=============================================
		//	Represents bit assosiation of components in a buffer.
		//	WARNING: Color Components are in REVERSE than placement, Ex:
		//		R8G8B8A8 components start at bit:
		//		  A  B  G  R
		//		 24 16  8  0
		//=============================================
		enum class BufferFormat{
			Unknown,

			//	Depth-Stencil Formats
			D16,		//	Feature Level 1
			D24,		//	Feature Level 1, Texture Only
			D24X8,		//	Feature Level 1, Color Buffer Only
			D24S8,		//	Feature Level 1, Color Buffer Only
			D32,		//	Feature Level 1
			D32F,		//	Feature Level 3
			D32S8X24,	//	Feature Level 1, Color Buffer Only
			D32FS8X24U,	//	Feature LEvel 3, Color Buffer Only

			//	Color Formats
			
			// One Component
			R8,			//	Feature Level 3
			A8,			//	Feature Level 1
			R16,		//	Feature Level 3
			R16F,		//	Feature Level 3
			R32,		//	Feature Level 3
			R32F,		//	Feature Level 3

			// Two Components
			R8G8,		//	Feature Level 3
			R16G16,		//	Feature Level 3
			R16G16F,	//	Feature Level 3
			R32G32,		//	Feature Level 3
			R32G32F,	//	Feature Level 3

			//	Three Components
			B8G8R8,			//	Feature Level 1
			R8G8B8,			//	Feature Level 1
			R8G8B8_sRGB,	//	
			R16G16B16,		//	Feature Level 1
			R16G16B16F,		//	Feature Level 3
			R32G32B32,		//	Feature Level 3
			R32G32B32F,		//	Feature Level 3

			//	Four Components
			B8G8R8A8,		//	Feature Level 1
			B8G8R8A8_sRGB,	//	Feature Level 3
			B8G8R8X8,		//	Feature Level 1, Color Buffer Only
			B8G8R8X8_sRGB,	//	Feature Level 3, Color Buffer Only
			R8G8B8A8,		//	Feature Level 1
			R8G8B8A8_sRGB,	//	Feature Level 3
			R16G16B16A16,	//	Feature Level 1
			R16G16B16A16F,	//	Feature Level 3
			R32G32B32A32,	//	Feature Level 2
			R32G32B32A32F,	//	Feature Level 3
		};

		enum class PrimitiveType{
			Points,
			Lines,
			Triangles,
		};

		enum class VertexType{
			None,
			Float,		// float
			Color32b,	// A8R8G8B8
		};

		enum class BufferType{
			Vertex,
			Index,
		};

		enum class ShaderVersion{
			Latest = 0,
			ShaderModel_2,
			ShaderModel_3,
			ShaderModel_4,
			ShaderModel_5
		};

		enum class ShaderType{
			Vertex,
			Geometry,
			Fragment,
		};

		enum class CullMode{
			None,
			Front,
			Back,
		};

		enum class InstanceDataType{
			None,
			PerVertexData,
			PerInstanceData,
		};

		enum class CompareFunc{
			Never,
			Less,
			LessEqual,
			Equal,
			GreaterEqual,
			Greater,
			Always,
			NotEqual,
		};

		enum class StencilOperation{
			Keep,
			Zero,
			Replace,
			Incr_Wrap,
			Decr_Wrap,
			Invert,
			Incr,
			Decr
		};

		enum class TextureType{
			Texture1D,
			Texture2D,
			Texture3D,
			TextureCube
		};

		enum class TextureFilter{
			None,		//	Value valid only for mipmapping
			Nearest,
			Linear,
		};

		enum class TextureWrap{
			Repeat,
			Clamp,
			ClampToEdge,
			Mirror,
		};

		enum class BlendOperation{
			Add,
			Sub,
			Sub_Reverse,
			Min,
			Max,
		};

		enum class BlendOption{
			Zero,
			One,
			SourceColor,
			OneMinusSourceColor,
			DestColor,
			OneMinusDestColor,
			SourceAlpha,
			OneMinusSourceAlpha,
			DestAlpha,
			OneMinusDestAlpha,
			BlendFactor,
			OneMinusBlendFactor,
		};

		enum class FillMode{
			WireFrame,
			Solid,
		};

		enum class BufferUsage{
			Static,
			Stream,
			Dynamic,
		};

		enum class BufferAccess{
			Read,
			Write,
			ReadAndWrite,
		};
	}
}