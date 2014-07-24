#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	namespace IO{
		namespace Image{
			enum class FileType : uint32{
				Unknown,
				Bitmap,
				Targa,
				Jpeg,
				Png,
			};

			enum class BitFormat : uint32{
				Unknown,
				f4Bit,
				f8Bit,
				f16Bit,
				f24Bit,
				f32Bit,
			};

			enum class ColorFormat{
				Unknown,
				RGB,
				RGBA,
			};

			enum class FlipType{
				Horizontal,
				Vertical,
			};

			enum class ScaleFilter : uint32{
				Box,
				BiLinear,
				BSpline,
				BiCubic,
				CatmullRom,
				Lanczos3,
			};
		}
	}
}