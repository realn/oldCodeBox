#include "stdafx.h"
#include "../Include/Math_Point2D.h"
#include "../Include/Math_Size2D.h"
#include "../Include/Exception.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CPoint2D::CPoint2D() : 
			X(0), 
			Y(0)
		{}

		CPoint2D::CPoint2D(const CPoint2D& Point) : 
			X(Point.X), 
			Y(Point.Y)
		{}

		CPoint2D::CPoint2D(const CSize2D& Size) :
			X(Size.Width),
			Y(Size.Height)
		{}

		CPoint2D::CPoint2D(const int32 iValue) : 
			X(iValue), 
			Y(iValue)
		{}

		CPoint2D::CPoint2D(const int32 iX, const int32 iY) : 
			X(iX), 
			Y(iY)
		{}

		CPoint2D::CPoint2D(const Collection::ICountable<int32>& array) :
			X(0), Y(0)
		{
			if( array.GetLength() >= 2 ){
				X = array[0];
				Y = array[1];
			}
		}

		void	CPoint2D::SetZero(){
			this->X = 0;
			this->Y = 0;
		}

		void	CPoint2D::Set(const CPoint2D& Point){
			this->X = Point.X;
			this->Y = Point.Y;
		}

		void	CPoint2D::Set(const int32 iValue){
			this->X = iValue;
			this->Y = iValue;
		}

		void	CPoint2D::Set(const int32 iX, const int32 iY){
			this->X = iX;
			this->Y = iY;
		}

		const bool	CPoint2D::IsZero() const{
			return this->X == 0 && this->Y == 0;
		}

		const bool	CPoint2D::IsPartialZero() const{
			return this->X == 0 || this->Y == 0;
		}

		const bool	CPoint2D::IsEqual(const CPoint2D& Point) const{
			return this->X == Point.X && this->Y == Point.Y;
		}

		const CPoint2D	CPoint2D::Add(const CPoint2D& Point) const{
			return CPoint2D(this->X + Point.X, this->Y + Point.Y);
		}

		const CPoint2D	CPoint2D::Sub(const CPoint2D& Point) const{
			return CPoint2D(this->X - Point.X, this->Y - Point.Y);
		}

		const CPoint2D	CPoint2D::Mul(const CPoint2D& Point) const{
			return CPoint2D(this->X * Point.X, this->Y * Point.Y);
		}

		const CPoint2D	CPoint2D::Div(const CPoint2D& Point) const{
			return CPoint2D(this->X / Point.X, this->Y / Point.Y);
		}

		const CPoint2D	CPoint2D::Mod(const CPoint2D& Point) const{
			return CPoint2D(this->X % Point.X, this->Y % Point.Y);
		}

		const CPoint2D	CPoint2D::Mul(const int32 iValue) const{
			return CPoint2D(this->X * iValue, this->Y * iValue);
		}

		const CPoint2D	CPoint2D::Div(const int32 iValue) const{
			return CPoint2D(this->X / iValue, this->Y / iValue);
		}

		const CPoint2D	CPoint2D::Mod(const int32 iValue) const{
			return CPoint2D(this->X % iValue, this->Y % iValue);
		}

		const CString	CPoint2D::ToString() const{
			return L"X: " + String::ToString(this->X) + L", Y: " + String::ToString(this->Y);
		}

		const CPoint2D&	CPoint2D::operator=(const CPoint2D& Point){
			this->Set(Point);
			return *this;
		}

		const CPoint2D	CPoint2D::operator+() const{
			return *this;
		}

		const CPoint2D	CPoint2D::operator-() const{
			return CPoint2D(-this->X, -this->Y);
		}

		const CPoint2D	CPoint2D::operator+(const CPoint2D& Point) const{
			return this->Add(Point);
		}

		const CPoint2D	CPoint2D::operator-(const CPoint2D& Point) const{
			return this->Sub(Point);
		}

		const CPoint2D	CPoint2D::operator*(const CPoint2D& Point) const{
			return this->Mul(Point);
		}

		const CPoint2D	CPoint2D::operator/(const CPoint2D& Point) const{
			return this->Div(Point);
		}

		const CPoint2D	CPoint2D::operator%(const CPoint2D& Point) const{
			return this->Mod(Point);
		}

		const CPoint2D	CPoint2D::operator*(const int32 iValue) const{
			return this->Mul(iValue);
		}

		const CPoint2D	CPoint2D::operator/(const int32 iValue) const{
			return this->Div(iValue);
		}

		const CPoint2D	CPoint2D::operator%(const int32 iValue) const{
			return this->Mod(iValue);
		}

		const CPoint2D&	CPoint2D::operator+=(const CPoint2D& Point){
			*this = this->Add(Point);
			return *this;
		}

		const CPoint2D&	CPoint2D::operator-=(const CPoint2D& Point){
			*this = this->Sub(Point);
			return *this;
		}

		const CPoint2D&	CPoint2D::operator*=(const CPoint2D& Point){
			*this = this->Mul(Point);
			return *this;
		}

		const CPoint2D&	CPoint2D::operator/=(const CPoint2D& Point){
			*this = this->Div(Point);
			return *this;
		}

		const CPoint2D&	CPoint2D::operator%=(const CPoint2D& Point){
			*this = this->Mod(Point);
			return *this;
		}

		const CPoint2D&	CPoint2D::operator*=(const int32 iValue){
			*this = this->Mul(iValue);
			return *this;
		}

		const CPoint2D&	CPoint2D::operator/=(const int32 iValue){
			*this = this->Div(iValue);
			return *this;
		}

		const CPoint2D&	CPoint2D::operator%=(const int32 iValue){
			*this = this->Mod(iValue);
			return *this;
		}

		const bool	CPoint2D::operator==(const CPoint2D& Point) const{
			return this->IsEqual(Point);
		}

		const bool	CPoint2D::operator!=(const CPoint2D& Point) const{
			return !this->IsEqual(Point);
		}

		const int32&	CPoint2D::operator[](const uint32 uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		int32&	CPoint2D::operator[](const uint32 uIndex){
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		const Collection::CArray<int32, 2>	CPoint2D::ToArray() const{
			return Collection::CArray<int32, 2>(&X, 2);
		}
	}
}
