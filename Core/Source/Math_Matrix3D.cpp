#include "stdafx.h"
#include "../Include/Math_Matrix3D.h"
#include "../Include/Math_Matrix4D.h"
#include "../Include/Exception.h"
#include "../Include/CBString.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CMatrix3D::CMatrix3D(){
		}

		CMatrix3D::CMatrix3D(const CMatrix3D& matrix) :
			Row1( matrix.Row1 ),
			Row2( matrix.Row2 ),
			Row3( matrix.Row3 )
		{}

		CMatrix3D::CMatrix3D(const CVector3D& row1, const CVector3D& row2, const CVector3D& row3) :
			Row1(row1),
			Row2(row2),
			Row3(row3)
		{}

		CMatrix3D::CMatrix3D(
			const float32 m11, const float32 m12, const float32 m13,
			const float32 m21, const float32 m22, const float32 m23,
			const float32 m31, const float32 m32, const float32 m33
			) :
			Row1( m11, m12, m13 ),
			Row2( m21, m22, m23 ),
			Row3( m31, m32, m33 )
		{}

		CMatrix3D::CMatrix3D(const float32 value) :
			Row1( value, 0.0f, 0.0f ),
			Row2( 0.0f, value, 0.0f ),
			Row3( 0.0f, 0.0f, value )
		{}

		CMatrix3D::CMatrix3D(const CMatrix4D& matrix) :
			Row1( matrix.Row1 ),
			Row2( matrix.Row2 ),
			Row3( matrix.Row3 )
		{}

		CMatrix3D::CMatrix3D(const Collection::ICountable<CVector3D>& array){
			if( array.GetLength() >= 3 ){
				Row1 = array[0];
				Row2 = array[1];
				Row3 = array[2];
			}
		}

		CMatrix3D::CMatrix3D(const Collection::ICountable<float32>& array){
			if( array.GetLength() >= 9 ){
				Row1.Set( array[0], array[1], array[2] );
				Row2.Set( array[3], array[4], array[5] );
				Row3.Set( array[6], array[7], array[8] );
			}
		}

		void	CMatrix3D::Set(const CMatrix3D& matrix){
			this->Row1 = matrix.Row1;
			this->Row2 = matrix.Row2;
			this->Row3 = matrix.Row3;
		}

		void	CMatrix3D::Set(const CVector3D& row1, const CVector3D& row2, const CVector3D& row3){
			this->Row1 = row1;
			this->Row2 = row2;
			this->Row3 = row3;
		}

		const CVector3D	CMatrix3D::Transform( const CVector3D& vector ) const {
			return CVector3D(
				this->GetColumn( 0 ).Dot( vector ),
				this->GetColumn( 1 ).Dot( vector ),
				this->GetColumn( 2 ).Dot( vector )
				);
		}

		const float32	CMatrix3D::Determinant() const{
			const float32 (*m)[3] = (float (*)[3])(&this->Row1.X);

			return 
				  m[0][0] * ( m[1][1] * m[2][2] - m[1][2] * m[2][1] )
				- m[0][1] * ( m[1][0] * m[2][2] - m[1][2] * m[2][0] )
				+ m[0][2] * ( m[1][0] * m[2][1] - m[1][1] * m[2][0] );
		}

		const CVector3D& CMatrix3D::Get(const uint32 uIndex) const{
			if( uIndex >= 3 ){
				CR_THROW(L"Index out of range.");
			}
			const CVector3D* r = &Row1;
			return r[uIndex];
		}

		CVector3D&	CMatrix3D::Get(const uint32 uIndex){
			if( uIndex >= 3 ){
				CR_THROW(L"Index out of range.");
			}
			CVector3D* r = &Row1;
			return r[uIndex];
		}

		const CVector3D	CMatrix3D::GetColumn( const uint32 uIndex ) const{
			const float32 (*m)[3] = (float32 (*) [3])(&this->Row1.X);
			return CVector3D( m[0][uIndex], m[1][uIndex], m[2][uIndex]);
		}

		const float32*	CMatrix3D::GetPointer() const{
			return &Row1.X;
		}

		float32*	CMatrix3D::GetPointer(){
			return &Row1.X;
		}

		const uint32	CMatrix3D::GetSize() const{
			return 9;
		}

		const uint32	CMatrix3D::GetSizeInBytes() const{
			return this->GetSize() * sizeof(float32);
		}

		const CMatrix3D	CMatrix3D::Add(const CMatrix3D& matrix) const{
			return CMatrix3D(
				this->Row1 + matrix.Row1,
				this->Row2 + matrix.Row2,
				this->Row3 + matrix.Row3
				);
		}

		const CMatrix3D CMatrix3D::Sub(const CMatrix3D& matrix) const{
			return CMatrix3D(
				this->Row1 - matrix.Row1,
				this->Row2 - matrix.Row2,
				this->Row3 - matrix.Row3
				);
		}

		const CMatrix3D	CMatrix3D::Mul(const CMatrix3D& matrix) const{
			const CVector3D col[] = {
				matrix.GetColumn( 0 ),
				matrix.GetColumn( 1 ),
				matrix.GetColumn( 2 )
			};
			const CVector3D* row = &this->Row1;

			return CMatrix3D(
				row[0] * col[0][0] + row[1] * col[0][1] + row[2] * col[0][2],
				row[0] * col[1][0] + row[1] * col[1][1] + row[2] * col[1][2],
				row[0] * col[2][0] + row[1] * col[2][1] + row[2] * col[2][2]
				);
		}

		const CMatrix3D CMatrix3D::Add(const float32 value) const{
			return CMatrix3D(
				this->Row1 + value,
				this->Row2 + value,
				this->Row3 + value
				);
		}

		const CMatrix3D CMatrix3D::Sub(const float32 value) const{
			return CMatrix3D(
				this->Row1 - value,
				this->Row2 - value,
				this->Row3 - value
				);
		}

		const CMatrix3D CMatrix3D::Mul(const float32 value) const{
			return CMatrix3D(
				this->Row1 * value,
				this->Row2 * value,
				this->Row3 * value
				);
		}

		const CMatrix3D CMatrix3D::Div(const float32 value) const{
			return CMatrix3D(
				this->Row1 / value,
				this->Row2 / value,
				this->Row3 / value
				);
		}

		const bool	CMatrix3D::IsEqual(const CMatrix3D& matrix) const{
			return 
				(this->Row1 == matrix.Row1) && 
				(this->Row2 == matrix.Row2) && 
				(this->Row3 == matrix.Row3);
		}

		const CMatrix3D CMatrix3D::operator+() const{
			return *this;
		}

		const CMatrix3D CMatrix3D::operator-() const{
			return CMatrix3D( -Row1, -Row2, -Row3 );
		}

		const CMatrix3D	CMatrix3D::operator+(const CMatrix3D& matrix) const{
			return this->Add(matrix);
		}

		const CMatrix3D	CMatrix3D::operator-(const CMatrix3D& matrix) const{
			return this->Sub(matrix);
		}

		const CMatrix3D	CMatrix3D::operator*(const CMatrix3D& matrix) const{
			return this->Mul(matrix);
		}

		const CVector3D CMatrix3D::operator*(const CVector3D& vector) const{
			return this->Transform(vector);
		}

		const CMatrix3D	CMatrix3D::operator+(const float32 value) const{
			return this->Add(value);
		}

		const CMatrix3D	CMatrix3D::operator-(const float32 value) const{
			return this->Sub(value);
		}

		const CMatrix3D	CMatrix3D::operator*(const float32 value) const{
			return this->Mul(value);
		}

		const CMatrix3D	CMatrix3D::operator/(const float32 value) const{
			return this->Div(value);
		}

		const CMatrix3D& CMatrix3D::operator+=(const CMatrix3D& matrix){
			this->Set(this->Add(matrix));
			return *this;
		}

		const CMatrix3D& CMatrix3D::operator-=(const CMatrix3D& matrix){
			this->Set(this->Sub(matrix));
			return *this;
		}

		const CMatrix3D& CMatrix3D::operator*=(const CMatrix3D& matrix){
			this->Set(this->Mul(matrix));
			return *this;
		}

		const CMatrix3D& CMatrix3D::operator+=(const float32 value){
			this->Set(this->Add(value));
			return *this;
		}

		const CMatrix3D& CMatrix3D::operator-=(const float32 value){
			this->Set(this->Sub(value));
			return *this;
		}

		const CMatrix3D& CMatrix3D::operator*=(const float32 value){
			this->Set(this->Mul(value));
			return *this;
		}

		const CMatrix3D& CMatrix3D::operator/=(const float32 value){
			this->Set(this->Div(value));
			return *this;
		}

		const bool	CMatrix3D::operator==(const CMatrix3D& matrix) const{
			return this->IsEqual(matrix);
		}

		const bool	CMatrix3D::operator!=(const CMatrix3D& matrix) const{
			return !this->IsEqual(matrix);
		}

		const CVector3D&	CMatrix3D::operator[](const uint32 uIndex) const{
			return this->Get( uIndex );
		}

		CVector3D&	CMatrix3D::operator[](const uint32 uIndex){
			return this->Get( uIndex );
		}

		const CString	CMatrix3D::ToString() const{
			return L"Row1: (" + Row1.ToString() + 
				L"), Row2: (" + Row2.ToString() +
				L"), Row3: (" + Row3.ToString() + L")";
		}

		const Collection::CArray<float32, 9>	CMatrix3D::ToArray() const{
			return Collection::CArray<float32, 9>( this->GetPointer(), this->GetSize() );
		}
	}
}