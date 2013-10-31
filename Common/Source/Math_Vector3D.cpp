#include "../Include/Math_Vector.h"
#include "../Include/Math.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CVector3D::CVector3D() : CVector2D(), Z(0.0f){
		}

		CVector3D::CVector3D(const CVector3D& Vector) : CVector2D(Vector), Z(Vector.Z){
		}

		CVector3D::CVector3D(const CVector2D& Vector) : CVector2D(Vector), Z(0.0f){
		}

		CVector3D::CVector3D(const CVector2D& Vector, const float fZ) : CVector2D(Vector), Z(fZ){
		}

		CVector3D::CVector3D(const CPoint3D& Point) : CVector2D(Point), Z((float)Point.Z){
		}

		CVector3D::CVector3D(const float fValue) : CVector2D(fValue), Z(fValue){
		}

		CVector3D::CVector3D(const float fX, const float fY) : CVector2D(fX, fY), Z(0.0f){
		}

		CVector3D::CVector3D(const float fX, const float fY, const float fZ) : CVector2D(fX, fY), Z(fZ){
		}

		void	CVector3D::SetZero(){
			CVector2D::SetZero();
			this->Z = 0.0f;
		}

		void	CVector3D::Set(const CVector3D& Vector){
			this->Set(Vector.X, Vector.Y, Vector.Z);
		}

		void	CVector3D::Set(const float fValue){
			this->X = fValue;
			this->Y = fValue;
			this->Z = fValue;
		}

		void	CVector3D::Set(const float fX, const float fY){
			CVector2D::Set(fX, fY);
			this->Z = 0.0f;
		}

		void	CVector3D::Set(const float fX, const float fY, const float fZ){
			CVector2D::Set(fX, fY);
			this->Z = fZ;
		}

		const bool	CVector3D::IsZero() const{
			return this->X == 0.0f && this->Y == 0.0f && this->Z == 0.0f;
		}

		const bool	CVector3D::IsPartialZero() const{
			return this->X == 0.0f || this->Y == 0.0f || this->Z == 0.0f;
		}

		const bool	CVector3D::IsNearZero() const{
			return Math::IsNearZero(this->X) && Math::IsNearZero(this->Y) && Math::IsNearZero(this->Z);
		}

		const bool	CVector3D::IsEqual(const CVector3D& Vector) const{
			return this->X == Vector.X && this->Y == Vector.Y && this->Z == Vector.Z;
		}

		const bool	CVector3D::IsNearEqual(const CVector3D& Vector) const{
			return Math::IsNearEqual(this->X, Vector.X) && 
				Math::IsNearEqual(this->Y, Vector.Y) && 
				Math::IsNearEqual(this->Z, Vector.Z);
		}

		const float	CVector3D::GetLength() const{
			return SqRoot(this->GetLengthSq());
		}

		const float CVector3D::GetLengthSq() const{
			return Power2(this->X) + Power2(this->Y) + Power2(this->Z);
		}

		const CVector3D	CVector3D::GetNormalized() const{
			return this->Div(this->GetLength());
		}

		void	CVector3D::Normalize(){
			this->Set(this->GetNormalized());
		}

		const CVector3D	CVector3D::Add(const CVector3D& Vector) const{
			return CVector3D(this->X + Vector.X, this->Y + Vector.Y, this->Z + Vector.Z);
		}

		const CVector3D	CVector3D::Sub(const CVector3D& Vector) const{
			return CVector3D(this->X - Vector.X, this->Y - Vector.Y, this->Z - Vector.Z);
		}

		const CVector3D	CVector3D::Mul(const CVector3D& Vector) const{
			return CVector3D(this->X * Vector.X, this->Y * Vector.Y, this->Z * Vector.Z);
		}

		const CVector3D	CVector3D::Div(const CVector3D& Vector) const{
			if(Vector.IsPartialZero()){
				throw CB::Exception::CInvalidArgumentException(L"Vector", Vector.ToString(),
					L"Division by Zero", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return CVector3D(this->X / Vector.X, this->Y / Vector.Y, this->Z / Vector.Z);
		}

		const CVector3D	CVector3D::Mul(const float fValue) const{
			return CVector3D(this->X * fValue, this->Y * fValue, this->Z * fValue);
		}

		const CVector3D	CVector3D::Div(const float fValue) const{
			if(fValue == 0.0f){
				throw CB::Exception::CInvalidArgumentException(L"fValue", CB::String::FromFloat(fValue),
					L"Division by Zero", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return CVector3D(this->X / fValue, this->Y / fValue, this->Z / fValue);
		}

		const float	CVector3D::Dot(const CVector3D& Vector) const{
			return this->X * Vector.X + this->Y * Vector.Y + this->Z * Vector.Z;
		}

		const CVector3D	CVector3D::Cross(const CVector3D& Vector) const{
			return CVector3D(
				(this->Y * Vector.Z - this->Z * Vector.Y),
				-(this->X * Vector.Z - this->Z * Vector.X),
				(this->X * Vector.Y - this->Y * Vector.X));
		}

		const CB::CString	CVector3D::ToString() const{
			return L"X: " + String::FromFloat(this->X) + 
				L", Y: " + String::FromFloat(this->Y) +
				L", Z: " + String::FromFloat(this->Z);
		}

		const CPoint3D	CVector3D::ToPoint() const{
			return CPoint3D((int)this->X, (int)this->Y, (int)this->Z);
		}

		const float*	CVector3D::ToFloat() const{
			return &this->X;
		}

		void	CVector3D::ToFloat(float* pFloat) const{
			pFloat[0] = this->X;
			pFloat[1] = this->Y;
			pFloat[2] = this->Z;
		}

		const CVector3D&	CVector3D::operator=(const CVector3D& Vector){
			this->Set(Vector.X, Vector.Y, Vector.Z);
			return *this;
		}

		const CVector3D	CVector3D::operator+() const{
			return *this;
		}

		const CVector3D	CVector3D::operator-() const{
			return CVector3D(-this->X, -this->Y, -this->Z);
		}

		const CVector3D	CVector3D::operator+(const CVector3D& Vector) const{
			return this->Add(Vector);
		}

		const CVector3D	CVector3D::operator-(const CVector3D& Vector) const{
			return this->Sub(Vector);
		}

		const CVector3D	CVector3D::operator*(const CVector3D& Vector) const{
			return this->Mul(Vector);
		}

		const CVector3D	CVector3D::operator/(const CVector3D& Vector) const{
			return this->Div(Vector);
		}

		const CVector3D	CVector3D::operator*(const float fValue) const{
			return this->Mul(fValue);
		}

		const CVector3D	CVector3D::operator/(const float fValue) const{
			return this->Div(fValue);
		}

		const CVector3D&	CVector3D::operator+=(const CVector3D& Vector){
			*this = this->Add(Vector);
			return *this;
		}

		const CVector3D&	CVector3D::operator-=(const CVector3D& Vector){
			*this = this->Sub(Vector);
			return *this;
		}

		const CVector3D&	CVector3D::operator*=(const CVector3D& Vector){
			*this = this->Mul(Vector);
			return *this;
		}

		const CVector3D&	CVector3D::operator/=(const CVector3D& Vector){
			*this = this->Div(Vector);
			return *this;
		}

		const CVector3D&	CVector3D::operator*=(const float fValue){
			*this = this->Mul(fValue);
			return *this;
		}

		const CVector3D&	CVector3D::operator/=(const float fValue){
			*this = this->Div(fValue);
			return *this;
		}

		const bool	CVector3D::operator==(const CVector3D& Vector) const{
			return this->IsEqual(Vector);
		}

		const bool	CVector3D::operator!=(const CVector3D& Vector) const{
			return !this->IsEqual(Vector);
		}

		const float&	CVector3D::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		float&	CVector3D::operator[](const unsigned uIndex){
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}