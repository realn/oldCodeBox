#include "../Internal/IndexBuffer.h"

namespace CB{
	COGLIndexBuffer::COGLIndexBuffer(CRefPtr<COGLDevice> pDevice, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength, const void* pData) :
		IOGLBaseBuffer(pDevice, Graphic::BufferType::Index, GL::GL_ELEMENT_ARRAY_BUFFER, uUsage, uAccess, uLength, pData)
	{

	}
}