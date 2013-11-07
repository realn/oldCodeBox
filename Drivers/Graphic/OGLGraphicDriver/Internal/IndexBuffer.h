#pragma once

#include "BaseBuffer.h"

namespace CB{
	class COGLIndexBuffer : 
		public IOGLBaseBuffer
	{
	public:
		COGLIndexBuffer(CRefPtr<COGLDevice> pDevice, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength, const void* pData);
	};
}