#include "stdafx.h"
#include "../Internal/IO_FreeImage.h"
#include "../Include/Exception.h"

namespace FreeImage{
	CBitmap::CBitmap() : m_pBitmap(0){
	}

	CBitmap::CBitmap(FIBITMAP* pBitmap) : m_pBitmap(pBitmap){
	}

	CBitmap::~CBitmap(){
		this->Free();
	}

	void	CBitmap::Create(const CB::Math::CSize2D& Size, const uint32 uBitsPerPixel){
		this->m_pBitmap = FreeImage_Allocate(Size.Width, Size.Height, uBitsPerPixel);
		if(!this->m_pBitmap){
			throw CB::Exception::CException(
				L"Failed to create image bitmap", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	void	CBitmap::Set(FIBITMAP* pBitmap){
		this->m_pBitmap = pBitmap;
	}

	void	CBitmap::Free(){
		if(this->m_pBitmap){
			FreeImage_Unload(this->m_pBitmap);
			this->m_pBitmap = 0;
		}
	}

	FIBITMAP*	CBitmap::Get() const{
		return this->m_pBitmap;
	}

	FIBITMAP*	CBitmap::Release(){
		FIBITMAP* pBitmap = this->m_pBitmap;
		this->m_pBitmap = 0;
		return pBitmap;
	}

	const bool	CBitmap::IsValid() const{
		return this->m_pBitmap != 0;
	}
}