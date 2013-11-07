#pragma once

#include "BaseBuffer.h"

namespace CB{
	class COGLVertexBuffer :
		public IOGLBaseBuffer
	{
	public:
		COGLVertexBuffer(CRefPtr<COGLDevice> pDevice, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength, const void* pData);
	};
}