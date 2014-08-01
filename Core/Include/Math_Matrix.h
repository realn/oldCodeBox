#pragma once

#include "Math_Vector4D.h"
#include "Collection_Array.h"

namespace CB{
	class CString;

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
			CMatrix(const float32* pMatrix);
			CMatrix(const CMatrix& Matrix);
			CMatrix(const CVector4D& vRow1, const CVector4D& vRow2,const CVector4D& vRow3, const CVector4D& vRow4);

			void	SetZero();
			void	SetIdentity();
			void	Set(const CMatrix& Matrix);
			void	Set(const float32* pMatrix);
			void	Set(const CVector4D& vRow1, const CVector4D& vRow2,const CVector4D& vRow3, const CVector4D& vRow4);

			void	SetTranslation(const float32 fX, const float32 fY, const float32 fZ);
			void	SetTranslation(const CVector3D& vPos);
			void	SetRotation(const float32 fAngle, const CVector3D& vAxis);
			void	SetRotation(const AxisOrientation uAxis, const float32 fAngle);
			void	SetRotation(const RotationOrder uOrder, const CVector3D& vAngle);

			void	Transpose();
			void	Inverse();

			const uint32	GetLength() const;
			const uint32	GetSizeInBytes() const;
			const bool		IsEmpty() const;

			const CVector4D*	GetPointer() const;
			CVector4D*			GetPointer();

			const float32*		GetMatrixPointer() const;
			float32*			GetMatrixPointer();
			
			const CMatrix		GetTransposed() const;
			const CMatrix		GetInverted() const;
			const CVector3D		Transform(const CVector3D& Vector) const;
			const CVector3D		TransformNormal(const CVector3D& vNormal) const;
			const float32		GetDeterminant() const;

			const CVector4D&	Get(const uint32 uIndex) const;
			CVector4D&			Get(const uint32 uIndex);
			const CVector4D		GetColumn(const uint32 uIndex) const;
			
			const float32&	Get(const uint32 uRow, const uint32 uColumn) const;
			float32&		Get(const uint32 uRow, const uint32 uColumn);

			const CMatrix	Add(const CMatrix& Matrix) const;
			const CMatrix	Sub(const CMatrix& Matrix) const;
			const CMatrix	Mul(const CMatrix& Matrix) const;

			const CMatrix	Mul(const float32 fValue) const;
			const CMatrix	Div(const float32 fValue) const;

			const CString	ToString() const; // NewLine = false
			const CString	ToString(const bool bNewLine) const;

			const CMatrix&	operator=(const CMatrix& Matrix);

			const CMatrix	operator+(const CMatrix& Matrix) const;
			const CMatrix	operator-(const CMatrix& Matrix) const;
			const CMatrix	operator*(const CMatrix& Matrix) const;
			const CMatrix	operator*(const float32 fValue) const;
			const CMatrix	operator/(const float32 fValue) const;
			const CVector3D	operator*(const CVector3D& Vector) const;

			const CMatrix&	operator+=(const CMatrix& Matrix);
			const CMatrix&	operator-=(const CMatrix& Matrix);
			const CMatrix&	operator*=(const CMatrix& Matrix);
			const CMatrix&	operator*=(const float32 fValue);
			const CMatrix&	operator/=(const float32 fValue);

			const CVector4D&	operator[](const uint32 uIndex) const;
			CVector4D&			operator[](const uint32 uIndex);

			operator const Collection::CArray<CVector4D, 4>() const;

			static const CMatrix	GetIdentity();
			static const CMatrix	GetTranslation(const float32 fX, const float32 fY, const float32 fZ);
			static const CMatrix	GetTranslation(const CVector3D& vPos);
			static const CMatrix	GetRotation(const float32 fAngle, const CVector3D& vAxis);
			static const CMatrix	GetRotation(const AxisOrientation uAxis, const float32 fAngle);
			static const CMatrix	GetRotation(const RotationOrder uOrder, const CVector3D& vAngle);

			static const CMatrix	GetOrtho(const CVector2D& Size, const float32 fZNear, const float32 fZFar);
			static const CMatrix	GetOrtho(const float32 fWidth, const float32 fHeight, const float32 fZNear, const float32 fZFar);
			static const CMatrix	GetOrtho(const float32 fLeft, const float32 fRight, const float32 fBottom, const float32 fTop, const float32 fZNear, const float32 fZFar);
			static const CMatrix	GetPerspective(const float32 fAspect, const float32 fFOV, const float32 fZNear, const float32 fZFar);
			static const CMatrix	GetPerspective(const float32 fAspect, const float32 fFOV, const float32 fZNear);
			static const CMatrix	GetFrustum(const float32 fLeft, const float32 fRight, const float32 fBottom, const float32 fTop, const float32 fZNear, const float32 fZFar);
		};
	}

	namespace String{
		extern COMMON_API const CB::CString	ToString(const CB::Math::AxisOrientation uAxis);
		extern COMMON_API const CB::CString	ToString(const CB::Math::RotationOrder uOrder);
	}
}