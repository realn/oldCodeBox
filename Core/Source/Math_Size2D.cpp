#include "stdafx.h"
#include "../Include/Math_Size2D.h"
#include "../Include/Math_Point2D.h"
#include "../Include/Exception.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CSize2D::CSize2D() : 
			Width(0), 
			Height(0)
		{}

		CSize2D::CSize2D(const CSize2D& Size) : 
			Width(Size.Width), 
			Height(Size.Height)
		{}

		CSize2D::CSize2D(const CPoint2D& Point) : 
			Width(Point.X > 0 ? Point.X : 0), 
			Height(Point.Y > 0 ? Point.Y : 0)
		{}

		CSize2D::CSize2D(const uint32 uValue) : 
			Width(uValue), 
			Height(uValue)
		{}

		CSize2D::CSize2D(const uint32 uWidth, const uint32 uHeight) : 
			Width(uWidth), 
			Height(uHeight)
		{}

		CSize2D::CSize2D(const Collection::ICountable<uint32>& array) :
			Width(0),
			Height(0)
		{
			if( array.GetLength() >= 2 ){
				Width = array[0];
				Height = array[1];
			}
		}

		void	CSize2D::SetZero(){
			this->Width = 0;
			this->Height = 0;
		}

		void	CSize2D::Set(const CSize2D& Size){
			this->Width = Size.Width;
			this->Height = Size.Height;
		}

		void	CSize2D::Set(const uint32 uValue){
			this->Width = uValue;
			this->Height = uValue;
		}

		void	CSize2D::Set(const uint32 uWidth, const uint32 uHeight){
			this->Width		= uWidth;
			this->Height	= uHeight;
		}

		const bool	CSize2D::IsZero() const{
			return this->Width == 0 && this->Height == 0;
		}

		const bool	CSize2D::IsPartialZero() const{
			return this->Width == 0 || this->Height == 0;
		}

		const bool	CSize2D::IsEqual(const CSize2D& Size) const{
			return this->Width == Size.Width && this->Height == Size.Height;
		}

		const CString	CSize2D::ToString() const{
			return L"Width: " + String::ToString(this->Width) + L", Height: " + String::ToString(this->Height);
		}

		const CSize2D&	CSize2D::operator=(const CSize2D& Size){
			this->Set(Size);
			return *this;
		}

		const bool	CSize2D::operator==(const CSize2D& Size) const{
			return this->IsEqual(Size);
		}

		const bool	CSize2D::operator!=(const CSize2D& Size) const{
			return !this->IsEqual(Size);
		}

		const uint32&	CSize2D::operator[](const uint32 uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		uint32&	CSize2D::operator[](const uint32 uIndex){
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		const Collection::CArray<uint32, 2>	CSize2D::ToArray() const{
			return Collection::CArray<uint32, 2>( &Width, 2 );
		}
	}
}