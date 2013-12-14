#include "../Include/Math_Matrix.h"
#include "../Include/Exception.h"
#include "../Include/Memory.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>

//#pragma comment(lib, "d3dx9.lib")
//#include <d3dx9.h>
//#undef getmessage

namespace CB{
	namespace Math{
		const CMatrix	FromGLM(const glm::mat4& matrix){
			return CMatrix(glm::value_ptr(glm::transpose(matrix)));
		}

		const glm::mat4	ToGLM(const CMatrix& matrix){
			return glm::transpose(glm::make_mat4(matrix.GetMatrixPointer()));
		}

		CMatrix::CMatrix(){
			Memory::SetZero(&this->Row[0], 4*4*sizeof(float32));
		}

		CMatrix::CMatrix(const float32* pMatrix){
			Memory::Copy(pMatrix, &this->Row[0], 4*4*sizeof(float32));
		}

		CMatrix::CMatrix(const CMatrix& Matrix){
			this->Set(Matrix);
		}

		CMatrix::CMatrix(const CVector4D& vRow1, const CVector4D& vRow2, const CVector4D& vRow3, const CVector4D& vRow4){
			this->Set(vRow1, vRow2, vRow3, vRow4);
		}

		void	CMatrix::SetZero(){
			this->Row[0].Set(0.0f, 0.0f, 0.0f, 0.0f);
			this->Row[1].Set(0.0f, 0.0f, 0.0f, 0.0f);
			this->Row[2].Set(0.0f, 0.0f, 0.0f, 0.0f);
			this->Row[3].Set(0.0f, 0.0f, 0.0f, 0.0f);
		}

		void	CMatrix::SetIdentity(){
			this->Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
			this->Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
			this->Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
			this->Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
		}

		void	CMatrix::Set(const CMatrix& Matrix){
			this->Row[0] = Matrix[0];
			this->Row[1] = Matrix[1];
			this->Row[2] = Matrix[2];
			this->Row[3] = Matrix[3];
		}

		void	CMatrix::Set(const float32* pMatrix){
			Memory::Copy(pMatrix, &this->Row[0], 4*4*sizeof(float32));
		}

		void	CMatrix::Set(const CVector4D& vRow1, const CVector4D& vRow2, const CVector4D& vRow3, const CVector4D& vRow4){
			this->Row[0] = vRow1;
			this->Row[1] = vRow2;
			this->Row[2] = vRow3;
			this->Row[3] = vRow4;
		}

		void	CMatrix::SetTranslation(const CVector3D& vPos){
			this->SetIdentity();
			this->Row[3] = CVector4D(vPos, 1.0f);
		}

		void	CMatrix::SetTranslation(const float32 fX, const float32 fY, const float32 fZ){
			this->SetTranslation(CVector3D(fX, fY, fZ));
		}

		void	CMatrix::SetRotation(const float32 fAngle, const CVector3D& vAxis){
			this->Set(FromGLM(glm::rotate(glm::mat4(1.0f), fAngle, glm::make_vec3(vAxis.GetPointer()))));
		}

		void	CMatrix::SetRotation(const AxisOrientation uAxis, const float32 fAngle){
			switch(uAxis){
			case AxisOrientation::AxisX:	this->SetRotation(fAngle, Math::CVector3D(1.0f, 0.0f, 0.0f));	break;
			case AxisOrientation::AxisY:	this->SetRotation(fAngle, Math::CVector3D(0.0f, 1.0f, 0.0f));	break;
			case AxisOrientation::AxisZ:	this->SetRotation(fAngle, Math::CVector3D(0.0f, 0.0f, 1.0f));	break;
			default:
				throw Exception::CInvalidArgumentException(L"uAxis", CB::String::ToString(uAxis),
					L"Unknown axis.", CR_INFO());
			}
		}

		void	CMatrix::SetRotation(const RotationOrder uOrder, const CVector3D& vAngle){
			switch (uOrder)
			{
			case RotationOrder::XYZ:
				this->SetRotation(AxisOrientation::AxisX, vAngle.X);
				this->Set(this->Mul(GetRotation(AxisOrientation::AxisY, vAngle.Y)));
				this->Set(this->Mul(GetRotation(AxisOrientation::AxisZ, vAngle.Z)));
				break;

			case RotationOrder::XZY:
				this->SetRotation(AxisOrientation::AxisX, vAngle.X);
				this->Set(this->Mul(GetRotation(AxisOrientation::AxisZ, vAngle.Z)));
				this->Set(this->Mul(GetRotation(AxisOrientation::AxisY, vAngle.Y)));
				break;

			case RotationOrder::ZXY:
				this->SetRotation(AxisOrientation::AxisZ, vAngle.Z);
				this->Set(this->Mul(GetRotation(AxisOrientation::AxisX, vAngle.X)));
				this->Set(this->Mul(GetRotation(AxisOrientation::AxisY, vAngle.Y)));
				break;

			default:
				throw CB::Exception::CInvalidArgumentException(L"uOrder", CB::String::ToString(uOrder),
					L"Unknown axis order.", CR_INFO());
			}
		}

		void	CMatrix::Transpose(){
			CMatrix temp = *this;
			for(uint32 i = 0; i < 4; i++){
				this->Get(i) = temp.GetColumn(i);
			}
		}

		void	CMatrix::Inverse(){
			this->Set(FromGLM(glm::inverse(ToGLM(*this))));
		}

		const uint32	CMatrix::GetLength() const{
			return 4;
		}

		const uint32	CMatrix::GetSizeInBytes() const{
			return this->GetLength() * sizeof(CVector4D);
		}

		const bool		CMatrix::IsEmpty() const{
			return false;
		}

		const CVector4D*	CMatrix::GetPointer() const{
			return &this->Row[0];// this->Row.GetPointer();
		}

		CVector4D*			CMatrix::GetPointer() {
			return &this->Row[0];// this->Row.GetPointer();
		}
		
		const float32*	CMatrix::GetMatrixPointer() const{
			return this->Row[0].GetPointer();
		}

		float32*		CMatrix::GetMatrixPointer(){
			return this->Row[0].GetPointer();
		}

		const CMatrix	CMatrix::GetTransposed() const{
			CMatrix mOut;
			for(uint32 i = 0; i < 4; i++){
				mOut[i] = this->GetColumn(i);
			}
			return mOut;
		}

		const CMatrix	CMatrix::GetInverted() const{
			return FromGLM(glm::inverse(ToGLM(*this)));
		}

		const CVector3D	CMatrix::Transform(const CVector3D& vVec) const{
			CVector3D vOut;

			for(uint32 i = 0; i < 3; i++){
				vOut[i] = this->GetColumn(i).Dot(CVector4D(vVec, 1.0f));
			}

			return vOut;
		}

		const CVector3D	CMatrix::TransformNormal(const CVector3D& vNormal) const{
			CVector3D vOut;

			for(uint32 i = 0; i < 3; i++){
				vOut[i] = CVector3D(this->GetColumn(i)).Dot(vNormal);
			}

			return vOut;
		}

		const float32	CMatrix::GetDeterminant() const{
			return glm::determinant(ToGLM(*this));
		}

		const CVector4D&	CMatrix::Get(const uint32 uIndex) const{
			switch(uIndex){
			case 0:	return this->Row[0];
			case 1:	return this->Row[1];
			case 2: return this->Row[2];
			case 3:	return this->Row[3];
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			};
		}

		CVector4D&	CMatrix::Get(const uint32 uIndex){
			switch(uIndex){
			case 0:	return this->Row[0];
			case 1:	return this->Row[1];
			case 2: return this->Row[2];
			case 3:	return this->Row[3];
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			};
		}

		const CVector4D	CMatrix::GetColumn(const uint32 uIndex) const{
			if(uIndex > 3){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}

			return CVector4D(this->Row[0][uIndex], this->Row[1][uIndex], this->Row[2][uIndex], this->Row[3][uIndex]);
		}

		const float32&	CMatrix::Get(const uint32 uRow, const uint32 uColumn) const{
			return this->Get(uRow)[uColumn];
		}

		float32&	CMatrix::Get(const uint32 uRow, const uint32 uColumn){
			return this->Get(uRow)[uColumn];
		}

		const CMatrix	CMatrix::Add(const CMatrix& Matrix) const{
			CMatrix mOut;
			for(uint32 uIndex = 0; uIndex < 4; uIndex++){
				mOut[uIndex] = this->Get(uIndex) + Matrix[uIndex];
			}
			return mOut;
		}

		const CMatrix	CMatrix::Sub(const CMatrix& Matrix) const{
			CMatrix mOut;
			for(uint32 uIndex = 0; uIndex < 4; uIndex++){
				mOut[uIndex] = this->Get(uIndex) - Matrix[uIndex];
			}
			return mOut;
		}

		const CMatrix	CMatrix::Mul(const CMatrix& Matrix) const{
			return FromGLM(ToGLM(*this) * ToGLM(Matrix));
		}

		const CMatrix CMatrix::Mul(const float32 fValue) const{
			CMatrix mOut;
			for(uint32 uIndex = 0; uIndex < 4; uIndex++){
				mOut[uIndex] = this->Get(uIndex) * fValue;
			}
			return mOut;
		}

		const CMatrix CMatrix::Div(const float32 fValue) const{
			if(fValue == 0.0f){
				throw CB::Exception::CNullArgumentException(L"fValue",
					L"Division by zero.", CR_INFO());
			}

			CMatrix mOut;
			for(uint32 uIndex = 0; uIndex < 4; uIndex++){
				mOut[uIndex] = this->Get(uIndex) / fValue;
			}
			return mOut;
		}

		const CString	CMatrix::ToString() const{
			return this->ToString(false);
		}

		const CString	CMatrix::ToString(const bool bNewLine) const{
			CString strOut;
			for(uint32 uRow = 0; uRow < 4; uRow++){
				for(uint32 uColumn = 0; uColumn < 4; uColumn++){
					strOut += L"m" + CB::String::FromUInt32(uRow+1) + 
						CB::String::FromUInt32(uColumn+1) + L": " + 
						CB::String::ToString(this->Get(uRow, uColumn));
					if(uRow != 3){
						strOut += L", ";
					}
				}
				if(uRow != 3 && bNewLine){
					strOut += L"\n";
				}
			}
			return strOut;
		}

		const CMatrix& CMatrix::operator=(const CMatrix& Matrix){
			this->Set(Matrix.Row[0], Matrix.Row[1], Matrix.Row[2], Matrix.Row[3]);
			return *this;
		}

		const CMatrix	CMatrix::operator+(const CMatrix& Matrix) const{
			return this->Add(Matrix);
		}

		const CMatrix	CMatrix::operator-(const CMatrix& Matrix) const{
			return this->Sub(Matrix);
		}

		const CMatrix	CMatrix::operator*(const CMatrix& Matrix) const{
			return this->Mul(Matrix);
		}

		const CMatrix	CMatrix::operator*(const float32 fValue) const{
			return this->Mul(fValue);
		}

		const CMatrix	CMatrix::operator/(const float32 fValue) const{
			return this->Div(fValue);
		}

		const CVector3D CMatrix::operator*(const CVector3D& vVector) const{
			return this->Transform(vVector);
		}

		const CMatrix&	CMatrix::operator+=(const CMatrix& Matrix){
			*this = this->Add(Matrix);
			return *this;
		}

		const CMatrix&	CMatrix::operator-=(const CMatrix& Matrix){
			*this = this->Sub(Matrix);
			return *this;
		}

		const CMatrix&	CMatrix::operator*=(const CMatrix& Matrix){
			*this = this->Mul(Matrix);
			return *this;
		}

		const CMatrix&	CMatrix::operator*=(const float32 fValue){
			*this = this->Mul(fValue);
			return *this;
		}

		const CMatrix&	CMatrix::operator/=(const float32 fValue){
			*this = this->Div(fValue);
			return *this;
		}

		const CVector4D&	CMatrix::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		CVector4D&	CMatrix::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		const CMatrix	CMatrix::GetIdentity(){
			CMatrix mOut;
			mOut.SetIdentity();
			return mOut;
		}

		const CMatrix	CMatrix::GetTranslation(const float32 fX, const float32 fY, const float32 fZ){
			CMatrix mOut;
			mOut.SetTranslation(fX, fY, fZ);
			return mOut;
		}

		const CMatrix	CMatrix::GetTranslation(const CVector3D& vPosition){
			CMatrix mOut;
			mOut.SetTranslation(vPosition);
			return mOut;
		}

		const CMatrix CMatrix::GetRotation(const float32 fAngle, const CVector3D& vAxis){
			CMatrix mOut;
			mOut.SetRotation(fAngle, vAxis);
			return mOut;
		}

		const CMatrix CMatrix::GetRotation(const AxisOrientation uAxis, const float32 fAngle){
			CMatrix mOut;
			mOut.SetRotation(uAxis, fAngle);
			return mOut;
		}

		const CMatrix	CMatrix::GetRotation(const RotationOrder uOrder, const CVector3D& vAngle){
			CMatrix mat;
			mat.SetRotation(uOrder, vAngle);
			return mat;
		}

		const CMatrix	CMatrix::GetOrtho(const CVector2D& Size, const float32 fZNear, const float32 fZFar){
			return GetOrtho(Size.X, Size.Y, fZNear, fZFar);
		}

		const CMatrix	CMatrix::GetOrtho(const float32 fWidth, const float32 fHeight, const float32 fZNear, const float32 fZFar){
			const float32 halfW = fWidth / 2.0f;
			const float32 halfH = fHeight / 2.0f;
			return FromGLM(glm::ortho(-halfW, halfW, -halfH, halfH, fZNear, fZFar));
		}

		const CMatrix	CMatrix::GetPerspective(const float32 fAspect, const float32 fEyeAngle, const float32 fZNear, const float32 fZFar){
			return FromGLM(glm::perspective(fEyeAngle, fAspect, fZNear, fZFar));
		}
	}

	//	Function implementations

	namespace String{
		const CString	ToString(const Math::AxisOrientation uAxis){
			switch (uAxis)
			{
			case Math::AxisOrientation::AxisX:	return L"AxisX";
			case Math::AxisOrientation::AxisY:	return L"AxisY";
			case Math::AxisOrientation::AxisZ:	return L"AxisZ";
			default:
				throw Exception::CInvalidArgumentException(L"uAxis", FromUInt32((uint32)uAxis),
					L"Unknown axis type. cannot convert to string.", CR_INFO());
			}
		}

		const CString	ToString(const Math::RotationOrder uOrder){
			switch (uOrder)
			{
			case Math::RotationOrder::XYZ:	return L"XYZ";
			case Math::RotationOrder::XZY:	return L"XZY";
			case Math::RotationOrder::ZXY:	return L"ZXY";
			default:
				throw Exception::CInvalidArgumentException(L"uOrder", FromUInt32((uint32)uOrder),
					L"Unknown rotation order error, cannot convert to string.", CR_INFO());
			}
		}
	}
}