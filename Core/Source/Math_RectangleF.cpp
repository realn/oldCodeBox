#include "stdafx.h"
#include "../Include/Math_RectangleF.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CRectangleF32::CRectangleF32(){
		}

		CRectangleF32::CRectangleF32(const CRectangleF32& Rect) :
			Position(Rect.Position),
			Size(Rect.Size)
		{}

		CRectangleF32::CRectangleF32(const CVector2D& Position, const CVector2D& Size) :
			Position(Position),
			Size(Size)
		{}

		CRectangleF32::CRectangleF32(const float32 X, const float32 Y, const CVector2D& Size) :
			Position(X, Y),
			Size(Size)
		{}

		CRectangleF32::CRectangleF32(const CVector2D& Position, const float32 Width, const float32 Height) :
			Position(Position),
			Size(Width, Height)
		{}

		CRectangleF32::CRectangleF32(const float32 X, const float32 Y, const float32 Width, const float32 Height) :
			Position(X, Y),
			Size(Width, Height)
		{}

		void	CRectangleF32::SetZero(){
			this->Position.SetZero();
			this->Size.SetZero();
		}

		void	CRectangleF32::Set(const CRectangleF32& Rectangle){
			this->Position = Rectangle.Position;
			this->Size = Rectangle.Size;
		}

		void	CRectangleF32::Set(const float32 X, const float32 Y, const float32 Width, const float32 Height){
			this->Position.Set(X, Y);
			this->Size.Set(Width, Height);
		}

		const bool	CRectangleF32::IsZero() const{
			return this->Position.IsZero() && this->Size.IsZero();
		}

		const bool	CRectangleF32::IsPartialZero() const{
			return this->Position.IsPartialZero() || this->Size.IsPartialZero();
		}

		const bool	CRectangleF32::IsEqual(const CRectangleF32& Rectangle) const{
			return this->Position.IsEqual(Rectangle.Position) && this->Size.IsEqual(Rectangle.Size);
		}

		const float32	CRectangleF32::GetXLower() const{
			return this->Position.X;
		}

		const float32	CRectangleF32::GetXHigher() const{
			return this->Position.X + this->Size.X;
		}

		const float32	CRectangleF32::GetYLower() const{
			return this->Position.Y;
		}

		const float32	CRectangleF32::GetYHigher() const{
			return this->Position.Y + this->Size.Y;
		}

		const bool	CRectangleF32::Contains(const CVector2D& Point) const{
			return Point.X >= this->GetXLower() &&
				Point.X <= this->GetXHigher() &&
				Point.Y >= this->GetYLower() &&
				Point.Y <= this->GetYHigher();
		}

		const bool	CRectangleF32::Contains(const CRectangleF32& Rectangle) const{
			return Rectangle.GetXLower() >= this->GetXLower() &&
				Rectangle.GetXHigher() <= this->GetXHigher() &&
				Rectangle.GetYLower() >= this->GetYLower() &&
				Rectangle.GetYHigher() <= this->GetYHigher();
		}

		const bool	CRectangleF32::Intersects(const CRectangleF32& Rectangle) const{
			if((Rectangle.GetXLower() >= this->GetXLower() && Rectangle.GetXLower() <= this->GetXHigher()) || 
				(Rectangle.GetXHigher() >= this->GetXLower() && Rectangle.GetXHigher() <= this->GetXHigher())){

				if((Rectangle.GetYLower() >= this->GetYLower() && Rectangle.GetYLower() <= this->GetYHigher()) ||
					(Rectangle.GetYHigher() >= this->GetYLower() && Rectangle.GetYHigher() <= this->GetYHigher())){
					return true;
				}
			}
			return false;
		}

		const CB::CString	CRectangleF32::ToString() const{
			return L"Position: (" + this->Position.ToString() + L"), Size: (" + this->Size.ToString() + L")";
		}

		const CRectangleF32&	CRectangleF32::operator=(const CRectangleF32& Rectangle){
			this->Position	= Rectangle.Position;
			this->Size		= Rectangle.Size;
			return *this;
		}

		const bool	CRectangleF32::operator==(const CRectangleF32& Rectangle) const{
			return this->IsEqual(Rectangle);
		}

		const bool	CRectangleF32::operator!=(const CRectangleF32& Rectangle) const{
			return !this->IsEqual(Rectangle);
		}

		const float32	CRectangleF32::operator[](const uint32 uIndex) const{
			switch (uIndex){
			case 0:	return this->GetXLower();
			case 1:	return this->GetYLower();
			case 2:	return this->GetXHigher();
			case 3:	return this->GetYHigher();
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}
	}
}