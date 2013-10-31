#pragma once

#include "Math_Vector.h"

namespace CB{
	namespace Math{
		enum class AxisOrientation{
			AxisX,
			AxisY,
			AxisZ
		};
		enum class RotationOrder{
			XYZ,
			XZY,
			ZXY
		};

		class COMMON_API CMatrix{
		public:
			CVector4D	Row[4];

			CMatrix();
			CMatrix(const float* pMatrix);
			CMatrix(const CMatrix& Matrix);
			CMatrix(const CVector4D& vRow1, const CVector4D& vRow2,const CVector4D& vRow3, const CVector4D& vRow4);

			void	SetZero();
			void	SetIdentity();
			void	Set(const CMatrix& Matrix);
			void	Set(const float* pMatrix);
			void	Set(const CVector4D& vRow1, const CVector4D& vRow2,const CVector4D& vRow3, const CVector4D& vRow4);

			void	SetTranslation(const float fX, const float fY, const float fZ);
			void	SetTranslation(const CVector3D& vPos);
			void	SetRotation(const float fAngle, const CVector3D& vAxis);
			void	SetRotation(const AxisOrientation uAxis, const float fAngle);
			void	SetRotation(const RotationOrder uOrder, const CVector3D& vAngle);

			void	Transpose();
			void	Inverse();
			
			const CMatrix	GetTransposed() const;
			const CMatrix	GetInverted() const;
			const CVector3D	Transform(const CVector3D& Vector) const;
			const CVector3D	TransformNormal(const CVector3D& vNormal) const;
			const float		GetDeterminant() const;

			const CVector4D&	GetRow(const unsigned uIndex) const;
			CVector4D&			GetRow(const unsigned uIndex);
			const CVector4D		GetColumn(const unsigned uIndex) const;
			
			const float&	Get(const unsigned uRow, const unsigned uColumn) const;
			float&			Get(const unsigned uRow, const unsigned uColumn);

			const CMatrix	Add(const CMatrix& Matrix) const;
			const CMatrix	Sub(const CMatrix& Matrix) const;
			const CMatrix	Mul(const CMatrix& Matrix) const;

			const CMatrix	Mul(const float fValue) const;
			const CMatrix	Div(const float fValue) const;

			const CString	ToString() const; // NewLine = false
			const CString	ToString(const bool bNewLine) const;
			const float*	ToFloat() const;

			const CMatrix&	operator=(const CMatrix& Matrix);

			const CMatrix	operator+(const CMatrix& Matrix) const;
			const CMatrix	operator-(const CMatrix& Matrix) const;
			const CMatrix	operator*(const CMatrix& Matrix) const;
			const CMatrix	operator*(const float fValue) const;
			const CMatrix	operator/(const float fValue) const;
			const CVector3D	operator*(const CVector3D& Vector) const;

			const CMatrix&	operator+=(const CMatrix& Matrix);
			const CMatrix&	operator-=(const CMatrix& Matrix);
			const CMatrix&	operator*=(const CMatrix& Matrix);
			const CMatrix&	operator*=(const float fValue);
			const CMatrix&	operator/=(const float fValue);

			const CVector4D&	operator[](const unsigned uIndex) const;
			CVector4D&			operator[](const unsigned uIndex);

			static const CMatrix	GetIdentity();
			static const CMatrix	GetTranslation(const float fX, const float fY, const float fZ);
			static const CMatrix	GetTranslation(const CVector3D& vPos);
			static const CMatrix	GetRotation(const float fAngle, const CVector3D& vAxis);
			static const CMatrix	GetRotation(const AxisOrientation uAxis, const float fAngle);
			static const CMatrix	GetRotation(const RotationOrder uOrder, const CVector3D& vAngle);

			static const CMatrix	GetOrtho(const CVector2D& Size, const float fZNear, const float fZFar);
			static const CMatrix	GetOrtho(const float fWidth, const float fHeight, const float fZNear, const float fZFar);
			static const CMatrix	GetPerspective(const float fAspect, const float fEyeAngle, const float fZNear, const float fZFar);
		};
	}

	namespace String{
		extern COMMON_API const CB::CString	ToString(const CB::Math::AxisOrientation uAxis);
		extern COMMON_API const CB::CString	ToString(const CB::Math::RotationOrder uOrder);
	}
}