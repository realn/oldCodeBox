#pragma once

namespace CB{
	namespace Graphic{
		//=============================================
		//	Represents bit assosiation of components in a buffer.
		//	WARNING: Color Components are in REVERSE than placement, Ex:
		//		R8G8B8A8 components start at bit:
		//		  A  B  G  R
		//		 24 16  8  0
		//=============================================
		enum class BufferFormat{
			Unknown,

			//	Depth-Stencil Formats
			D16,		//	Feature Level 1
			D24,		//	Feature Level 1, Texture Only
			D24X8,		//	Feature Level 1, Color Buffer Only
			D24S8,		//	Feature Level 1, Color Buffer Only
			D32,		//	Feature Level 1
			D32F,		//	Feature Level 3
			D32S8X24,	//	Feature Level 1, Color Buffer Only
			D32FS8X24U,	//	Feature LEvel 3, Color Buffer Only

			//	Color Formats
			
			// One Component
			R8,			//	Feature Level 3
			A8,			//	Feature Level 1
			R16,		//	Feature Level 3
			R16F,		//	Feature Level 3
			R32,		//	Feature Level 3
			R32F,		//	Feature Level 3

			// Two Components
			R8G8,		//	Feature Level 3
			R16G16,		//	Feature Level 3
			R16G16F,	//	Feature Level 3
			R32G32,		//	Feature Level 3
			R32G32F,	//	Feature Level 3

			//	Three Components
			B8G8R8,			//	Feature Level 1
			R8G8B8,			//	Feature Level 1
			R8G8B8_sRGB,	//	
			R16G16B16,		//	Feature Level 1
			R16G16B16F,		//	Feature Level 3
			R32G32B32,		//	Feature Level 3
			R32G32B32F,		//	Feature Level 3

			//	Four Components
			B8G8R8A8,		//	Feature Level 1
			B8G8R8A8_sRGB,	//	Feature Level 3
			B8G8R8X8,		//	Feature Level 1, Color Buffer Only
			B8G8R8X8_sRGB,	//	Feature Level 3, Color Buffer Only
			R8G8B8A8,		//	Feature Level 1
			R8G8B8A8_sRGB,	//	Feature Level 3
			R16G16B16A16,	//	Feature Level 1
			R16G16B16A16F,	//	Feature Level 3
			R32G32B32A32,	//	Feature Level 2
			R32G32B32A32F,	//	Feature Level 3
		};
	}
}