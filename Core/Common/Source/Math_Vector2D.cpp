#include "../Include/Math_Vector.h"
#include "../Include/Math.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CVector2D::CVector2D() : 
			X(0.0f), 
			Y(0.0f)
		{}

		CVector2D::CVector2D(const CVector2D& Vector) : 
			X(Vector.X), 
			Y(Vector.Y)
		{}

		CVector2D::CVector2D(const CPoint& Point) : 
			X((float32)Point.X), 
			Y((float32)Point.Y)
		{}

		CVector2D::CVector2D(const float32 fValue) : 
			X(fValue), 
			Y(fValue)
		{}

		CVector2D::CVector2D(const float32 fX, const float32 fY) : 
			X(fX), 
			Y(fY)
		{}

		void	CVector2D::SetZero(){
			this->X = 0.0f;
			this->Y = 0.0f;
		}

		void	CVector2D::Set(const CVector2D& Vector){
			this->X = Vector.X;
			this->Y = Vector.Y;
		}

		void	CVector2D::Set(const float32 fValue){
			this->X = fValue;
			this->Y = fValue;
		}

		void	CVector2D::Set(const float32 fX, const float32 fY){
			this->X = fX;
			this->Y = fY;
		}

		const bool	CVector2D::IsZero() const{
			return this->X == 0.0f && this->Y == 0.0f;
		}

		const bool	CVector2D::IsPartialZero() const{
			return this->X == 0.0f || this->Y == 0.0f;
		}

		const bool	CVector2D::IsNearZero() const{
			return Math::IsNearZero(this->X) && Math::IsNearZero(this->Y);
		}

		const bool	CVector2D::IsEqual(const CVector2D& Vector) const{
			return this->X == Vector.X && this->Y == Vector.Y;
		}

		const bool	CVector2D::IsNearEqual(const CVector2D& Vector) const{
			return Math::IsNearEqual(this->X, Vector.X) && Math::IsNearEqual(this->Y, Vector.Y);
		}

		const bool	CVector2D::IsEmpty() const{
			return false;
		}

		const uint32	CVector2D::GetLength() const{
			return 2;
		}

		const uint32	CVector2D::GetSizeInBytes() const{
			return this->GetLength() * sizeof(float32);
		}

		const float32&	CVector2D::Get(const uint32 uIndex) const{
			switch (uIndex){
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		float32&	CVector2D::Get(const uint32 uIndex){
			switch (uIndex){
			case 0:	return this->X;
			case 1:	return this->Y;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		const float32*	CVector2D::GetPointer() const{
			return &this->X;
		}

		float32*	CVector2D::GetPointer(){
			return &this->X;
		}

		const float32	CVector2D::GetVectorLength() const{
			return SqRoot(this->GetVectorLengthSq());
		}

		const float32 CVector2D::GetVectorLengthSq() const{
			return Power2(this->X) + Power2(this->Y);
		}

		const CVector2D	CVector2D::GetNormalized() const{
			return this->Div(this->GetVectorLength());
		}

		void	CVector2D::Normalize(){
			this->Set(this->GetNormalized());
		}

		const CVector2D	CVector2D::Add(const CVector2D& Vector) const{
			return CVector2D(this->X + Vector.X, this->Y + Vector.Y);
		}

		const CVector2D	CVector2D::Sub(const CVector2D& Vector) const{
			return CVector2D(this->X - Vector.X, this->Y - Vector.Y);
		}

		const CVector2D	CVector2D::Mul(const CVector2D& Vector) const{
			return CVector2D(this->X * Vector.X, this->Y * Vector.Y);
		}

		const CVector2D	CVector2D::Div(const CVector2D& Vector) const{
			if(Vector.IsPartialZero()){
				throw Exception::CInvalidArgumentException(L"Vector", Vector.ToString(),
					L"Division by Zero", CR_INFO());
			}

			return CVector2D(this->X / Vector.X, this->Y / Vector.Y);
		}

		const CVector2D	CVector2D::Mul(const float32 fValue) const{
			return CVector2D(this->X * fValue, this->Y * fValue);
		}

		const CVector2D	CVector2D::Div(const float32 fValue) const{
			if(fValue == 0.0f){
				throw Exception::CInvalidArgumentException(L"fValue", CB::String::ToString(fValue),
					L"Division by Zero", CR_INFO());
			}

			return CVector2D(this->X / fValue, this->Y / fValue);
		}

		const float32	CVector2D::Dot(const CVector2D& Vector) const{
			return this->X * Vector.X + this->Y * Vector.Y;
		}

		const CB::CString	CVector2D::ToString() const{
			return L"X: " + String::ToString(this->X) + L", Y: " + String::ToString(this->Y);
		}

		const CPoint	CVector2D::ToPoint() const{
			return CPoint((int)this->X, (int)this->Y);
		}

		const CVector2D&	CVector2D::operator=(const CVector2D& Vector){
			this->Set(Vector);
			return *this;
		}

		const CVector2D	CVector2D::operator+() const{
			return *this;
		}

		const CVector2D	CVector2D::operator-() const{
			return CVector2D(-this->X, -this->Y);
		}

		const CVector2D	CVector2D::operator+(const CVector2D& Vector) const{
			return this->Add(Vector);
		}

		const CVector2D	CVector2D::operator-(const CVector2D& Vector) const{
			return this->Sub(Vector);
		}

		const CVector2D	CVector2D::operator*(const CVector2D& Vector) const{
			return this->Mul(Vector);
		}

		const CVector2D	CVector2D::operator/(const CVector2D& Vector) const{
			return this->Div(Vector);
		}

		const CVector2D	CVector2D::operator*(const float32 fValue) const{
			return this->Mul(fValue);
		}

		const CVector2D	CVector2D::operator/(const float32 fValue) const{
			return this->Div(fValue);
		}

		const CVector2D&	CVector2D::operator+=(const CVector2D& Vector){
			this->Set(this->Add(Vector));
			return *this;
		}

		const CVector2D&	CVector2D::operator-=(const CVector2D& Vector){
			this->Set(this->Sub(Vector));
			return *this;
		}

		const CVector2D&	CVector2D::operator*=(const CVector2D& Vector){
			this->Set(this->Mul(Vector));
			return *this;
		}

		const CVector2D&	CVector2D::operator/=(const CVector2D& Vector){
			this->Set(this->Div(Vector));
			return *this;
		}

		const CVector2D&	CVector2D::operator*=(const float32 fValue){
			this->Set(this->Mul(fValue));
			return *this;
		}

		const CVector2D&	CVector2D::operator/=(const float32 fValue){
			this->Set(this->Div(fValue));
			return *this;
		}

		const bool	CVector2D::operator==(const CVector2D& Vector) const{
			return this->IsEqual(Vector);
		}

		const bool	CVector2D::operator!=(const CVector2D& Vector) const{
			return !this->IsEqual(Vector);
		}

		const float32&	CVector2D::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		float32&	CVector2D::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		CVector2D::operator const CB::Collection::CArray<float32, 2U>() const{
			return Collection::CArray<float32, 2>(this->GetPointer(), this->GetLength());
		}
	}
}