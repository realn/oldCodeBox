#include "../Include/GraphicTools.h"

namespace CB{
	namespace Tools{
		CRefPtr<Graphic::ITexture2D>	CreateTextureFromImage(CRefPtr<Graphic::IDevice> pDevice, const IO::CImage& image, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat){
			auto size = image.GetSize();
			
			Collection::CList<byte> pixels;
			image.GetPixels(pixels);

			Graphic::BufferFormat uInFormat = Graphic::BufferFormat::B8G8R8A8;
			if(image.GetColorFormat() == IO::Image::ColorFormat::RGB){
				uInFormat = Graphic::BufferFormat::B8G8R8;
			}
			
			return pDevice->CreateTexture2D(size, uUsage, uAccess, uFormat, uInFormat, pixels);
		}
	}
}