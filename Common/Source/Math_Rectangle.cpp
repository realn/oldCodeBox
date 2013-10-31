#include "../Include/Math_Rectangle.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CRectangle::CRectangle() : Position(), Size(){
		}

		CRectangle::CRectangle(const CRectangle& Rectangle) : Position(Rectangle.Position), Size(Rectangle.Size){
		}

		CRectangle::CRectangle(const CPoint& Position, const CSize& Size) 
			: Position(Position), Size(Size){
		}

		CRectangle::CRectangle(const int iX, const int iY, const CSize& Size)
			: Position(iX, iY), Size(Size){
		}

		CRectangle::CRectangle(const CPoint& Position, const unsigned uWidth, const unsigned uHeight)
			: Position(Position), Size(uWidth, uHeight){
		}

		CRectangle::CRectangle(const int iX, const int iY, const unsigned uWidth, const unsigned uHeight)
			: Position(iX, iY), Size(uWidth, uHeight){
		}

		void	CRectangle::SetZero(){
			this->Position.SetZero();
			this->Size.SetZero();
		}

		void	CRectangle::Set(const CRectangle& Rect){
			this->Position = Rect.Position;
			this->Size = Rect.Size;
		}

		void	CRectangle::Set(const int iX, const int iY, const unsigned uWidth, const unsigned uHeight){
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

		const int	CRectangle::GetLeft() const{
			return this->Position.X;
		}

		const int	CRectangle::GetRight() const{
			return this->Position.X + this->Size.Width;
		}

		const int	CRectangle::GetTop() const{
			return this->Position.Y;
		}

		const int	CRectangle::GetBottom() const{
			return this->Position.Y + this->Size.Height;
		}

		const bool	CRectangle::Contains(const CPoint& Point) const{
			return Point.X >= this->GetLeft() && 
				Point.X <= this->GetRight() && 
				Point.Y >= this->GetTop() && 
				Point.Y <= this->GetTop();
		}

		const bool	CRectangle::Contains(const CRectangle& Rectangle) const{
			return Rectangle.GetLeft() >= this->GetLeft() &&
				Rectangle.GetRight() <= this->GetRight() &&
				Rectangle.GetTop() >= this->GetTop() &&
				Rectangle.GetBottom() <= this->GetBottom();
		}

		const bool	CRectangle::Intersects(const CRectangle& Rectangle) const{
			if((Rectangle.GetLeft() >= this->GetLeft() && Rectangle.GetLeft() <= this->GetRight()) || 
				(Rectangle.GetRight() >= this->GetLeft() && Rectangle.GetRight() <= this->GetRight())){

				if((Rectangle.GetTop() >= this->GetTop() && Rectangle.GetTop() <= this->GetBottom()) ||
					(Rectangle.GetBottom() >= this->GetTop() && Rectangle.GetBottom() <= this->GetBottom())){
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

		const int	CRectangle::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->GetLeft();
			case 1:	return this->GetTop();
			case 2:	return this->GetRight();
			case 3:	return this->GetBottom();
			default:
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}