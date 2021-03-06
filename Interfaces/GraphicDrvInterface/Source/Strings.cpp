#include "../Include/GraphicDriver_Strings.h"

namespace CB{
	namespace Graphic{
		const CString	g_strCreateManagerProcName = L"CreateGraphicManager";
	}

	namespace String{
		const CString	ToString(const Graphic::BufferFormat uFormat){
			switch (uFormat)
			{
			case Graphic::BufferFormat::D16:			return L"D16";
			case Graphic::BufferFormat::D24:			return L"D24";
			case Graphic::BufferFormat::D24S8:			return L"D24S8";
			case Graphic::BufferFormat::D24X8:			return L"D24X8";
			case Graphic::BufferFormat::D32:			return L"D32";
			case Graphic::BufferFormat::D32F:			return L"D32F";
			case Graphic::BufferFormat::D32S8X24:		return L"D32S8X24";
			case Graphic::BufferFormat::D32FS8X24U:		return L"D32FS8X24U";

			case Graphic::BufferFormat::R8:				return L"R8";
			case Graphic::BufferFormat::A8:				return L"A8";
			case Graphic::BufferFormat::R16:			return L"R16";
			case Graphic::BufferFormat::R16F:			return L"R16F";
			case Graphic::BufferFormat::R32:			return L"R32";
			case Graphic::BufferFormat::R32F:			return L"R32F";

			case Graphic::BufferFormat::R8G8:			return L"R8G8";
			case Graphic::BufferFormat::R16G16:			return L"R16G16";
			case Graphic::BufferFormat::R16G16F:		return L"R16G16F";
			case Graphic::BufferFormat::R32G32:			return L"R32G32";
			case Graphic::BufferFormat::R32G32F:		return L"R32G32F";

			case Graphic::BufferFormat::R8G8B8:			return L"R8G8B8";
			case Graphic::BufferFormat::B8G8R8:			return L"B8G8R8";
			case Graphic::BufferFormat::R8G8B8_sRGB:	return L"R8G8B8_sRGB";
			case Graphic::BufferFormat::R16G16B16:		return L"R16G16B16";
			case Graphic::BufferFormat::R16G16B16F:		return L"R16G16B16F";
			case Graphic::BufferFormat::R32G32B32:		return L"R32G32B32";
			case Graphic::BufferFormat::R32G32B32F:		return L"R32G32B32F";

			case Graphic::BufferFormat::B8G8R8A8:		return L"B8G8R8A8";
			case Graphic::BufferFormat::B8G8R8A8_sRGB:	return L"B8G8R8A8_sRGB";
			case Graphic::BufferFormat::B8G8R8X8:		return L"B8G8R8X8";
			case Graphic::BufferFormat::B8G8R8X8_sRGB:	return L"B8G8R8X8_sRGB";
			case Graphic::BufferFormat::R8G8B8A8:		return L"R8G8B8A8";
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	return L"R8G8B8A8_sRGB";
			case Graphic::BufferFormat::R16G16B16A16:	return L"R16G16B16A16";
			case Graphic::BufferFormat::R16G16B16A16F:	return L"R16G16B16A16F";
			case Graphic::BufferFormat::R32G32B32A32:	return L"R32G32B32A32";
			case Graphic::BufferFormat::R32G32B32A32F:	return L"R32G32B32A32F";

			default:
				return String::ToString((uint32)uFormat);
			}
		}

		const CString	ToString(const Graphic::BufferType uType){
			switch(uType){
			case Graphic::BufferType::Vertex:	return L"Vertex";
			case Graphic::BufferType::Index:	return L"Index";

			default:
				return String::FromUInt32((uint32)uType);
			}
		}

		const CString	ToString(const Graphic::BufferUsage uUsage){
			switch (uUsage)
			{
			case Graphic::BufferUsage::Dynamic:	return L"Dynamic";
			case Graphic::BufferUsage::Static:	return L"Static";
			case Graphic::BufferUsage::Stream:	return L"Stream";

			default:				
				return String::FromUInt32((uint32)uUsage);
			}
		}

		const CString	ToString(const Graphic::BufferAccess uAccess){
			switch (uAccess)
			{
			case Graphic::BufferAccess::Read:	return L"Read";
			case Graphic::BufferAccess::Write:	return L"Write";
			case Graphic::BufferAccess::ReadAndWrite:	return L"Read And Write";

			default:
				return String::FromUInt32((uint32)uAccess);
			}
		}

		const CString	ToString(const Graphic::ShaderType uType){
			switch (uType)
			{
			case Graphic::ShaderType::Vertex:	return L"Vertex";
			case Graphic::ShaderType::Geometry:	return L"Geometry";
			case Graphic::ShaderType::Fragment:	return L"Fragment";

			default:
				return String::FromUInt32((uint32)uType);
			}
		}

		const CString	ToString(const Graphic::ShaderVersion uVersion){
			switch (uVersion)
			{
			case Graphic::ShaderVersion::Latest:	return L"Latest";
			case Graphic::ShaderVersion::ShaderModel_2:		return L"Shader Model 2.0";
			case Graphic::ShaderVersion::ShaderModel_3:		return L"Shader Model 3.0";
			case Graphic::ShaderVersion::ShaderModel_4:		return L"Shader Model 4.0";
			case Graphic::ShaderVersion::ShaderModel_5:		return L"Shader Model 5.0";
			default:
				return String::FromUInt32((uint32)uVersion);
			}
		}

		const CString	ToString(const Graphic::CompareFunc uType){
			switch (uType)
			{
			case Graphic::CompareFunc::Never:	return L"Never";
			case Graphic::CompareFunc::Less:	return L"Less";
			case Graphic::CompareFunc::LessEqual:	return L"LessEqual";
			case Graphic::CompareFunc::Equal:	return L"Equal";
			case Graphic::CompareFunc::Greater:	return L"Greater";
			case Graphic::CompareFunc::GreaterEqual:	return L"GreaterEqual";
			case Graphic::CompareFunc::Always:	return L"Always";
			case Graphic::CompareFunc::NotEqual:	return L"NotEqual";
			default:
				return String::FromUInt32((uint32)uType);
			}
		}

		const CString	ToString(const Graphic::VertexType uType){
			switch(uType){
			case Graphic::VertexType::Float:	return L"Float";
			case Graphic::VertexType::Color32b:	return L"32b Color";

			default:
				return String::FromUInt32((uint32)uType);
			}
		}

		const CString	ToString(const Graphic::InstanceDataType uType){
			switch (uType)
			{
			case Graphic::InstanceDataType::None:	L"None";
			case Graphic::InstanceDataType::PerInstanceData:	return L"Per Instance";
			case Graphic::InstanceDataType::PerVertexData:		return L"Per Vertex";

			default:
				return String::FromUInt32((uint32)uType);
			}
		}

		const CString	ToString(const Graphic::StencilOperation uOp){
			switch (uOp)
			{
			case Graphic::StencilOperation::Decr:		return L"Decrement";
			case Graphic::StencilOperation::Decr_Wrap:	return L"Decrement & Wrap";
			case Graphic::StencilOperation::Incr:		return L"Increment";
			case Graphic::StencilOperation::Incr_Wrap:	return L"Increment & Wrap";
			case Graphic::StencilOperation::Invert:		return L"Invert";
			case Graphic::StencilOperation::Keep:		return L"Keep";
			case Graphic::StencilOperation::Replace:	return L"Replace";
			case Graphic::StencilOperation::Zero:		return L"Zero";

			default:
				return String::FromUInt32((uint32)uOp);
			}
		}

		const CString	ToString(const Graphic::BlendOperation uOp){
			switch (uOp)
			{
			case Graphic::BlendOperation::Add:	return L"Add";
			case Graphic::BlendOperation::Max:	return L"Max";
			case Graphic::BlendOperation::Min:	return L"Min";
			case Graphic::BlendOperation::Sub:	return L"Sub";
			case Graphic::BlendOperation::Sub_Reverse:	return L"Sub Reverse";

			default:
				return String::FromUInt32((uint32)uOp);
			}
		}

		const CString	ToString(const Graphic::BlendOption uOption){
			switch (uOption)
			{
			case Graphic::BlendOption::DestAlpha:			return L"Dest Alpha";
			case Graphic::BlendOption::DestColor:			return L"Dest Color";
			case Graphic::BlendOption::One:					return L"One";
			case Graphic::BlendOption::OneMinusDestAlpha:	return L"One Minus Dest Alpha";
			case Graphic::BlendOption::OneMinusDestColor:	return L"One Minus Dest Color";
			case Graphic::BlendOption::OneMinusSourceAlpha:	return L"One Minus Source Alpha";
			case Graphic::BlendOption::OneMinusSourceColor:	return L"One Minus Source Color";
			case Graphic::BlendOption::SourceAlpha:			return L"Source Alpha";
			case Graphic::BlendOption::SourceColor:			return L"Source Color";
			case Graphic::BlendOption::Zero:				return L"Zero";
			case Graphic::BlendOption::BlendFactor:			return L"Blend Factor";
			case Graphic::BlendOption::OneMinusBlendFactor:	return L"One Minus Blend Factor";

			default:
				return String::ToString((uint32)uOption);
			}
		}

		const CString	ToString(const Graphic::CullMode uCull){
			switch (uCull)
			{
			case Graphic::CullMode::Front:	return L"Front";
			case Graphic::CullMode::Back:	return L"Back";
			case Graphic::CullMode::None:		return L"None";

			default:
				return String::FromUInt32((uint32)uCull);
			}
		}

		const CString	ToString(const Graphic::FillMode uFill){
			switch (uFill)
			{
			case Graphic::FillMode::Solid:	return L"Solid";
			case Graphic::FillMode::WireFrame:	return L"WireFrame";

			default:
				return String::FromUInt32((uint32)uFill);
			}
		}

		const CString	ToString(const Graphic::DeviceStateType uType){
			switch (uType)
			{
			case Graphic::DeviceStateType::Blend:			return L"Blend";
			case Graphic::DeviceStateType::DepthStencil:	return L"DepthStencil";
			case Graphic::DeviceStateType::Rasterizer:		return L"Rasterizer";

			default:
				return String::FromUInt32((uint32)uType);
			}
		}

		const CString	ToString(const Graphic::FeatureLevel uLevel){
			switch (uLevel){
			case Graphic::FeatureLevel::Level_1:	return L"Level 1";
			case Graphic::FeatureLevel::Level_2:	return L"Level 2";
			case Graphic::FeatureLevel::Level_3:	return L"Level 3";
			case Graphic::FeatureLevel::Level_4:	return L"Level 4";
			default:
				return String::ToString((uint32)uLevel);
			}
		}

		const CString	ToString(const Graphic::TextureFilter uFilter){
			switch (uFilter)
			{
			case Graphic::TextureFilter::None:		return L"None";
			case Graphic::TextureFilter::Nearest:	return L"Nearest";
			case Graphic::TextureFilter::Linear:	return L"Linear";
			default:
				return String::ToString((uint32)uFilter);
			}
		}

		const CString	ToString(const Graphic::TextureWrap uWrap){
			switch (uWrap)
			{
			case Graphic::TextureWrap::Clamp:		return L"Clamp";
			case Graphic::TextureWrap::ClampToEdge:	return L"Clamp To Edge";
			case Graphic::TextureWrap::Mirror:		return L"Mirror";
			case Graphic::TextureWrap::Repeat:		return L"Repeat";
			default:
				return String::ToString((uint32)uWrap);
			}
		}

		const CString	ToString(const Graphic::TextureType uType){
			switch (uType)
			{
			case Graphic::TextureType::Texture1D:	return L"Texture 1D";
			case Graphic::TextureType::Texture2D:	return L"Texture 2D";
			case Graphic::TextureType::Texture3D:	return L"Texture 3D";
			case Graphic::TextureType::TextureCube:	return L"Texture Cube";
			default:
				return String::ToString((uint32)uType);
			}
		}
	}
}