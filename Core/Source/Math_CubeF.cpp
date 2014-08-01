#include "stdafx.h"
#include "../Include/Math_CubeF.h"
#include "../Include/Math_RectangleF.h"
#include "../Include/Exception.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CCubeF::CCubeF(){
		}

		CCubeF::CCubeF(const CCubeF& Box) :
			Position(Box.Position),
			Size(Box.Size)
		{}

		CCubeF::CCubeF(const CVector3D& Position, const CVector3D& Size) :
			Position(Position),
			Size(Size)
		{}

		CCubeF::CCubeF(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth) :
			Position(X, Y, Z),
			Size(Width, Height, Depth)
		{}

		CCubeF::CCubeF(const CRectangleF32& rect, const float32 Z, const float32 Depth) :
			Position( rect.Position, Z),
			Size( rect.Size, Depth)
		{}

		void	CCubeF::SetZero(){
			this->Position.SetZero();
			this->Size.SetZero();
		}

		void	CCubeF::Set(const CCubeF& Box){
			this->Position = Box.Position;
			this->Size = Box.Size;
		}

		void	CCubeF::Set(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth){
			this->Position.Set(X, Y, Z);
			this->Size.Set(Width, Height, Depth);
		}

		const bool	CCubeF::IsZero() const{
			return this->Position.IsZero() && this->Size.IsZero();
		}

		const bool	CCubeF::IsPartialZero() const{
			return this->Position.IsPartialZero() || this->Size.IsPartialZero();
		}

		const bool	CCubeF::IsEqual(const CCubeF& Box) const{
			return this->Position.IsEqual(Box.Position) && this->Size.IsEqual(Box.Size);
		}

		const float32	CCubeF::GetXLower() const{
			return this->Position.X;
		}

		const float32	CCubeF::GetXHigher() const{
			return this->Position.X + this->Size.X;
		}

		const float32	CCubeF::GetYLower() const{
			return this->Position.Y;
		}

		const float32 CCubeF::GetYHigher() const{
			return this->Position.Y + this->Size.Y;
		}

		const float32	CCubeF::GetZLower() const{
			return this->Position.Z;
		}

		const float32 CCubeF::GetZHigher() const{
			return this->Position.Z + this->Size.Z;
		}

		const bool	CCubeF::Contains(const CVector3D& Point) const{
			return Point.X >= this->GetXLower() && 
				Point.X <= this->GetXHigher() && 
				Point.Y >= this->GetYLower() && 
				Point.Y <= this->GetYHigher() &&
				Point.Z >= this->GetZLower() &&
				Point.Z <= this->GetZHigher();
		}

		const bool	CCubeF::Contains(const CCubeF& Box) const{
			return Box.GetXLower() >= this->GetXLower() &&
				Box.GetXHigher() <= this->GetXHigher() &&
				Box.GetYLower() >= this->GetYLower() &&
				Box.GetYHigher() <= this->GetYHigher() &&
				Box.GetZLower() >= this->GetZLower() &&
				Box.GetZHigher() <= this->GetZHigher();
		}

		const bool	CCubeF::Intersects(const CCubeF& Box) const{
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

		const CB::CString	CCubeF::ToString() const{
			return L"Position: (" + this->Position.ToString() + L"), Size: (" + this->Size.ToString() + L")";
		}

		const CCubeF&	CCubeF::operator=(const CCubeF& Box){
			this->Position	= Box.Position;
			this->Size		= Box.Size;
			return *this;
		}

		const bool	CCubeF::operator==(const CCubeF& Box) const{
			return this->IsEqual(Box);
		}

		const bool	CCubeF::operator!=(const CCubeF& Box) const{
			return !this->IsEqual(Box);
		}

		const float32	CCubeF::operator[](const uint32 uIndex) const{
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

		const Collection::CArray<float32, 6>	CCubeF::ToArray() const{
			float32 data[] = {
				Position.X, Position.Y, Position.Z,
				Size.X, Size.Y, Size.Z
			};
			return Collection::CArray<float32, 5>( data, 6 );
		}
	}
}