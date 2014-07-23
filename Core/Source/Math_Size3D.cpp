#include "stdafx.h"
#include "../Include/Math_Size.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CSize3D::CSize3D() : 
			Depth(0)
		{}

		CSize3D::CSize3D(const CSize3D& Size) : 
			CSize(Size), 
			Depth(Size.Depth)
		{}

		CSize3D::CSize3D(const CPoint3D& Point) : 
			CSize(Point), 
			Depth(Point.Z > 0 ? Point.Z : 0)
		{}

		CSize3D::CSize3D(const CSize& Size) : 
			CSize(Size), 
			Depth(0)
		{}

		CSize3D::CSize3D(const CSize& Size, const uint32 uDepth) : 
			CSize(Size), 
			Depth(uDepth)
		{}

		CSize3D::CSize3D(const CPoint& Point) : 
			CSize(Point), 
			Depth(0)
		{}

		CSize3D::CSize3D(const CPoint& Point, const uint32 uDepth) : 
			CSize(Point), 
			Depth(uDepth)
		{}

		CSize3D::CSize3D(const uint32 uValue) : 
			CSize(uValue), 
			Depth(uValue)
		{}

		CSize3D::CSize3D(const uint32 uWidth, const uint32 uHeight) : 
			CSize(uWidth, uHeight), 
			Depth(0)
		{}

		CSize3D::CSize3D(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth) : 
			CSize(uWidth, uHeight), 
			Depth(uDepth)
		{}

		void	CSize3D::SetZero(){
			CSize::SetZero();
			this->Depth = 0;
		}

		void	CSize3D::Set(const CSize3D& Size){
			CSize::Set(Size);
			this->Depth = Size.Depth;
		}

		void	CSize3D::Set(const uint32 uValue){
			CSize::Set(uValue);
			this->Depth = uValue;
		}

		void	CSize3D::Set(const uint32 uWidth, const uint32 uHeight){
			CSize::Set(uWidth, uHeight);
			this->Depth = 0;
		}

		void	CSize3D::Set(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth){
			CSize::Set(uWidth, uHeight);
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

		const CPoint3D	CSize3D::ToPoint() const{
			return CPoint3D(this->Width, this->Height, this->Depth);
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
	}
}