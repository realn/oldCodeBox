#include "../Include/Math_Size.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CSize3D::CSize3D() : CSize(), Depth(0){}

		CSize3D::CSize3D(const CSize3D& Size) : CSize(Size), Depth(Size.Depth){}

		CSize3D::CSize3D(const CPoint3D& Point) : CSize(Point), Depth(Point.Z > 0 ? Point.Z : 0){}

		CSize3D::CSize3D(const CSize& Size) : CSize(Size), Depth(0){}

		CSize3D::CSize3D(const CSize& Size, const unsigned uDepth) : CSize(Size), Depth(uDepth){}

		CSize3D::CSize3D(const CPoint& Point) : CSize(Point), Depth(0){}

		CSize3D::CSize3D(const CPoint& Point, const unsigned uDepth) : CSize(Point), Depth(uDepth){}

		CSize3D::CSize3D(const unsigned uValue) : CSize(uValue), Depth(uValue){}

		CSize3D::CSize3D(const unsigned uWidth, const unsigned uHeight) : CSize(uWidth, uHeight), Depth(0){}

		CSize3D::CSize3D(const unsigned uWidth, const unsigned uHeight, const unsigned uDepth) : CSize(uWidth, uHeight), Depth(uDepth){}

		void	CSize3D::SetZero(){
			CSize::SetZero();
			this->Depth = 0;
		}

		void	CSize3D::Set(const CSize3D& Size){
			CSize::Set(Size);
			this->Depth = Size.Depth;
		}

		void	CSize3D::Set(const unsigned uValue){
			CSize::Set(uValue);
			this->Depth = uValue;
		}

		void	CSize3D::Set(const unsigned uWidth, const unsigned uHeight){
			CSize::Set(uWidth, uHeight);
			this->Depth = 0;
		}

		void	CSize3D::Set(const unsigned uWidth, const unsigned uHeight, const unsigned uDepth){
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
			return L"Width: " + String::FromUInt32(this->Width) 
				+ L", Height: " + String::FromUInt32(this->Height)
				+ L", Depth: " + String::FromUInt32(this->Depth);
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

		const unsigned&	CSize3D::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			case 2:	return this->Depth;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		unsigned&	CSize3D::operator[](const unsigned uIndex){
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			case 2:	return this->Depth;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}