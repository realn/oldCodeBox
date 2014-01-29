#include "../Include/Math_Vector.h"
#include "../Include/Math.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CVector4D::CVector4D() : 
			X(0.0f),
			Y(0.0f),
			Z(0.0f), 
			W(1.0f)
		{}

		CVector4D::CVector4D(const CVector4D& Vector) : 
			X(Vector.X),
			Y(Vector.Y),
			Z(Vector.Z), 
			W(Vector.W)
		{}

		CVector4D::CVector4D(const CVector3D& Vector) : 
			X(Vector.X),
			Y(Vector.Y),
			Z(Vector.Z), 
			W(1.0f)
		{}

		CVector4D::CVector4D(const CVector3D& Vector, const float32 fW) : 
			X(Vector.X),
			Y(Vector.Y),
			Z(Vector.Z), 
			W(fW)
		{}

		CVector4D::CVector4D(const CVector2D& Vector) : 
			X(Vector.X),
			Y(Vector.Y), 
			Z(0.0f),
			W(1.0f)
		{}

		CVector4D::CVector4D(const CVector2D& Vector, const float32 fZ) : 
			X(Vector.X),
			Y(Vector.Y),
			Z(fZ), 
			W(1.0f)
		{}

		CVector4D::CVector4D(const CVector2D& Vector, const float32 fZ, const float32 fW) : 
			X(Vector.X),
			Y(Vector.Y),
			Z(fZ), 
			W(fW)
		{}

		CVector4D::CVector4D(const CPoint3D& Point) : 
			X((float32)Point.X),
			Y((float32)Point.Y),
			Z((float32)Point.Z),
			W(1.0f)
		{}

		CVector4D::CVector4D(const CPoint3D& Point, const float32 fW) : 
			X((float32)Point.X),
			Y((float32)Point.Y),
			Z((float32)Point.Z),
			W(fW)
		{}

		CVector4D::CVector4D(const float32 fValue) : 
			X(fValue),
			Y(fValue),
			Z(fValue),
			W(1.0f)
		{}

		CVector4D::CVector4D(const float32 fValue, const float32 fW) : 
			X(fValue),
			Y(fValue),
			Z(fValue),
			W(fW)
		{}

		CVector4D::CVector4D(const float32 fX, const float32 fY, const float32 fZ) : 
			X(fX),
			Y(fY), 
			Z(fZ), 
			W(1.0f)
		{}

		CVector4D::CVector4D(const float32 fX, const float32 fY, const float32 fZ, const float32 fW) : 
			X(fX), 
			Y(fY), 
			Z(fZ), 
			W(fW)
		{}

		void	CVector4D::SetZero(){
			this->X = 0.0f;
			this->Y = 0.0f;
			this->Z = 0.0f;
			this->W = 0.0f;
		}

		void	CVector4D::Set(const CVector4D& Vector){
			this->X = Vector.X;
			this->Y = Vector.Y;
			this->Z = Vector.Z;
			this->W = Vector.W;
		}

		void	CVector4D::Set(const float32 fValue){
			this->X = fValue;
			this->Y = fValue;
			this->Z = fValue;
			this->W = 1.0f;
		}

		void	CVector4D::Set(const float32 fValue, const float32 fW){
			this->X = fValue;
			this->Y = fValue;
			this->Z = fValue;
			this->W = fW;
		}

		void	CVector4D::Set(const float32 fX, const float32 fY, const float32 fZ){
			this->X = fX;
			this->Y = fY;
			this->Z = fZ;
			this->W = 1.0f;
		}

		void	CVector4D::Set(const float32 fX, const float32 fY, const float32 fZ, const float32 fW){
			this->X = fX;
			this->Y = fY;
			this->Z = fZ;
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

		const bool	CVector4D::IsEmpty() const{
			return false;
		}

		const uint32	CVector4D::GetLength() const{
			return 4;
		}

		const uint32	CVector4D::GetSizeInBytes() const{
			return this->GetLength() * sizeof(float32);
		}

		const float32&	CVector4D::Get(const uint32 uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			case 3:	return this->W;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		float32&	CVector4D::Get(const uint32 uIndex){
			switch (uIndex)
			{
			case 0:	return this->X;
			case 1:	return this->Y;
			case 2:	return this->Z;
			case 3:	return this->W;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		const float32*	CVector4D::GetPointer() const{
			return &this->X;
		}

		float32*	CVector4D::GetPointer(){
			return &this->X;
		}

		const float32	CVector4D::GetVectorLength() const{
			return SqRoot(this->GetVectorLengthSq());
		}

		const float32 CVector4D::GetVectorLengthSq() const{
			return Power2(this->X) + Power2(this->Y) + Power2(this->Z);
		}

		const CVector4D	CVector4D::GetNormalized() const{
			float32 fLen = this->GetVectorLength();
			return CVector4D(X / fLen, Y / fLen, Z / fLen, this->W);
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
					L"Division by Zero", CR_INFO());
			}

			return CVector4D(this->X / Vector.X, this->Y / Vector.Y, this->Z / Vector.Z, this->W / Vector.W);
		}

		const CVector4D	CVector4D::Mul(const float32 fValue) const{
			return CVector4D(this->X * fValue, this->Y * fValue, this->Z * fValue, this->W * fValue);
		}

		const CVector4D	CVector4D::Div(const float32 fValue) const{
			if(fValue == 0.0f){
				throw CB::Exception::CInvalidArgumentException(L"fValue", String::ToString(fValue),
					L"Division by Zero", CR_INFO());
			}

			return CVector4D(this->X / fValue, this->Y / fValue, this->Z / fValue, this->W / fValue);
		}

		const float32	CVector4D::Dot(const CVector4D& Vector) const{
			return this->X * Vector.X + this->Y * Vector.Y + this->Z * Vector.Z + this->W * Vector.W;
		}

		const CB::CString	CVector4D::ToString() const{
			return L"X: " + String::ToString(this->X) + 
				L", Y: " + String::ToString(this->Y) +
				L", Z: " + String::ToString(this->Z) + 
				L", W: " + String::ToString(this->W);
		}

		const CPoint3D	CVector4D::ToPoint() const{
			return CPoint3D((int)this->X, (int)this->Y, (int)this->Z);
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

		const CVector4D	CVector4D::operator*(const float32 fValue) const{
			return this->Mul(fValue);
		}

		const CVector4D	CVector4D::operator/(const float32 fValue) const{
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

		const CVector4D&	CVector4D::operator*=(const float32 fValue){
			*this = this->Mul(fValue);
			return *this;
		}

		const CVector4D&	CVector4D::operator/=(const float32 fValue){
			*this = this->Div(fValue);
			return *this;
		}

		const bool	CVector4D::operator==(const CVector4D& Vector) const{
			return this->IsEqual(Vector);
		}

		const bool	CVector4D::operator!=(const CVector4D& Vector) const{
			return !this->IsEqual(Vector);
		}

		const float32&	CVector4D::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		float32&	CVector4D::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		CVector4D::operator const CVector3D() const{
			return CVector3D(this->X, this->Y, this->Z);
		}

		CVector4D::operator const CB::Collection::CArray<float32, 4U>() const{
			return Collection::CArray<float32, 4>(this->GetPointer(), this->GetLength());
		}
	}
}