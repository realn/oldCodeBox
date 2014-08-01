#include "stdafx.h"
#include "../Include/Math_Rectangle.h"
#include "../Include/Exception.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CRectangle::CRectangle() : 
			Position(), 
			Size()
		{}

		CRectangle::CRectangle(const CRectangle& Rectangle) : 
			Position(Rectangle.Position), 
			Size(Rectangle.Size)
		{}

		CRectangle::CRectangle(const CPoint2D& Position, const CSize2D& Size) : 
			Position(Position), 
			Size(Size)
		{}

		CRectangle::CRectangle(const int iX, const int iY, const CSize2D& Size) : 
			Position(iX, iY), 
			Size(Size)
		{}

		CRectangle::CRectangle(const CPoint2D& Position, const uint32 uWidth, const uint32 uHeight) : 
			Position(Position), 
			Size(uWidth, uHeight)
		{}

		CRectangle::CRectangle(const int32 iX, const int32 iY, const uint32 uWidth, const uint32 uHeight) : 
			Position(iX, iY), 
			Size(uWidth, uHeight)
		{}

		void	CRectangle::SetZero(){
			this->Position.SetZero();
			this->Size.SetZero();
		}

		void	CRectangle::Set(const CRectangle& Rect){
			this->Position = Rect.Position;
			this->Size = Rect.Size;
		}

		void	CRectangle::Set(const int32 iX, const int32 iY, const uint32 uWidth, const uint32 uHeight){
			this->Position.Set(iX, iY);
			this->Size.Set(uWidth, uHeight);
		}

		const bool	CRectangle::IsZero() const{
			return this->Position.IsZero() && this->Size.IsZero();
		}

		const bool	CRectangle::IsPartialZero() const{
			return this->Position.IsPartialZero() && this->Size.IsPartialZero();
		}

		const bool	CRectangle::IsEqual(const CRectangle& Rectangle) const{
			return this->Position.IsEqual(Rectangle.Position) && this->Size.IsEqual(Rectangle.Size);
		}

		const int32	CRectangle::GetXLower() const{
			return this->Position.X;
		}

		const int32	CRectangle::GetXHigher() const{
			return this->Position.X + (int32)this->Size.Width;
		}

		const int32	CRectangle::GetYLower() const{
			return this->Position.Y;
		}

		const int32 CRectangle::GetYHigher() const{
			return this->Position.Y + (int32)this->Size.Height;
		}

		const bool	CRectangle::Contains(const CPoint2D& Point) const{
			return Point.X >= this->GetXLower() && 
				Point.X <= this->GetXHigher() && 
				Point.Y >= this->GetYLower() && 
				Point.Y <= this->GetYHigher();
		}

		const bool	CRectangle::Contains(const CRectangle& Rectangle) const{
			return Rectangle.GetXLower() >= this->GetXLower() &&
				Rectangle.GetXHigher() <= this->GetXHigher() &&
				Rectangle.GetYLower() >= this->GetYLower() &&
				Rectangle.GetYHigher() <= this->GetYHigher();
		}

		const bool	CRectangle::Intersects(const CRectangle& Rectangle) const{
			if((Rectangle.GetXLower() >= this->GetXLower() && Rectangle.GetXLower() <= this->GetXHigher()) || 
				(Rectangle.GetXHigher() >= this->GetXLower() && Rectangle.GetXHigher() <= this->GetXHigher())){

				if((Rectangle.GetYLower() >= this->GetYLower() && Rectangle.GetYLower() <= this->GetYHigher()) ||
					(Rectangle.GetYHigher() >= this->GetYLower() && Rectangle.GetYHigher() <= this->GetYHigher())){
					return true;
				}
			}
			return false;
		}

		const CB::CString	CRectangle::ToString() const{
			return L"Position: (" + this->Position.ToString() + L"), Size: (" + this->Size.ToString() + L")";
		}

		const CRectangle&	CRectangle::operator=(const CRectangle& Rectangle){
			this->Position	= Rectangle.Position;
			this->Size		= Rectangle.Size;
			return *this;
		}

		const bool	CRectangle::operator==(const CRectangle& Rectangle) const{
			return this->IsEqual(Rectangle);
		}

		const bool	CRectangle::operator!=(const CRectangle& Rectangle) const{
			return !this->IsEqual(Rectangle);
		}

		const int32	CRectangle::operator[](const uint32 uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->GetXLower();
			case 1:	return this->GetYLower();
			case 2:	return this->GetXHigher();
			case 3:	return this->GetYHigher();
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		const Collection::CArray<int32, 4>	CRectangle::ToArray() const{
			int32 data[] = {
				Position.X, Position.Y,
				(int32)Size.Width, (int32)Size.Height
			};
			return Collection::CArray<int32, 4>(data, 4);
		}
	}
}