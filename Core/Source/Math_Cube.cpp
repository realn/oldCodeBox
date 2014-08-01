#include "stdafx.h"
#include "../Include/Math_Cube.h"
#include "../Include/Math_Rectangle.h"
#include "../Include/Exception.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_Array.h"

namespace CB{
	namespace Math{
		CCube::CCube(){
		}

		CCube::CCube(const CCube& Cube) :
			Position(Cube.Position),
			Size(Cube.Size)
		{}

		CCube::CCube(const CPoint3D& Position, const CSize3D& Size) :
			Position(Position),
			Size(Size)
		{}

		CCube::CCube(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth) :
			Position(X, Y, Z),
			Size(Width, Height, Depth)
		{}

		CCube::CCube(const CRectangle& Rect, int32 Z, uint32 Depth) :
			Position( Rect.Position, Z),
			Size( Rect.Size, Depth )
		{}

		CCube::CCube(const Collection::ICountable<int32>& array){
			if( array.GetLength() >= 6){
				Position.Set( array[0], array[1], array[2] );
				Size.Set( array[3], array[4], array[5] );
			}
		}

		void	CCube::SetZero(){
			this->Position.SetZero();
			this->Size.SetZero();
		}

		void	CCube::Set(const CCube& Cube){
			this->Position = Cube.Position;
			this->Size = Cube.Size;
		}

		void	CCube::Set(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth){
			this->Position.Set(X, Y, Z);
			this->Size.Set(Width, Height, Depth);
		}

		const bool	CCube::IsZero() const{
			return this->Position.IsZero() && this->Size.IsZero();
		}

		const bool	CCube::IsPartialZero() const{
			return this->Position.IsPartialZero() || this->Size.IsPartialZero();
		}

		const bool	CCube::IsEqual(const CCube& Cube) const{
			return this->Position.IsEqual(Cube.Position) && this->Size.IsEqual(Cube.Size);
		}

		const int32	CCube::GetXLower() const{
			return this->Position.X;
		}

		const int32	CCube::GetXHigher() const{
			return this->Position.X + this->Size.Width;
		}

		const int32	CCube::GetYLower() const{
			return this->Position.Y;
		}

		const int32 CCube::GetYHigher() const{
			return this->Position.Y + this->Size.Height;
		}

		const int32	CCube::GetZLower() const{
			return this->Position.Z;
		}

		const int32 CCube::GetZHigher() const{
			return this->Position.Z + this->Size.Depth;
		}

		const bool	CCube::Contains(const CPoint3D& Point) const{
			return Point.X >= this->GetXLower() && 
				Point.X <= this->GetXHigher() && 
				Point.Y >= this->GetYLower() && 
				Point.Y <= this->GetYHigher() &&
				Point.Z >= this->GetZLower() &&
				Point.Z <= this->GetZHigher();
		}

		const bool	CCube::Contains(const CCube& Cube) const{
			return Cube.GetXLower() >= this->GetXLower() &&
				Cube.GetXHigher() <= this->GetXHigher() &&
				Cube.GetYLower() >= this->GetYLower() &&
				Cube.GetYHigher() <= this->GetYHigher() &&
				Cube.GetZLower() >= this->GetZLower() &&
				Cube.GetZHigher() <= this->GetZHigher();
		}

		const bool	CCube::Intersects(const CCube& Cube) const{
			if((Cube.GetXLower() >= this->GetXLower() && Cube.GetXLower() <= this->GetXHigher()) || 
				(Cube.GetXHigher() >= this->GetXLower() && Cube.GetXHigher() <= this->GetXHigher())){

				if((Cube.GetYLower() >= this->GetYLower() && Cube.GetYLower() <= this->GetYHigher()) ||
					(Cube.GetYHigher() >= this->GetYLower() && Cube.GetYHigher() <= this->GetYHigher())){
					
					if((Cube.GetZLower() >= this->GetZLower() && Cube.GetZLower() <= this->GetZHigher()) ||
						(Cube.GetZHigher() >= this->GetZLower() && Cube.GetZHigher() <= this->GetZHigher())){
						return true;
					}
				}
			}
			return false;
		}

		const CB::CString	CCube::ToString() const{
			return L"Position: (" + this->Position.ToString() + L"), Size: (" + this->Size.ToString() + L")";
		}

		const CCube&	CCube::operator=(const CCube& Cube){
			this->Position	= Cube.Position;
			this->Size		= Cube.Size;
			return *this;
		}

		const bool	CCube::operator==(const CCube& Cube) const{
			return this->IsEqual(Cube);
		}

		const bool	CCube::operator!=(const CCube& Cube) const{
			return !this->IsEqual(Cube);
		}

		const int32	CCube::operator[](const uint32 uIndex) const{
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

		const Collection::CArray<int32, 6>	CCube::ToArray() const {
			int32 data[] = {
				Position.X, Position.Y, Position.Z,
				Size.Width, Size.Height, Size.Depth
			};
			return Collection::CArray<int32, 6>( data, 6 );
		}
	}
}