#include "../Include/Math_Color.h"
#include "../Include/Math.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CColor::CColor() : Red(1.0f), Green(1.0f), Blue(1.0f), Alpha(1.0f){
		}

		CColor::CColor(const CColor& Color) : Red(Color.Red), Green(Color.Green), Blue(Color.Blue), Alpha(Color.Alpha){
		}

		CColor::CColor(const CVector3D& Vector) : Red(Vector.X), Green(Vector.Y), Blue(Vector.Z), Alpha(1.0f){
		}

		CColor::CColor(const CVector3D& Vector, const float fAlpha) : Red(Vector.X), Green(Vector.Y), Blue(Vector.Z), Alpha(fAlpha){
		}

		CColor::CColor(const CVector4D& Vector) : Red(Vector.X), Green(Vector.Y), Blue(Vector.Z), Alpha(Vector.W){
		}

		CColor::CColor(const CPoint3D& Point) :
			Red(Math::Convert0255to01(Point.X)),
			Green(Math::Convert0255to01(Point.Y)),
			Blue(Math::Convert0255to01(Point.Z)),
			Alpha(1.0f)
		{
		}

		CColor::CColor(const CPoint3D& Point, const float fAlpha) :
			Red(Math::Convert0255to01(Point.X)),
			Green(Math::Convert0255to01(Point.Y)),
			Blue(Math::Convert0255to01(Point.Z)),
			Alpha(fAlpha)
		{
		}

		CColor::CColor(const float fColor) : Red(fColor), Green(fColor), Blue(fColor), Alpha(1.0f){
		}

		CColor::CColor(const float fColor, const float fAlpha) : Red(fColor), Green(fColor), Blue(fColor), Alpha(fAlpha){
		}

		CColor::CColor(const float fRed, const float fGreen, const float fBlue) : Red(fRed), Green(fGreen), Blue(fBlue), Alpha(1.0f){
		}

		CColor::CColor(const float fRed, const float fGreen, const float fBlue, const float fAlpha) : Red(fRed), Blue(fBlue), Green(fGreen), Alpha(fAlpha){
		}

		void	CColor::Set(const CColor& Color){
			this->Red	= Color.Red;
			this->Green	= Color.Green;
			this->Blue	= Color.Blue;
			this->Alpha = Color.Alpha;
		}

		void	CColor::Set(const float fColor){
			const float fCol = Clamp01(fColor);
			this->Red	= fCol;
			this->Green = fCol;
			this->Blue	= fCol;
			this->Alpha = 1.0f;
		}

		void	CColor::Set(const float fColor, const float fAlpha){
			const float fCol = Clamp01(fColor);
			this->Red	= fCol;
			this->Green = fCol;
			this->Blue	= fCol;
			this->Alpha = Clamp01(fAlpha);
		}

		void	CColor::Set(const float fRed, const float fGreen, const float fBlue){
			this->Red	= Clamp01(fRed);
			this->Green = Clamp01(fGreen);
			this->Blue	= Clamp01(fBlue);
			this->Alpha = 1.0f;
		}

		void	CColor::Set(const float fRed, const float fGreen, const float fBlue, const float fAlpha){
			this->Red	= Clamp01(fRed);
			this->Green = Clamp01(fGreen);
			this->Blue	= Clamp01(fBlue);
			this->Alpha = Clamp01(fAlpha);
		}

		void	CColor::Set(const unsigned char uColor){
			const float fColor = Convert0255to01(uColor);
			this->Red	= fColor;
			this->Green = fColor;
			this->Blue	= fColor;
			this->Alpha = 1.0f;
		}

		void	CColor::Set(const unsigned char uColor, const unsigned char uAlpha){
			this->Set(uColor);
			this->Alpha = Convert0255to01(uAlpha);
		}

		void	CColor::Set(const unsigned char uRed, const unsigned char uGreen, const unsigned char uBlue){
			this->Red	= Convert0255to01(uRed);
			this->Green	= Convert0255to01(uGreen);
			this->Blue	= Convert0255to01(uBlue);
			this->Alpha = 1.0f;
		}

		void	CColor::Set(const unsigned char uRed, const unsigned char uGreen, const unsigned char uBlue, const unsigned char uAlpha){
			this->Set(uRed, uGreen, uBlue);
			this->Alpha = Convert0255to01(uAlpha);
		}

		const unsigned char	CColor::GetRedByte() const{
			return Convert01to0255(this->Red);
		}

		const unsigned char	CColor::GetGreenByte() const{
			return Convert01to0255(this->Green);
		}

		const unsigned char	CColor::GetBlueByte() const{
			return Convert01to0255(this->Blue);
		}

		const unsigned char CColor::GetAlphaByte() const{
			return Convert01to0255(this->Alpha);
		}

		const bool	CColor::IsBlack() const{
			return this->Red <= 0.0f && this->Green <= 0.0f && this->Blue <= 0.0f;
		}

		const bool	CColor::IsNearBlack() const{
			return IsNearZero(this->Red) && IsNearZero(this->Green) && IsNearZero(this->Blue);
		}

		const bool	CColor::IsWhite() const{
			return this->Red >= 1.0f && this->Green >= 1.0f && this->Blue >= 1.0f;
		}

		const bool	CColor::IsNearWhite() const{
			return Math::IsNearEqual(this->Red, 1.0f) && Math::IsNearEqual(this->Green, 1.0f) && Math::IsNearEqual(this->Blue, 1.0f);
		}

		const bool	CColor::IsOpaque() const{
			return this->Alpha >= 1.0f;
		}

		const bool	CColor::IsNearOpaque() const{
			return Math::IsNearEqual(this->Alpha, 1.0f);
		}

		const bool	CColor::IsTransparent() const{
			return this->Alpha <= 0.0f;
		}

		const bool	CColor::IsNearTransparent() const{
			return IsNearZero(this->Alpha);
		}

		void	CColor::Clamp(){
			this->Red	= Clamp01(this->Red);
			this->Green	= Clamp01(this->Green);
			this->Blue	= Clamp01(this->Blue);
			this->Alpha = Clamp01(this->Alpha);
		}

		const bool	CColor::IsEqual(const CColor& Color) const{
			return this->Red == Color.Red && this->Green == Color.Green && this->Blue == Color.Blue && this->Alpha == Color.Alpha;
		}

		const bool	CColor::IsNearEqual(const CColor& Color) const{
			return Math::IsNearEqual(this->Red, Color.Red) && 
				Math::IsNearEqual(this->Green, Color.Green) &&
				Math::IsNearEqual(this->Blue, Color.Blue) &&
				Math::IsNearEqual(this->Alpha, Color.Alpha);
		}

		const unsigned	CColor::ToABGR() const{
			unsigned char uRed		= this->GetRedByte();
			unsigned char uGreen	= this->GetGreenByte();
			unsigned char uBlue		= this->GetBlueByte();
			unsigned char uAlpha	= this->GetAlphaByte();

			unsigned uReturn = 0;

			uReturn = uAlpha;
			uReturn = uReturn << 8 | uBlue;
			uReturn = uReturn << 8 | uGreen;
			uReturn = uReturn << 8 | uRed;

			return uReturn;
		}

		const unsigned	CColor::ToARGB() const{
			unsigned char uRed		= this->GetRedByte();
			unsigned char uGreen	= this->GetGreenByte();
			unsigned char uBlue		= this->GetBlueByte();
			unsigned char uAlpha	= this->GetAlphaByte();

			unsigned uReturn = 0;

			uReturn = uAlpha;
			uReturn = uReturn << 8 | uRed;
			uReturn = uReturn << 8 | uGreen;
			uReturn = uReturn << 8 | uBlue;
	
			return uReturn;
		}

		const unsigned	CColor::ToBGRA() const{
			unsigned char uRed		= this->GetRedByte();
			unsigned char uGreen	= this->GetGreenByte();
			unsigned char uBlue		= this->GetBlueByte();
			unsigned char uAlpha	= this->GetAlphaByte();

			unsigned uReturn = 0;

			uReturn = uBlue;
			uReturn = uReturn << 8 | uGreen;
			uReturn = uReturn << 8 | uRed;
			uReturn = uReturn << 8 | uAlpha;

			return uReturn;
		}

		const unsigned	CColor::ToRGBA() const{
			unsigned char uRed		= this->GetRedByte();
			unsigned char uGreen	= this->GetGreenByte();
			unsigned char uBlue		= this->GetBlueByte();
			unsigned char uAlpha	= this->GetAlphaByte();

			unsigned uReturn = 0;

			uReturn = uRed;
			uReturn = uReturn << 8 | uGreen;
			uReturn = uReturn << 8 | uBlue;
			uReturn = uReturn << 8 | uAlpha;

			return uReturn;
		}

		const CColor	CColor::Add(const CColor& Color) const{
			return CColor(this->Red + Color.Red, this->Green + Color.Green, this->Blue + Color.Blue, this->Alpha + Color.Alpha);
		}

		const CColor	CColor::Sub(const CColor& Color) const{
			return CColor(this->Red - Color.Red, this->Green - Color.Green, this->Blue - Color.Blue, this->Alpha - Color.Alpha);
		}

		const CColor	CColor::Mul(const CColor& Color) const{
			return CColor(this->Red * Color.Red, this->Green * Color.Green, this->Blue * Color.Blue, this->Alpha * Color.Alpha);
		}

		const CColor	CColor::Div(const CColor& Color) const{
			if(Color.Red == 0.0f || Color.Green == 0.0f || Color.Blue == 0.0f || Color.Alpha == 0.0f){
				throw CB::Exception::CInvalidArgumentException(L"Color", Color.ToString(),
					L"Division by zero", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return CColor(this->Red / Color.Red, this->Green / Color.Green, this->Blue / Color.Blue, this->Alpha / Color.Alpha);
		}

		const CColor	CColor::AddColor(const CColor& Color) const{
			return CColor(this->Red + Color.Red, this->Green + Color.Green, this->Blue + Color.Blue);
		}

		const CColor	CColor::SubColor(const CColor& Color) const{
			return CColor(this->Red - Color.Red, this->Green - Color.Green, this->Blue - Color.Blue);
		}

		const CColor	CColor::MulColor(const CColor& Color) const{
			return CColor(this->Red * Color.Red, this->Green * Color.Green, this->Blue * Color.Blue);
		}

		const CColor	CColor::DivColor(const CColor& Color) const{
			if(Color.Red == 0.0f || Color.Green == 0.0f || Color.Blue == 0.0f){
				throw CB::Exception::CInvalidArgumentException(L"Color", Color.ToString(),
					L"Division by zero", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return CColor(this->Red / Color.Red, this->Green / Color.Green, this->Blue / Color.Blue);
		}

		const CB::CString	CColor::ToString() const{
			return L"Red: " + String::FromFloat(this->Red) + 
				L", Green: " + String::FromFloat(this->Green) + 
				L", Blue: " + String::FromFloat(this->Blue) + 
				L", Alpha: " + String::FromFloat(this->Alpha);
		}

		const CVector3D CColor::ToVector() const{
			return CVector3D(this->Red, this->Green, this->Blue);
		}

		const CVector4D	CColor::ToVector4D() const{
			return CVector4D(this->Red, this->Green, this->Blue, this->Alpha);
		}

		const CPoint3D	CColor::ToPoint() const{
			return CPoint3D(this->GetRedByte(), this->GetGreenByte(), this->GetBlueByte());
		}

		const CColor	CColor::ToColor() const{
			return CColor(this->Red, this->Green, this->Blue, 1.0f);
		}

		const CColor&	CColor::operator=(const CColor& Color){
			this->Set(Color);
			return *this;
		}

		const CColor	CColor::operator+(const CColor& Color) const{
			return this->Add(Color);
		}

		const CColor	CColor::operator-(const CColor& Color) const{
			return this->Sub(Color);
		}

		const CColor	CColor::operator*(const CColor& Color) const{
			return this->Mul(Color);
		}

		const CColor	CColor::operator/(const CColor& Color) const{
			return this->Div(Color);
		}

		const bool	CColor::operator==(const CColor& Color) const{
			return this->IsEqual(Color);
		}

		const bool	CColor::operator!=(const CColor& Color) const{
			return !this->IsEqual(Color);
		}

		const float&	CColor::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->Red;
			case 1:	return this->Green;
			case 2:	return this->Blue;
			case 3:	return this->Alpha;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		float&	CColor::operator[](const unsigned uIndex){
			switch (uIndex)
			{
			case 0:	return this->Red;
			case 1:	return this->Green;
			case 2:	return this->Blue;
			case 3:	return this->Alpha;
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}