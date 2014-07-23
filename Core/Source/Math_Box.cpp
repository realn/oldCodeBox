#include "stdafx.h"
#include "../Include/Math_Box.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CBox::CBox(){
		}

		CBox::CBox(const CBox& Box) :
			Position(Box.Position),
			Size(Box.Size)
		{}

		CBox::CBox(const CPoint3D& Position, const CSize3D& Size) :
			Position(Position),
			Size(Size)
		{}

		CBox::CBox(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth) :
			Position(X, Y, Z),
			Size(Width, Height, Depth)
		{}

		void	CBox::SetZero(){
			this->Position.SetZero();
			this->Size.SetZero();
		}

		void	CBox::Set(const CBox& Box){
			this->Position = Box.Position;
			this->Size = Box.Size;
		}

		void	CBox::Set(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth){
			this->Position.Set(X, Y, Z);
			this->Size.Set(Width, Height, Depth);
		}

		const bool	CBox::IsZero() const{
			return this->Position.IsZero() && this->Size.IsZero();
		}

		const bool	CBox::IsPartialZero() const{
			return this->Position.IsPartialZero() || this->Size.IsPartialZero();
		}

		const bool	CBox::IsEqual(const CBox& Box) const{
			return this->Position.IsEqual(Box.Position) && this->Size.IsEqual(Box.Size);
		}

		const int32	CBox::GetXLower() const{
			return this->Position.X;
		}

		const int32	CBox::GetXHigher() const{
			return this->Position.X + this->Size.Width;
		}

		const int32	CBox::GetYLower() const{
			return this->Position.Y;
		}

		const int32 CBox::GetYHigher() const{
			return this->Position.Y + this->Size.Height;
		}

		const int32	CBox::GetZLower() const{
			return this->Position.Z;
		}

		const int32 CBox::GetZHigher() const{
			return this->Position.Z + this->Size.Depth;
		}

		const bool	CBox::Contains(const CPoint3D& Point) const{
			return Point.X >= this->GetXLower() && 
				Point.X <= this->GetXHigher() && 
				Point.Y >= this->GetYLower() && 
				Point.Y <= this->GetYHigher() &&
				Point.Z >= this->GetZLower() &&
				Point.Z <= this->GetZHigher();
		}

		const bool	CBox::Contains(const CBox& Box) const{
			return Box.GetXLower() >= this->GetXLower() &&
				Box.GetXHigher() <= this->GetXHigher() &&
				Box.GetYLower() >= this->GetYLower() &&
				Box.GetYHigher() <= this->GetYHigher() &&
				Box.GetZLower() >= this->GetZLower() &&
				Box.GetZHigher() <= this->GetZHigher();
		}

		const bool	CBox::Intersects(const CBox& Box) const{
			if((Box.GetXLower() >= this->GetXLower() && Box.GetXLower() <= this->GetXHigher()) || 
				(Box.GetXHigher() >= this->GetXLower() && Box.GetXHigher() <= this->GetXHigher())){

				if((Box.GetYLower() >= this->GetYLower() && Box.GetYLower() <= this->GetYHigher()) ||
					(Box.GetYHigher() >= this->GetYLower() && Box.GetYHigher() <= this->GetYHigher())){
					
					if((Box.GetZLower() >= this->GetZLower() && Box.GetZLower() <= this->GetZHigher()) ||
						(Box.GetZHigher() >= this->GetZLower() && Box.GetZHigher() <= this->GetZHigher())){
						return true;
					}
				}
			}
			return false;
		}

		const CB::CString	CBox::ToString() const{
			return L"Position: (" + this->Position.ToString() + L"), Size: (" + this->Size.ToString() + L")";
		}

		const CBox&	CBox::operator=(const CBox& Box){
			this->Position	= Box.Position;
			this->Size		= Box.Size;
			return *this;
		}

		const bool	CBox::operator==(const CBox& Box) const{
			return this->IsEqual(Box);
		}

		const bool	CBox::operator!=(const CBox& Box) const{
			return !this->IsEqual(Box);
		}

		const int32	CBox::operator[](const uint32 uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->GetXLower();
			case 1:	return this->GetYLower();
			case 2:	return this->GetZLower();
			case 3:	return this->GetXHigher();
			case 4:	return this->GetYHigher();
			case 5:	return this->GetZHigher();
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::ToString(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}
	}
}