#include "../Include/Math_Point.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CPoint3D::CPoint3D() : CPoint(), Z(0){}

		CPoint3D::CPoint3D(const CPoint3D& Point) : CPoint(Point), Z(Point.Z){}

		CPoint3D::CPoint3D(const CPoint& Point) : CPoint(Point), Z(0){}

		CPoint3D::CPoint3D(const CPoint& Point, const int iZ) : CPoint(Point), Z(iZ){}

		CPoint3D::CPoint3D(const int iValue) : CPoint(iValue), Z(iValue){}

		CPoint3D::CPoint3D(const int iX, const int iY) : CPoint(iX, iY), Z(0){}

		CPoint3D::CPoint3D(const int iX, const int iY, const int iZ) : CPoint(iX, iY), Z(iZ){}

		void	CPoint3D::Set(const CPoint3D& Point){
			CPoint::Set(Point);
			this->Z = Point.Z;
		}

		void	CPoint3D::Set(const CPoint& Point){
			CPoint::Set(Point);
		}

		void	CPoint3D::Set(const CPoint& Point, const int iZ){
			this->Set(Point);
			this->Z = iZ;
		}

		void	CPoint3D::Set(const int iValue){
			this->X = iValue;
			this->Y = iValue;
			this->Z = iValue;
		}

		void	CPoint3D::Set(const int iX, const int iY){
			CPoint::Set(iX, iY);
		}

		void	CPoint3D::Set(const int iX, const int iY, const int iZ){
			CPoint::Set(iX, iY);
			this->Z = iZ;
		}

		const bool	CPoint3D::IsZero() const{
			return this->X == 0 && this->Y == 0 && this->Z == 0;
		}

		const bool	CPoint3D::IsPartialZero() const{
			return this->X == 0 || this->Y == 0 || this->Z == 0;
		}

		const bool	CPoint3D::IsEqual(const CPoint3D& Point) const{
			return this->X == Point.X && this->Y == Point.Y && this->Z == Point.Z;
		}

		const CPoint3D	CPoint3D::Add(const CPoint3D& Point) const{
			return CPoint3D(this->X + Point.X, this->Y + Point.Y, this->Z + Point.Z);
		}

		const CPoint3D	CPoint3D::Sub(const CPoint3D& Point) const{
			return CPoint3D(this->X - Point.X, this->Y - Point.Y, this->Z - Point.Z);
		}

		const CPoint3D	CPoint3D::Mul(const CPoint3D& Point) const{
			return CPoint3D(this->X * Point.X, this->Y * Point.Y, this->Z * Point.Z);
		}

		const CPoint3D	CPoint3D::Div(const CPoint3D& Point) const{
			return CPoint3D(this->X / Point.X, this->Y / Point.Y, this->Z / Point.Z);
		}

		const CPoint3D	CPoint3D::Mod(const CPoint3D& Point) const{
			return CPoint3D(this->X % Point.X, this->Y % Point.Y, this->Z % Point.Z);
		}

		const CPoint3D	CPoint3D::Mul(const int iValue) const{
			return CPoint3D(this->X * iValue, this->Y * iValue, this->Z * iValue);
		}

		const CPoint3D	CPoint3D::Div(const int iValue) const{
			return CPoint3D(this->X / iValue, this->Y / iValue, this->Z / iValue);
		}

		const CPoint3D	CPoint3D::Mod(const int iValue) const{
			return CPoint3D(this->X % iValue, this->Y % iValue, this->Z % iValue);
		}

		const CString	CPoint3D::ToString() const{
			return L"X: " + String::FromInt32(this->X) + L", Y: " + String::FromInt32(this->Y) + L", Z: " + String::FromInt32(this->Z);
		}

		const CPoint3D&	CPoint3D::operator=(const CPoint3D& Point){
			this->Set(Point);
			return *this;
		}

		const CPoint3D	CPoint3D::operator+() const{
			return *this;
		}

		const CPoint3D	CPoint3D::operator-() const{
			return CPoint3D(-this->X, -this->Y, -this->Z);
		}

		const CPoint3D	CPoint3D::operator+(const CPoint3D& Point) const{
			return this->Add(Point);
		}

		const CPoint3D	CPoint3D::operator-(const CPoint3D& Point) const{
			return this->Sub(Point);
		}

		const CPoint3D	CPoint3D::operator*(const CPoint3D& Point) const{
			return this->Mul(Point);
		}

		const CPoint3D	CPoint3D::operator/(const CPoint3D& Point) const{
			return this->Div(Point);
		}

		const CPoint3D	CPoint3D::operator%(const CPoint3D& Point) const{
			return this->Mod(Point);
		}

		const CPoint3D	CPoint3D::operator*(const int iValue) const{
			return this->Mul(iValue);
		}

		const CPoint3D	CPoint3D::operator/(const int iValue) const{
			return this->Div(iValue);
		}

		const CPoint3D	CPoint3D::operator%(const int iValue) const{
			return this->Mod(iValue);
		}

		const CPoint3D&	CPoint3D::operator+=(const CPoint3D& Point){
			*this = this->Add(Point);
			return *this;
		}

		const CPoint3D&	CPoint3D::operator-=(const CPoint3D& Point){
			*this = this->Sub(Point);
			return *this;
		}

		const CPoint3D&	CPoint3D::operator*=(const CPoint3D& Point){
			*this = this->Mul(Point);
			return *this;
		}

		const CPoint3D&	CPoint3D::operator/=(const CPoint3D& Point){
			*this = this->Div(Point);
			return *this;
		}

		const CPoint3D&	CPoint3D::operator%=(const CPoint3D& Point){
			*this = this->Mod(Point);
			return *this;
		}

		const CPoint3D&	CPoint3D::operator*=(const int iValue){
			*this = this->Mul(iValue);
			return *this;
		}

		const CPoint3D&	CPoint3D::operator/=(const int iValue){
			*this = this->Div(iValue);
			return *this;
		}

		const CPoint3D&	CPoint3D::operator%=(const int iValue){
			*this = this->Mod(iValue);
			return *this;
		}

		const bool	CPoint3D::operator==(const CPoint3D& Point) const{
			return this->IsEqual(Point);
		}

		const bool	CPoint3D::operator!=(const CPoint3D& Point) const{
			return !this->IsEqual(Point);
		}

		const int&	CPoint3D::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		int&	CPoint3D::operator[](const unsigned uIndex){
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}