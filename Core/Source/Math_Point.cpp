#include "stdafx.h"
#include "../Include/Math_Point.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CPoint::CPoint() : 
			X(0), 
			Y(0)
		{}

		CPoint::CPoint(const CPoint& Point) : 
			X(Point.X), 
			Y(Point.Y)
		{}

		CPoint::CPoint(const int32 iValue) : 
			X(iValue), 
			Y(iValue)
		{}

		CPoint::CPoint(const int32 iX, const int32 iY) : 
			X(iX), 
			Y(iY)
		{}

		void	CPoint::SetZero(){
			this->X = 0;
			this->Y = 0;
		}

		void	CPoint::Set(const CPoint& Point){
			this->X = Point.X;
			this->Y = Point.Y;
		}

		void	CPoint::Set(const int32 iValue){
			this->X = iValue;
			this->Y = iValue;
		}

		void	CPoint::Set(const int32 iX, const int32 iY){
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

		const CPoint	CPoint::Mul(const int32 iValue) const{
			return CPoint(this->X * iValue, this->Y * iValue);
		}

		const CPoint	CPoint::Div(const int32 iValue) const{
			return CPoint(this->X / iValue, this->Y / iValue);
		}

		const CPoint	CPoint::Mod(const int32 iValue) const{
			return CPoint(this->X % iValue, this->Y % iValue);
		}

		const CString	CPoint::ToString() const{
			return L"X: " + String::ToString(this->X) + L", Y: " + String::ToString(this->Y);
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

		const CPoint	CPoint::operator*(const int32 iValue) const{
			return this->Mul(iValue);
		}

		const CPoint	CPoint::operator/(const int32 iValue) const{
			return this->Div(iValue);
		}

		const CPoint	CPoint::operator%(const int32 iValue) const{
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

		const CPoint&	CPoint::operator*=(const int32 iValue){
			*this = this->Mul(iValue);
			return *this;
		}

		const CPoint&	CPoint::operator/=(const int32 iValue){
			*this = this->Div(iValue);
			return *this;
		}

		const CPoint&	CPoint::operator%=(const int32 iValue){
			*this = this->Mod(iValue);
			return *this;
		}

		const bool	CPoint::operator==(const CPoint& Point) const{
			return this->IsEqual(Point);
		}

		const bool	CPoint::operator!=(const CPoint& Point) const{
			return !this->IsEqual(Point);
		}

		const int32&	CPoint::operator[](const uint32 uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		int32&	CPoint::operator[](const uint32 uIndex){
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}
	}
}
