#include "../Internal/VertexBuffer.h"

namespace CB{
	COGLVertexBuffer::COGLVertexBuffer(CRefPtr<COGLDevice> pDevice, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength, const void* pData) :
		IOGLBaseBuffer(pDevice, Graphic::BufferType::Vertex, GL_ARRAY_BUFFER, uUsage, uAccess, uLength, pData)
	{

	}
}