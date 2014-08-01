#include "stdafx.h"
#include "../Include/Math_Size3D.h"
#include "../Include/Math_Size2D.h"
#include "../Include/Math_Point3D.h"
#include "../Include/Exception.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CSize3D::CSize3D() : 
			Width(0),
			Height(0),
			Depth(0)
		{}

		CSize3D::CSize3D(const CSize3D& Size) : 
			Width(Size.Width),
			Height(Size.Height),
			Depth(Size.Depth)
		{}

		CSize3D::CSize3D(const CPoint3D& Point) : 
			Width(Point.X > 0 ? Point.X : 0), 
			Height(Point.Y > 0 ? Point.Y : 0),
			Depth(Point.Z > 0 ? Point.Z : 0)
		{}

		CSize3D::CSize3D(const CSize2D& Size) : 
			Width(Size.Width),
			Height(Size.Height),
			Depth(0)
		{}

		CSize3D::CSize3D(const CSize2D& Size, const uint32 uDepth) : 
			Width(Size.Width),
			Height(Size.Height),
			Depth(uDepth)
		{}

		CSize3D::CSize3D(const uint32 uValue) : 
			Width(uValue), 
			Height(uValue), 
			Depth(uValue)
		{}

		CSize3D::CSize3D(const uint32 uWidth, const uint32 uHeight) : 
			Width(uWidth), 
			Height(uHeight),
			Depth(0)
		{}

		CSize3D::CSize3D(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth) : 
			Width(uWidth), 
			Height(uHeight),
			Depth(uDepth)
		{}

		CSize3D::CSize3D(const Collection::ICountable<uint32>& array) :
			Width(0),
			Height(0),
			Depth(0)
		{
			if( array.GetLength() >= 3 ){
				Width = array[0];
				Height = array[1];
				Depth = array[2];
			}
		}

		void	CSize3D::SetZero(){
			this->Width = 0;
			this->Height = 0;
			this->Depth = 0;
		}

		void	CSize3D::Set(const CSize3D& Size){
			this->Width = Size.Width;
			this->Height = Size.Height;
			this->Depth = Size.Depth;
		}

		void	CSize3D::Set(const uint32 uValue){
			this->Width = uValue;
			this->Height = uValue;
			this->Depth = uValue;
		}

		void	CSize3D::Set(const uint32 uWidth, const uint32 uHeight){
			this->Width = uWidth;
			this->Height = uHeight;
			this->Depth = 0;
		}

		void	CSize3D::Set(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth){
			this->Width = uWidth;
			this->Height = uHeight;
			this->Depth = uDepth;
		}

		const bool	CSize3D::IsZero() const{
			return this->Width == 0 && this->Height == 0 && this->Depth == 0;
		}

		const bool	CSize3D::IsPartialZero() const{
			return this->Width == 0 || this->Height == 0 || this->Depth == 0;
		}

		const bool	CSize3D::IsEqual(const CSize3D& Size) const{
			return this->Width == Size.Width && this->Height == Size.Height && this->Depth == Size.Depth;
		}

		const CString	CSize3D::ToString() const{
			return L"Width: " + String::ToString(this->Width) 
				+ L", Height: " + String::ToString(this->Height)
				+ L", Depth: " + String::ToString(this->Depth);
		}

		const CSize3D&	CSize3D::operator=(const CSize3D& Size){
			this->Set(Size);
			return *this;
		}

		const bool	CSize3D::operator==(const CSize3D& Size) const{
			return this->IsEqual(Size);
		}

		const bool	CSize3D::operator!=(const CSize3D& Size) const{
			return !this->IsEqual(Size);
		}

		const uint32&	CSize3D::operator[](const uint32 uIndex) const{
			switch (uIndex){
			case 0:	return this->Width;
			case 1:	return this->Height;
			case 2:	return this->Depth;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		uint32&	CSize3D::operator[](const uint32 uIndex){
			switch (uIndex){
			case 0:	return this->Width;
			case 1:	return this->Height;
			case 2:	return this->Depth;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		const Collection::CArray<uint32, 3>	CSize3D::ToArray() const{
			return Collection::CArray<uint32, 3>( &Width, 3 );
		}
	}
}