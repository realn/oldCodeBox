#include "stdafx.h"
#include "../Internal/IO_FreeImage.h"

namespace FreeImage{
	CData::CData() : Bitmap(), Format(FIF_BMP){
	}

	CData::CData(FREE_IMAGE_FORMAT uFormat) : Bitmap(), Format(uFormat){
	}

	CData::CData(FIBITMAP* pBitmap, FREE_IMAGE_FORMAT uFormat) : Bitmap(pBitmap), Format(uFormat){
	}
}