#include "stdafx.h"
#include "../Include/Graphic_Strings.h"
#include "../Include/Graphic_Consts.h"

#include <CBString.h>
#include <CBString_Funcs.h>

namespace CB{
	namespace String{
		const CString	ToString(const Graphic::BufferFormat uFormat){
			switch (uFormat)
			{
			case Graphic::BufferFormat::D16:			return L"D16";
			case Graphic::BufferFormat::D24:			return L"D24";
			case Graphic::BufferFormat::D24S8:			return L"D24S8";
			case Graphic::BufferFormat::D24X8:			return L"D24X8";
			case Graphic::BufferFormat::D32:			return L"D32";
			case Graphic::BufferFormat::D32F:			return L"D32F";
			case Graphic::BufferFormat::D32S8X24:		return L"D32S8X24";
			case Graphic::BufferFormat::D32FS8X24U:		return L"D32FS8X24U";

			case Graphic::BufferFormat::R8:				return L"R8";
			case Graphic::BufferFormat::A8:				return L"A8";
			case Graphic::BufferFormat::R16:			return L"R16";
			case Graphic::BufferFormat::R16F:			return L"R16F";
			case Graphic::BufferFormat::R32:			return L"R32";
			case Graphic::BufferFormat::R32F:			return L"R32F";

			case Graphic::BufferFormat::R8G8:			return L"R8G8";
			case Graphic::BufferFormat::R16G16:			return L"R16G16";
			case Graphic::BufferFormat::R16G16F:		return L"R16G16F";
			case Graphic::BufferFormat::R32G32:			return L"R32G32";
			case Graphic::BufferFormat::R32G32F:		return L"R32G32F";

			case Graphic::BufferFormat::R8G8B8:			return L"R8G8B8";
			case Graphic::BufferFormat::B8G8R8:			return L"B8G8R8";
			case Graphic::BufferFormat::R8G8B8_sRGB:	return L"R8G8B8_sRGB";
			case Graphic::BufferFormat::R16G16B16:		return L"R16G16B16";
			case Graphic::BufferFormat::R16G16B16F:		return L"R16G16B16F";
			case Graphic::BufferFormat::R32G32B32:		return L"R32G32B32";
			case Graphic::BufferFormat::R32G32B32F:		return L"R32G32B32F";

			case Graphic::BufferFormat::B8G8R8A8:		return L"B8G8R8A8";
			case Graphic::BufferFormat::B8G8R8A8_sRGB:	return L"B8G8R8A8_sRGB";
			case Graphic::BufferFormat::B8G8R8X8:		return L"B8G8R8X8";
			case Graphic::BufferFormat::B8G8R8X8_sRGB:	return L"B8G8R8X8_sRGB";
			case Graphic::BufferFormat::R8G8B8A8:		return L"R8G8B8A8";
			case Graphic::BufferFormat::R8G8B8A8_sRGB:	return L"R8G8B8A8_sRGB";
			case Graphic::BufferFormat::R16G16B16A16:	return L"R16G16B16A16";
			case Graphic::BufferFormat::R16G16B16A16F:	return L"R16G16B16A16F";
			case Graphic::BufferFormat::R32G32B32A32:	return L"R32G32B32A32";
			case Graphic::BufferFormat::R32G32B32A32F:	return L"R32G32B32A32F";

			default:
				return String::ToString((uint32)uFormat);
			}
		}
	}
}