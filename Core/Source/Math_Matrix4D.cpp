#include "stdafx.h"
#include "../Include/Math_Matrix4D.h"
#include "../Include/Math_Matrix3D.h"
#include "../Include/Math_Vector4D.h"
#include "../Include/Math_Vector3D.h"
#include "../Include/Math_Vector2D.h"
#include "../Include/Exception.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CMatrix4D::CMatrix4D(){
		}

		CMatrix4D::CMatrix4D(const CMatrix4D& matrix) :
			Row1( matrix.Row1 ),
			Row2( matrix.Row2 ),
			Row3( matrix.Row3 ),
			Row4( matrix.Row4 )
		{}

		CMatrix4D::CMatrix4D(const CVector4D& vRow1, const CVector4D& vRow2, const CVector4D& vRow3, const CVector4D& vRow4) :
			Row1( vRow1 ),
			Row2( vRow2 ),
			Row3( vRow3 ),
			Row4( vRow4 )
		{}

		CMatrix4D::CMatrix4D(
			const float32 m11, const float32 m12, const float32 m13, const float32 m14,
			const float32 m21, const float32 m22, const float32 m23, const float32 m24,
			const float32 m31, const float32 m32, const float32 m33, const float32 m34,
			const float32 m41, const float32 m42, const float32 m43, const float32 m44
		) :
			Row1( m11, m12, m13, m14 ),
			Row2( m21, m22, m23, m24 ),
			Row3( m31, m32, m33, m34 ),
			Row4( m41, m42, m43, m44 )
		{}


		CMatrix4D::CMatrix4D( const float32 value ) :
			Row1( value, 0.0f, 0.0f, 0.0f ),
			Row2( 0.0f, value, 0.0f, 0.0f ),
			Row3( 0.0f, 0.0f, value, 0.0f ),
			Row4( 0.0f, 0.0f, 0.0f, value )
		{}

		CMatrix4D::CMatrix4D( const CMatrix3D& matrix ) :
			Row1( matrix.Row1, 0.0f ),
			Row2( matrix.Row2, 0.0f ),
			Row3( matrix.Row3, 0.0f ),
			Row4( 0.0f, 0.0f, 0.0f, 1.0f )
		{}

		CMatrix4D::CMatrix4D( const CMatrix3D& matrix, const float32 value ) :
			Row1( matrix.Row1, 0.0f ),
			Row2( matrix.Row2, 0.0f ),
			Row3( matrix.Row3, 0.0f ),
			Row4( 0.0f, 0.0f, 0.0f, value )
		{}

		CMatrix4D::CMatrix4D( const CMatrix3D& matrix, const CVector4D& trans ) :
			Row1( matrix.Row1, 0.0f ),
			Row2( matrix.Row2, 0.0f ),
			Row3( matrix.Row3, 0.0f ),
			Row4( trans )
		{}

		CMatrix4D::CMatrix4D( const Collection::ICountable<CVector4D>& array ){
			if( array.GetLength() >= 4 ){
				Row1 = array[0];
				Row2 = array[1];
				Row3 = array[2];
				Row4 = array[3];
			}
		}

		CMatrix4D::CMatrix4D( const Collection::ICountable<float32>& array ){
			if( array.GetLength() >= 16 ){
				Row1.Set( array[0], array[1], array[2], array[3] );
				Row2.Set( array[4], array[5], array[6], array[7] );
				Row3.Set( array[8], array[9], array[10], array[11] );
				Row4.Set( array[12], array[13], array[14], array[15] );
			}
		}

		void	CMatrix4D::Set(const CMatrix4D& matrix){
			Row1 = matrix.Row1;
			Row2 = matrix.Row2;
			Row3 = matrix.Row3;
			Row4 = matrix.Row4;
		}

		void	CMatrix4D::Set(const CVector4D& vRow1, const CVector4D& vRow2, const CVector4D& vRow3, const CVector4D& vRow4){
			this->Row1 = vRow1;
			this->Row2 = vRow2;
			this->Row3 = vRow3;
			this->Row4 = vRow4;
		}

		const uint32	CMatrix4D::GetSize() const{
			return 16;
		}

		const uint32	CMatrix4D::GetSizeInBytes() const{
			return this->GetSize() * sizeof(float32);
		}

		const bool		CMatrix4D::IsEmpty() const{
			return false;
		}

		const float32*	CMatrix4D::GetPointer() const{
			return &this->Row1.X;
		}

		float32*		CMatrix4D::GetPointer() {
			return &this->Row1.X;
		}

		const float32	CMatrix4D::Determinant() const{
			const float (*m)[4] = (const float(*)[4])&this->Row1.X;

			CMatrix3D minor1 = this->GetMinor( 0, 0 );
			CMatrix3D minor2 = this->GetMinor( 0, 1 );
			CMatrix3D minor3 = this->GetMinor( 0, 2 );
			CMatrix3D minor4 = this->GetMinor( 0, 3 );

			return 
				+ ( m[0][0] * minor1.Determinant() )
				- ( m[0][1] * minor2.Determinant() )
				+ ( m[0][2] * minor3.Determinant() )
				- ( m[0][3] * minor4.Determinant() );
		}
		
		const CVector4D	CMatrix4D::Transform(const CVector4D& vector) const{
			return CVector4D(
				this->GetColumn( 0 ).Dot( vector ),
				this->GetColumn( 1 ).Dot( vector ),
				this->GetColumn( 2 ).Dot( vector ),
				this->GetColumn( 3 ).Dot( vector )
				);
		}

		const CVector3D	CMatrix4D::Transform(const CVector3D& vector) const{
			return CVector3D( this->Transform( CVector4D( vector, 1.0f ) ) );
		}

		const CVector4D&	CMatrix4D::Get(const uint32 uIndex) const{
			if( uIndex >= 4 ){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
			const CVector4D* m = &Row1;

			return m[uIndex];
		}

		CVector4D&	CMatrix4D::Get(const uint32 uIndex){
			if( uIndex > 3 ){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
			CVector4D* m = &Row1;

			return m[uIndex];
		}

		const CVector4D	CMatrix4D::GetColumn(const uint32 uIndex) const{
			if(uIndex > 3){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}

			return CVector4D(this->Row1[uIndex], this->Row2[uIndex], this->Row3[uIndex], this->Row4[uIndex]);
		}

		const CMatrix3D	CMatrix4D::GetMinor(const uint32 uRow, const uint32 uCol) const{
			const float32 (*m)[4] = (const float32(*)[4])&this->Row1.X;
			CMatrix3D out;
			for( uint32 y = 0; y < 3; y++ ){
				for( uint32 x = 0; x < 3; x++ ){
					uint32 idY = y < uRow ? y : (y + 1);
					uint32 idX = x < uCol ? x : (x + 1);

					out[y][x] = m[idY][idX];
				}
			}

			return out;
		}

		const CMatrix4D	CMatrix4D::Add(const CMatrix4D& matrix) const{
			return CMatrix4D(
				this->Row1 + matrix.Row1,
				this->Row2 + matrix.Row2,
				this->Row3 + matrix.Row3,
				this->Row4 + matrix.Row4
				);
		}

		const CMatrix4D	CMatrix4D::Sub(const CMatrix4D& matrix) const{
			return CMatrix4D(
				this->Row1 - matrix.Row1,
				this->Row2 - matrix.Row2,
				this->Row3 - matrix.Row3,
				this->Row4 - matrix.Row4
				);
		}

		const CMatrix4D	CMatrix4D::Mul(const CMatrix4D& Matrix) const{
			const CVector4D col[] = {
				Matrix.GetColumn( 0 ),
				Matrix.GetColumn( 1 ),
				Matrix.GetColumn( 2 ),
				Matrix.GetColumn( 3 )
			};
			const CVector4D* row = &this->Row1;

			return CMatrix4D(
				row[0] * col[0][0] + row[1] * col[0][1] + row[2] * col[0][2] + row[3] * col[0][3],
				row[0] * col[1][0] + row[1] * col[1][1] + row[2] * col[1][2] + row[3] * col[1][3],
				row[0] * col[2][0] + row[1] * col[2][1] + row[2] * col[2][2] + row[3] * col[2][3],
				row[0] * col[3][0] + row[1] * col[3][1] + row[2] * col[3][2] + row[3] * col[3][3]
			);

		}

		const CMatrix4D	CMatrix4D::Add(const float32 value) const{
			return CMatrix4D(
				this->Row1 + value,
				this->Row2 + value,
				this->Row3 + value,
				this->Row4 + value
				);
		}

		const CMatrix4D	CMatrix4D::Sub(const float32 value) const{
			return CMatrix4D(
				this->Row1 - value,
				this->Row2 - value,
				this->Row3 - value,
				this->Row4 - value
				);
		}

		const CMatrix4D CMatrix4D::Mul(const float32 value) const{
			return CMatrix4D(
				this->Row1 * value,
				this->Row2 * value,
				this->Row3 * value,
				this->Row4 * value
				);
		}

		const CMatrix4D CMatrix4D::Div(const float32 value) const{
			if(value == 0.0f){
				throw CB::Exception::CNullArgumentException(L"fValue",
					L"Division by zero.", CR_INFO());
			}

			return CMatrix4D(
				this->Row1 / value,
				this->Row2 / value,
				this->Row3 / value,
				this->Row4 / value
				);
		}

		const CString	CMatrix4D::ToString() const{
			return 
				   L"Row1: (" + this->Row1.ToString() + 
				L"), Row2: (" + this->Row2.ToString() +
				L"), Row3: (" + this->Row3.ToString() +
				L"), Row4: (" + this->Row4.ToString() + L")";
		}

		const CMatrix4D& CMatrix4D::operator=(const CMatrix4D& Matrix){
			this->Set(Matrix);
			return *this;
		}

		const CMatrix4D	CMatrix4D::operator+(const CMatrix4D& Matrix) const{
			return this->Add(Matrix);
		}

		const CMatrix4D	CMatrix4D::operator-(const CMatrix4D& Matrix) const{
			return this->Sub(Matrix);
		}

		const CMatrix4D	CMatrix4D::operator*(const CMatrix4D& Matrix) const{
			return this->Mul(Matrix);
		}

		const CMatrix4D	CMatrix4D::operator+(const float32 fValue) const{
			return this->Add(fValue);
		}

		const CMatrix4D	CMatrix4D::operator-(const float32 fValue) const{
			return this->Sub(fValue);
		}

		const CMatrix4D	CMatrix4D::operator*(const float32 fValue) const{
			return this->Mul(fValue);
		}

		const CMatrix4D	CMatrix4D::operator/(const float32 fValue) const{
			return this->Div(fValue);
		}

		const CVector3D CMatrix4D::operator*(const CVector3D& vVector) const{
			return this->Transform(vVector);
		}

		const CVector4D	CMatrix4D::operator*(const CVector4D& vector) const {
			return this->Transform( vector );
		}

		const CMatrix4D&	CMatrix4D::operator+=(const CMatrix4D& Matrix){
			*this = this->Add(Matrix);
			return *this;
		}

		const CMatrix4D&	CMatrix4D::operator-=(const CMatrix4D& Matrix){
			*this = this->Sub(Matrix);
			return *this;
		}

		const CMatrix4D&	CMatrix4D::operator*=(const CMatrix4D& Matrix){
			*this = this->Mul(Matrix);
			return *this;
		}

		const CMatrix4D&	CMatrix4D::operator+=(const float32 fValue){
			*this = this->Add(fValue);
			return *this;
		}

		const CMatrix4D&	CMatrix4D::operator-=(const float32 fValue){
			*this = this->Sub(fValue);
			return *this;
		}

		const CMatrix4D&	CMatrix4D::operator*=(const float32 fValue){
			*this = this->Mul(fValue);
			return *this;
		}

		const CMatrix4D&	CMatrix4D::operator/=(const float32 fValue){
			*this = this->Div(fValue);
			return *this;
		}

		const CVector4D&	CMatrix4D::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		CVector4D&	CMatrix4D::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		const Collection::CArray<float32, 16>	CMatrix4D::ToArray() const{
			return Collection::CArray<float32, 16>( this->GetPointer(), this->GetSize() );
		}
	}
	//	Function implementations
}