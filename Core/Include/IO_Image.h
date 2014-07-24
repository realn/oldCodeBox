#pragma once

#include "Macros.h"
#include "Types.h"
#include "IO_Image_Defs.h"
#include "SmartPointers_Hidden.h"
#include "Collection_List.h"

namespace CB{
	template<typename _Type> class CRefPtr;
	namespace Math{
		class CPoint;
		class CSize;
		class CRectangle;
	}

	namespace IO{
		class IStream;

		class COMMON_API CImage{
		private:
			CHiddenPtr	m_Data;

		public:
			CImage();
			CImage(const CImage& Image);
			CImage(const Math::CSize& Size);
			CImage(const Math::CSize& Size, const Image::BitFormat uFormat);
			~CImage();

			void	Create(const Math::CSize& Size);
			void	Create(const Math::CSize& Size, const Image::BitFormat uFormat);
			void	Free();

			void	WriteToStream(CRefPtr<IO::IStream> pStream) const;
			void	WriteToStream(CRefPtr<IO::IStream> pStream, const Image::FileType uFileType) const;
			void	ReadFromStream(CRefPtr<IO::IStream> pStream);

			const Math::CSize			GetSize() const;
			const Image::BitFormat		GetBitFormat() const;
			const uint32				GetBytesPerPixel() const;
			const Image::ColorFormat	GetColorFormat() const;
			const bool					IsLoaded() const;

			void	GetPixels(Collection::CList<byte>& Pixels) const;
			void	SetPixels(const Collection::CList<byte>& Pixels);

			void	Convert(const Image::BitFormat uFormat);
			void	Flip(const Image::FlipType uFlip);
			void	Resize(const Math::CSize& Size); // uFilter = BiCubic, bKeepRatio = false
			void	Resize(const Math::CSize& Size, const Image::ScaleFilter uFilter);	// bKeepRatio: false
			void	Resize(const Math::CSize& Size, const Image::ScaleFilter uFilter, const bool bKeepRatio);

			void	CopyTo(CImage& Image) const;
			void	CopyTo(CImage& Image, const Math::CRectangle& rtSource) const;
			void	PasteTo(CImage& Image, const Math::CPoint& ptDestination) const; //fAlpha: 1.0f
			void	PasteTo(CImage& Image, const Math::CPoint& ptDestination, const float fAlpha) const;

			const CString	ToString() const;

			const CImage&	operator=(const CImage& Image);
		};

	}

	namespace String{
		extern COMMON_API const CString	ToString(const IO::Image::BitFormat uFormat);
		extern COMMON_API const CString	ToString(const IO::Image::ColorFormat uFormat);
		extern COMMON_API const CString	ToString(const IO::Image::FileType uType);
		extern COMMON_API const CString	ToString(const IO::Image::FlipType uType);
		extern COMMON_API const CString	ToString(const IO::Image::ScaleFilter uFilter);
	}
}