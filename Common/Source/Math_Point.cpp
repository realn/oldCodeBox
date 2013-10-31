#include "../Include/Math_Point.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CPoint::CPoint() : X(0), Y(0){}

		CPoint::CPoint(const CPoint& Point) : X(Point.X), Y(Point.Y){}

		CPoint::CPoint(const int iValue) : X(iValue), Y(iValue){}

		CPoint::CPoint(const int iX, const int iY) : X(iX), Y(iY){}

		void	CPoint::SetZero(){
			this->X = 0;
			this->Y = 0;
		}

		void	CPoint::Set(const CPoint& Point){
			this->X = Point.X;
			this->Y = Point.Y;
		}

		void	CPoint::Set(const int iValue){
			this->X = iValue;
			this->Y = iValue;
		}

		void	CPoint::Set(const int iX, const int iY){
			this->X = iX;
			this->Y = iY;
		}

		const bool	CPoint::IsZero() const{
			return this->X == 0 && this->Y == 0;
		}

		const bool	CPoint::IsPartialZero() const{
			return this->X == 0 || this->Y == 0;
		}

		const bool	CPoint::IsEqual(const CPoint& Point) const{
			return this->X == Point.X && this->Y == Point.Y;
		}

		const CPoint	CPoint::Add(const CPoint& Point) const{
			return CPoint(this->X + Point.X, this->Y + Point.Y);
		}

		const CPoint	CPoint::Sub(const CPoint& Point) const{
			return CPoint(this->X - Point.X, this->Y - Point.Y);
		}

		const CPoint	CPoint::Mul(const CPoint& Point) const{
			return CPoint(this->X * Point.X, this->Y * Point.Y);
		}

		const CPoint	CPoint::Div(const CPoint& Point) const{
			return CPoint(this->X / Point.X, this->Y / Point.Y);
		}

		const CPoint	CPoint::Mod(const CPoint& Point) const{
			return CPoint(this->X % Point.X, this->Y % Point.Y);
		}

		const CPoint	CPoint::Mul(const int iValue) const{
			return CPoint(this->X * iValue, this->Y * iValue);
		}

		const CPoint	CPoint::Div(const int iValue) const{
			return CPoint(this->X / iValue, this->Y / iValue);
		}

		const CPoint	CPoint::Mod(const int iValue) const{
			return CPoint(this->X % iValue, this->Y % iValue);
		}

		const CString	CPoint::ToString() const{
			return L"X: " + String::FromInt32(this->X) + L", Y: " + String::FromInt32(this->Y);
		}

		const CPoint&	CPoint::operator=(const CPoint& Point){
			this->Set(Point);
			return *this;
		}

		const CPoint	CPoint::operator+() const{
			return *this;
		}

		const CPoint	CPoint::operator-() const{
			return CPoint(-this->X, -this->Y);
		}

		const CPoint	CPoint::operator+(const CPoint& Point) const{
			return this->Add(Point);
		}

		const CPoint	CPoint::operator-(const CPoint& Point) const{
			return this->Sub(Point);
		}

		const CPoint	CPoint::operator*(const CPoint& Point) const{
			return this->Mul(Point);
		}

		const CPoint	CPoint::operator/(const CPoint& Point) const{
			return this->Div(Point);
		}

		const CPoint	CPoint::operator%(const CPoint& Point) const{
			return this->Mod(Point);
		}

		const CPoint	CPoint::operator*(const int iValue) const{
			return this->Mul(iValue);
		}

		const CPoint	CPoint::operator/(const int iValue) const{
			return this->Div(iValue);
		}

		const CPoint	CPoint::operator%(const int iValue) const{
			return this->Mod(iValue);
		}

		const CPoint&	CPoint::operator+=(const CPoint& Point){
			*this = this->Add(Point);
			return *this;
		}

		const CPoint&	CPoint::operator-=(const CPoint& Point){
			*this = this->Sub(Point);
			return *this;
		}

		const CPoint&	CPoint::operator*=(const CPoint& Point){
			*this = this->Mul(Point);
			return *this;
		}

		const CPoint&	CPoint::operator/=(const CPoint& Point){
			*this = this->Div(Point);
			return *this;
		}

		const CPoint&	CPoint::operator%=(const CPoint& Point){
			*this = this->Mod(Point);
			return *this;
		}

		const CPoint&	CPoint::operator*=(const int iValue){
			*this = this->Mul(iValue);
			return *this;
		}

		const CPoint&	CPoint::operator/=(const int iValue){
			*this = this->Div(iValue);
			return *this;
		}

		const CPoint&	CPoint::operator%=(const int iValue){
			*this = this->Mod(iValue);
			return *this;
		}

		const bool	CPoint::operator==(const CPoint& Point) const{
			return this->IsEqual(Point);
		}

		const bool	CPoint::operator!=(const CPoint& Point) const{
			return !this->IsEqual(Point);
		}

		const int&	CPoint::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		int&	CPoint::operator[](const unsigned uIndex){
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}
