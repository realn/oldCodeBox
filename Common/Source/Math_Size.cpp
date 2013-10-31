#include "../Include/Math_Size.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CSize::CSize() : Width(0), Height(0){}

		CSize::CSize(const CSize& Size) : Width(Size.Width), Height(Size.Height){}

		CSize::CSize(const CPoint& Point) : Width(Point.X > 0 ? Point.X : 0), Height(Point.Y > 0 ? Point.Y : 0){}

		CSize::CSize(const unsigned uValue) : Width(uValue), Height(uValue){}

		CSize::CSize(const unsigned uWidth, const unsigned uHeight) : Width(uWidth), Height(uHeight){}

		void	CSize::SetZero(){
			this->Width = 0;
			this->Height = 0;
		}

		void	CSize::Set(const CSize& Size){
			this->Width = Size.Width;
			this->Height = Size.Height;
		}

		void	CSize::Set(const unsigned uValue){
			this->Width = uValue;
			this->Height = uValue;
		}

		void	CSize::Set(const unsigned uWidth, const unsigned uHeight){
			this->Width		= uWidth;
			this->Height	= uHeight;
		}

		const bool	CSize::IsZero() const{
			return this->Width == 0 && this->Height == 0;
		}

		const bool	CSize::IsPartialZero() const{
			return this->Width == 0 || this->Height == 0;
		}

		const bool	CSize::IsEqual(const CSize& Size) const{
			return this->Width == Size.Width && this->Height == Size.Height;
		}

		const CString	CSize::ToString() const{
			return L"Width: " + String::FromUInt32(this->Width) + L", Height: " + String::FromUInt32(this->Height);
		}

		const CPoint	CSize::ToPoint() const{
			return CPoint(this->Width, this->Height);
		}

		const CSize&	CSize::operator=(const CSize& Size){
			this->Set(Size);
			return *this;
		}

		const bool	CSize::operator==(const CSize& Size) const{
			return this->IsEqual(Size);
		}

		const bool	CSize::operator!=(const CSize& Size) const{
			return !this->IsEqual(Size);
		}

		const unsigned&	CSize::operator[](const unsigned uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		unsigned&	CSize::operator[](const unsigned uIndex){
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}