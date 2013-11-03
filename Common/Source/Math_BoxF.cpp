#include "../Include/Math_BoxF.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CBoxF::CBoxF(){
		}

		CBoxF::CBoxF(const CBoxF& Box) :
			Position(Box.Position),
			Size(Box.Size)
		{}

		CBoxF::CBoxF(const CVector3D& Position, const CVector3D& Size) :
			Position(Position),
			Size(Size)
		{}

		CBoxF::CBoxF(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth) :
			Position(X, Y, Z),
			Size(Width, Height, Depth)
		{}

		void	CBoxF::SetZero(){
			this->Position.SetZero();
			this->Size.SetZero();
		}

		void	CBoxF::Set(const CBoxF& Box){
			this->Position = Box.Position;
			this->Size = Box.Size;
		}

		void	CBoxF::Set(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth){
			this->Position.Set(X, Y, Z);
			this->Size.Set(Width, Height, Depth);
		}

		const bool	CBoxF::IsZero() const{
			return this->Position.IsZero() && this->Size.IsZero();
		}

		const bool	CBoxF::IsPartialZero() const{
			return this->Position.IsPartialZero() || this->Size.IsPartialZero();
		}

		const bool	CBoxF::IsEqual(const CBoxF& Box) const{
			return this->Position.IsEqual(Box.Position) && this->Size.IsEqual(Box.Size);
		}

		const float32	CBoxF::GetXLower() const{
			return this->Position.X;
		}

		const float32	CBoxF::GetXHigher() const{
			return this->Position.X + this->Size.X;
		}

		const float32	CBoxF::GetYLower() const{
			return this->Position.Y;
		}

		const float32 CBoxF::GetYHigher() const{
			return this->Position.Y + this->Size.Y;
		}

		const float32	CBoxF::GetZLower() const{
			return this->Position.Z;
		}

		const float32 CBoxF::GetZHigher() const{
			return this->Position.Z + this->Size.Z;
		}

		const bool	CBoxF::Contains(const CVector3D& Point) const{
			return Point.X >= this->GetXLower() && 
				Point.X <= this->GetXHigher() && 
				Point.Y >= this->GetYLower() && 
				Point.Y <= this->GetYHigher() &&
				Point.Z >= this->GetZLower() &&
				Point.Z <= this->GetZHigher();
		}

		const bool	CBoxF::Contains(const CBoxF& Box) const{
			return Box.GetXLower() >= this->GetXLower() &&
				Box.GetXHigher() <= this->GetXHigher() &&
				Box.GetYLower() >= this->GetYLower() &&
				Box.GetYHigher() <= this->GetYHigher() &&
				Box.GetZLower() >= this->GetZLower() &&
				Box.GetZHigher() <= this->GetZHigher();
		}

		const bool	CBoxF::Intersects(const CBoxF& Box) const{
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

		const CB::CString	CBoxF::ToString() const{
			return L"Position: (" + this->Position.ToString() + L"), Size: (" + this->Size.ToString() + L")";
		}

		const CBoxF&	CBoxF::operator=(const CBoxF& Box){
			this->Position	= Box.Position;
			this->Size		= Box.Size;
			return *this;
		}

		const bool	CBoxF::operator==(const CBoxF& Box) const{
			return this->IsEqual(Box);
		}

		const bool	CBoxF::operator!=(const CBoxF& Box) const{
			return !this->IsEqual(Box);
		}

		const float32	CBoxF::operator[](const uint32 uIndex) const{
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