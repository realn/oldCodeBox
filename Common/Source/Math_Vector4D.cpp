#include "../Include/Math_Vector.h"
#include "../Include/Math.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CVector4D::CVector4D() : CVector3D(), W(1.0f){
		}

		CVector4D::CVector4D(const CVector4D& Vector) : CVector3D(Vector), W(Vector.W){
		}

		CVector4D::CVector4D(const CVector3D& Vector) : CVector3D(Vector), W(1.0f){
		}

		CVector4D::CVector4D(const CVector3D& Vector, const float fW) : CVector3D(Vector), W(fW){
		}

		CVector4D::CVector4D(const CVector2D& Vector) : CVector3D(Vector), W(1.0f){
		}

		CVector4D::CVector4D(const CVector2D& Vector, const float fZ) : CVector3D(Vector, fZ), W(1.0f){
		}

		CVector4D::CVector4D(const CVector2D& Vector, const float fZ, const float fW) : CVector3D(Vector, fZ), W(fW){
		}

		CVector4D::CVector4D(const CPoint3D& Point) : CVector3D(Point), W(1.0f){
		}

		CVector4D::CVector4D(const CPoint3D& Point, const float fW) : CVector3D(Point), W(fW){
		}

		CVector4D::CVector4D(const float fValue) : CVector3D(fValue), W(1.0f){
		}

		CVector4D::CVector4D(const float fValue, const float fW) : CVector3D(fValue), W(fW){
		}

		CVector4D::CVector4D(const float fX, const float fY, const float fZ) : CVector3D(fX, fY, fZ), W(1.0f){
		}

		CVector4D::CVector4D(const float fX, const float fY, const float fZ, const float fW) : CVector3D(fX, fY, fZ), W(fW){
		}

		void	CVector4D::SetZero(){
			CVector3D::SetZero();
			this->W = 0.0f;
		}

		void	CVector4D::Set(const CVector4D& Vector){
			CVector3D::Set(Vector);
			this->W = Vector.W;
		}

		void	CVector4D::Set(const float fValue){
			CVector3D::Set(fValue);
			this->W = 1.0f;
		}

		void	CVector4D::Set(const float fValue, const float fW){
			CVector3D::Set(fValue);
			this->W = fW;
		}

		void	CVector4D::Set(const float fX, const float fY, const float fZ){
			CVector3D::Set(fX, fY, fZ);
			this->W = 1.0f;
		}

		void	CVector4D::Set(const float fX, const float fY, const float fZ, const float fW){
			CVector3D::Set(fX, fY, fZ);
			this->W = fW;
		}

		const bool	CVector4D::IsZero() const{
			return this->X == 0.0f && this->Y == 0.0f && this->Z == 0.0f && this->W == 0.0f;
		}

		const bool	CVector4D::IsPartialZero() const{
			return this->X == 0.0f || this->Y == 0.0f || this->Z == 0.0f || this->W == 0.0f;
		}

		const bool	CVector4D::IsNearZero() const{
			return Math::IsNearZero(this->X) && 
				Math::IsNearZero(this->Y) && 
				Math::IsNearZero(this->Z) &&
				Math::IsNearZero(this->W);
		}

		const bool	CVector4D::IsEqual(const CVector4D& Vector) const{
			return this->X == Vector.X && this->Y == Vector.Y && this->Z == Vector.Z && this->W == Vector.W;
		}

		const bool	CVector4D::IsNearEqual(const CVector4D& Vector) const{
			return Math::IsNearEqual(this->X, Vector.X) && 
				Math::IsNearEqual(this->Y, Vector.Y) && 
				Math::IsNearEqual(this->Z, Vector.Z) &&
				Math::IsNearEqual(this->W, Vector.W);
		}

		const float	CVector4D::GetLength() const{
			return SqRoot(this->GetLengthSq());
		}

		const float CVector4D::GetLengthSq() const{
			return Power2(this->X) + Power2(this->Y) + Power2(this->Z);
		}

		const CVector4D	CVector4D::GetNormalized() const{
			return CVector4D(CVector3D::Div(this->GetLength()), this->W);
		}

		void	CVector4D::Normalize(){
			this->Set(this->GetNormalized());
		}

		const CVector4D	CVector4D::Add(const CVector4D& Vector) const{
			return CVector4D(this->X + Vector.X, this->Y + Vector.Y, this->Z + Vector.Z, this->W + Vector.W);
		}

		const CVector4D	CVector4D::Sub(const CVector4D& Vector) const{
			return CVector4D(this->X - Vector.X, this->Y - Vector.Y, this->Z - Vector.Z, this->W - Vector.W);
		}

		const CVector4D	CVector4D::Mul(const CVector4D& Vector) const{
			return CVector4D(this->X * Vector.X, this->Y * Vector.Y, this->Z * Vector.Z, this->W * Vector.W);
		}

		const CVector4D	CVector4D::Div(const CVector4D& Vector) const{
			if(Vector.IsPartialZero()){
				throw CB::Exception::CInvalidArgumentException(L"Vector", Vector.ToString(),
					L"Division by Zero", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return CVector4D(this->X / Vector.X, this->Y / Vector.Y, this->Z / Vector.Z, this->W / Vector.W);
		}

		const CVector4D	CVector4D::Mul(const float fValue) const{
			return CVector4D(this->X * fValue, this->Y * fValue, this->Z * fValue, this->W * fValue);
		}

		const CVector4D	CVector4D::Div(const float fValue) const{
			if(fValue == 0.0f){
				throw CB::Exception::CInvalidArgumentException(L"fValue", String::FromFloat(fValue),
					L"Division by Zero", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return CVector4D(this->X / fValue, this->Y / fValue, this->Z / fValue, this->W / fValue);
		}

		const float	CVector4D::Dot(const CVector4D& Vector) const{
			return this->X * Vector.X + this->Y * Vector.Y + this->Z * Vector.Z + this->W * Vector.W;
		}

		const CB::CString	CVector4D::ToString() const{
			return L"X: " + String::FromFloat(this->X) + 
				L", Y: " + String::FromFloat(this->Y) +
				L", Z: " + String::FromFloat(this->Z) + 
				L", W: " + String::FromFloat(this->W);
		}

		const CPoint3D	CVector4D::ToPoint() const{
			return CPoint3D((int)this->X, (int)this->Y, (int)this->Z);
		}

		const float*	CVector4D::ToFloat() const{
			return &this->X;
		}

		void	CVector4D::ToFloat(float* pFloat) const{
			pFloat[0] = this->X;
			pFloat[1] = this->Y;
			pFloat[2] = this->Z;
			pFloat[3] = this->W;
		}

		const CVector4D&	CVector4D::operator=(const CVector4D& Vector){
			this->Set(Vector);
			return *this;
		}

		const CVector4D	CVector4D::operator+() const{
			return *this;
		}

		const CVector4D	CVector4D::operator-() const{
			return CVector4D(-this->X, -this->Y, -this->Z, this->W);
		}

		const CVector4D	CVector4D::operator+(const CVector4D& Vector) const{
			return this->Add(Vector);
		}

		const CVector4D	CVector4D::operator-(const CVector4D& Vector) const{
			return this->Sub(Vector);
		}

		const CVector4D	CVector4D::operator*(const CVector4D& Vector) const{
			return this->Mul(Vector);
		}

		const CVector4D	CVector4D::operator/(const CVector4D& Vector) const{
			return this->Div(Vector);
		}

		const CVector4D	CVector4D::operator*(const float fValue) const{
			return this->Mul(fValue);
		}

		const CVector4D	CVector4D::operator/(const float fValue) const{
			return this->Div(fValue);
		}

		const CVector4D&	CVector4D::operator+=(const CVector4D& Vector){
			*this = this->Add(Vector);
			return *this;
		}

		const CVector4D&	CVector4D::operator-=(const CVector4D& Vector){
			*this = this->Sub(Vector);
			return *this;
		}

		const CVector4D&	CVector4D::operator*=(const CVector4D& Vector){
			*this = this->Mul(Vector);
			return *this;
		}

		const CVector4D&	CVector4D::operator/=(const CVector4D& Vector){
			*this = this->Div(Vector);
			return *this;
		}

		const CVector4D&	CVector4D::operator*=(const float fValue){
			*this = this->Mul(fValue);
			return *this;
		}

		const CVector4D&	CVector4D::operator/=(const float fValue){
			*this = this->Div(fValue);
			return *this;
		}

		const bool	CVector4D::operator==(const CVector4D& Vector) const{
			return this->IsEqual(Vector);
		}

		const bool	CVector4D::operator!=(const CVector4D& Vector) const{
			return !this->IsEqual(Vector);
		}

		const float&	CVector4D::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			case 3:	return this->W;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		float&	CVector4D::operator[](const unsigned uIndex){
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			case 3:	return this->W;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}