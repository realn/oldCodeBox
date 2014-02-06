#pragma once

#include <IO_MemoryStream.h>
#include "BaseBuffer.h"

namespace CB{
	class IOGLBaseBuffer;

	class COGLBufferStream :
		public IO::IMemoryStream,
		public Manage::IManagedObject<IOGLBaseBuffer, COGLBufferStream>
	{
	private:
		CGLRenderContext& GL;

	public:
		COGLBufferStream(CRefPtr<IOGLBaseBuffer> pBuffer, CGLRenderContext& GL, const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength);
		~COGLBufferStream();
	};
}