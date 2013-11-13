#pragma once

#include <GraphicDriver.h>
#include "WinPlatform.h"
#include "OpenGL.h"
#include <Collection_List.h>

namespace CB{
	namespace GLUtils{
		extern const uint32	GetBitsPerPixel(const Graphic::BufferFormat uFormat);

		extern const Graphic::BufferFormat	ToColorBufferFormat(const PIXELFORMATDESCRIPTOR& pfd);

		extern void	SetPixelFormat(PIXELFORMATDESCRIPTOR& pfd, const Graphic::BufferFormat uFormat);
		extern void	SetPixelFormat(Collection::CList<int32>& Attribs, const Graphic::BufferFormat uFormat);

		extern const GLenum	ToBufferUsage(const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess);

		extern const GLenum	ToVertexType(const Graphic::VertexType uType);
		extern const uint32	ToVertexTypeNumber(const Graphic::VertexType uType);
		extern const Graphic::VertexType	ToVertexType(const GLenum uType, const uint32 uNumber);

		extern const uint32	GetTypeSize(const GLenum uType);
	}
}