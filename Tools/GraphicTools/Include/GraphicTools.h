#pragma once

#include "Macros.h"
#include <GraphicDriver.h>
#include <Font.h>
#include <IO_Image.h>
#include <Math_RectangleF.h>

#include "Tools_Mesh.h"
#include "Tools_Font.h"

namespace CB{
	namespace Tools{
		extern GRAPHICTOOLS_API CRefPtr<Graphic::ITexture2D>	CreateTextureFromImage(CRefPtr<Graphic::IDevice> pDevice, const IO::CImage& image, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat);
	}
}