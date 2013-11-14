#pragma once

#include "Macros.h"
#include "GraphicDriver_Consts.h"
#include <CBString.h>

namespace CB{
	namespace String{
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::BufferFormat uFormat);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::BufferType uType);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::BufferUsage uUsage);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::BufferAccess uAccess);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::ShaderType uType);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::ShaderVersion uVersion);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::CompareFunc uType);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::VertexType uType);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::InstanceDataType uType);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::StencilOperation uOp);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::BlendOperation uOp);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::BlendOption uOption);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::CullMode uCull);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::FillMode uFill);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::DeviceStateType uType);
		extern GRAPHICDRVINTERFACE_API const CString	ToString(const Graphic::FeatureLevel uLevel);
	}
}