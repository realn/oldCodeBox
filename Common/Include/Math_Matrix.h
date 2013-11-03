#pragma once

#include "Math_Vector.h"
#include "Collection_Array.h"

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

		template class COMMON_API Collection::CArray<CVector4D, 4>;

		class COMMON_API CMatrix :
			public Collection::ICountable<CVector4D>,
			public Collection::IPacked<CVector4D>
		{
		public:
			Collection::CArray<CVector4D, 4>	Row;

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

			const uint32	GetLength() const override;
			const uint32	GetSizeInBytes() const override;
			const bool		IsEmpty() const override;

			const CVector4D*	GetPointer() const override;
			CVector4D*			GetPointer() override;

			const float32*	GetMatrixPointer() const;
			float32*		GetMatrixPointer();
			
			const CMatrix	GetTransposed() const;
			const CMatrix	GetInverted() const;
			const CVector3D	Transform(const CVector3D& Vector) const;
			const CVector3D	TransformNormal(const CVector3D& vNormal) const;
			const float32		GetDeterminant() const;

			const CVector4D&	Get(const uint32 uIndex) const override;
			CVector4D&			Get(const uint32 uIndex) override;
			const CVector4D		GetColumn(const uint32 uIndex) const;
			
			const float32&	Get(const uint32 uRow, const uint32 uColumn) const;
			float32&			Get(const uint32 uRow, const uint32 uColumn);

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

			static const CMatrix	GetIdentity();
			static const CMatrix	GetTranslation(const float32 fX, const float32 fY, const float32 fZ);
			static const CMatrix	GetTranslation(const CVector3D& vPos);
			static const CMatrix	GetRotation(const float32 fAngle, const CVector3D& vAxis);
			static const CMatrix	GetRotation(const AxisOrientation uAxis, const float32 fAngle);
			static const CMatrix	GetRotation(const RotationOrder uOrder, const CVector3D& vAngle);

			static const CMatrix	GetOrtho(const CVector2D& Size, const float32 fZNear, const float32 fZFar);
			static const CMatrix	GetOrtho(const float32 fWidth, const float32 fHeight, const float32 fZNear, const float32 fZFar);
			static const CMatrix	GetPerspective(const float32 fAspect, const float32 fEyeAngle, const float32 fZNear, const float32 fZFar);
		};
	}

	namespace String{
		extern COMMON_API const CB::CString	ToString(const CB::Math::AxisOrientation uAxis);
		extern COMMON_API const CB::CString	ToString(const CB::Math::RotationOrder uOrder);
	}
}