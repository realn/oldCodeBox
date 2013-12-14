#pragma once

#include "Math_Vector.h"

namespace CB{
	namespace Math{
		class COMMON_API CColor{
		public:
			float32	Red;
			float32	Green;
			float32	Blue;
			float32	Alpha;

			CColor();
			CColor(const CColor& Color);
			CColor(const CVector3D& Vector);
			CColor(const CVector3D& Vector, const float32 fAlpha);
			CColor(const CVector4D& Vector);
			CColor(const CPoint3D& Point); // clamped to 0-255
			CColor(const CPoint3D& Point, const float32 fAlpha);
			explicit CColor(const float32 fColor);
			explicit CColor(const float32 fColor, const float32 fAlpha);
			CColor(const float32 fRed, const float32 fGreen, const float32 fBlue); // clamped to 0-1
			CColor(const float32 fRed, const float32 fGreen, const float32 fBlue, const float32 fAlpha);

			void	Set(const CColor& Color);
			void	Set(const float32 fColor);
			void	Set(const float32 fColor, const float32 fAlpha);
			void	Set(const float32 fRed, const float32 fGreen, const float32 fBlue);
			void	Set(const float32 fRed, const float32 fGreen, const float32 fBlue, const float32 fAlpha);
			void	Set(const byte uColor);
			void	Set(const byte uColor, const byte uAlpha);
			void	Set(const byte uRed, const byte uGreen, const byte uBlue);
			void	Set(const byte uRed, const byte uGreen, const byte uBlue, const byte uAlpha);

			const byte	GetRedByte() const;
			const byte GetGreenByte() const;
			const byte GetBlueByte() const;
			const byte GetAlphaByte() const;

			const bool	IsBlack() const;
			const bool	IsNearBlack() const;
			const bool	IsWhite() const;
			const bool	IsNearWhite() const;

			const bool	IsOpaque() const;
			const bool	IsNearOpaque() const;
			const bool	IsTransparent() const;
			const bool	IsNearTransparent() const;

			void		Clamp();

			const bool IsEqual(const CColor& Color) const;
			const bool IsNearEqual(const CColor& Color) const;

			const uint32 ToRGBA() const;
			const uint32 ToARGB() const;
			const uint32 ToBGRA() const;
			const uint32 ToABGR() const;

			const CColor	Add(const CColor& Color) const;
			const CColor	Sub(const CColor& Color) const;
			const CColor	Mul(const CColor& Color) const;
			const CColor	Div(const CColor& Color) const;

			const CColor	AddColor(const CColor& Color) const;
			const CColor	SubColor(const CColor& Color) const;
			const CColor	MulColor(const CColor& Color) const;
			const CColor	DivColor(const CColor& Color) const;

			const CString		ToString() const;
			const CVector3D		ToVector() const;
			const CVector4D		ToVector4D() const;
			const CPoint3D		ToPoint() const;
			const CColor		ToColor() const;

			const CColor&	operator=(const CColor& Color);

			const CColor	operator+(const CColor& Color) const;
			const CColor	operator-(const CColor& Color) const;
			const CColor	operator*(const CColor& Color) const;
			const CColor	operator/(const CColor& Color) const;

			const bool		operator==(const CColor& Color) const;
			const bool		operator!=(const CColor& Color) const;

			const float32&	operator[](const uint32 uIndex) const;
			float32&			operator[](const uint32 uIndex);
		};

		class CColorHSV{
		public:
			float32	H;
			float32	S;
			float32	V;
		};
	}
}