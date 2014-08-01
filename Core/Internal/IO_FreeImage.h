#pragma once

#include "../Include/Math_Rectangle.h"
#include "../Include/Collection.h"
#include <FreeImage.h>

namespace FreeImage{
	class CBitmap{
	private:
		FIBITMAP*	m_pBitmap;

	public:
		CBitmap();
		CBitmap(FIBITMAP* pBitmap);
		~CBitmap();

		void	Create(const CB::Math::CSize2D& Size, const uint32 uBitsPerPixel);
		void	Set(FIBITMAP* pBitmap);
		void	Free();
		FIBITMAP*	Get() const;
		FIBITMAP*	Release();

		const bool	IsValid() const;
	};

	class CStream{
	private:
		FIMEMORY*	m_pStream;

	public:
		CStream();
		CStream(FIMEMORY* pStream);
		CStream(BYTE* pData, const unsigned uLength);
		CStream(CB::Collection::CList<BYTE>& Data);
		~CStream();

		void	Create(CB::Collection::CList<BYTE>& Data);
		void	Create(BYTE* pData, const unsigned uLength);
		void	Set(FIMEMORY* pStream);
		void	Free();
		FIMEMORY*	Get() const;
	};

	class CData{
	public:
		CBitmap				Bitmap;
		FREE_IMAGE_FORMAT	Format;

		CData();
		CData(FREE_IMAGE_FORMAT uFormat);
		CData(FIBITMAP* pBitmap, FREE_IMAGE_FORMAT uFormat);
	};
}