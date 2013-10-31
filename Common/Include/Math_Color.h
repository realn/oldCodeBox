#pragma once

#include "Math_Vector.h"

namespace CB{
	namespace Math{
		class COMMON_API CColor{
		public:
			float	Red;
			float	Green;
			float	Blue;
			float	Alpha;

			CColor();
			CColor(const CColor& Color);
			CColor(const CVector3D& Vector);
			CColor(const CVector3D& Vector, const float fAlpha);
			CColor(const CVector4D& Vector);
			CColor(const CPoint3D& Point); // clamped to 0-255
			CColor(const CPoint3D& Point, const float fAlpha);
			explicit CColor(const float fColor);
			explicit CColor(const float fColor, const float fAlpha);
			CColor(const float fRed, const float fGreen, const float fBlue); // clamped to 0-1
			CColor(const float fRed, const float fGreen, const float fBlue, const float fAlpha);

			void	Set(const CColor& Color);
			void	Set(const float fColor);
			void	Set(const float fColor, const float fAlpha);
			void	Set(const float fRed, const float fGreen, const float fBlue);
			void	Set(const float fRed, const float fGreen, const float fBlue, const float fAlpha);
			void	Set(const unsigned char uColor);
			void	Set(const unsigned char uColor, const unsigned char uAlpha);
			void	Set(const unsigned char uRed, const unsigned char uGreen, const unsigned char uBlue);
			void	Set(const unsigned char uRed, const unsigned char uGreen, const unsigned char uBlue, const unsigned char uAlpha);

			const unsigned char	GetRedByte() const;
			const unsigned char GetGreenByte() const;
			const unsigned char GetBlueByte() const;
			const unsigned char GetAlphaByte() const;

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

			const unsigned ToRGBA() const;
			const unsigned ToARGB() const;
			const unsigned ToBGRA() const;
			const unsigned ToABGR() const;

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

			const float&	operator[](const unsigned uIndex) const;
			float&			operator[](const unsigned uIndex);
		};

		class CColorHSV{
		public:
			float	H;
			float	S;
			float	V;
		};
	}
}