#include "stdafx.h"
#include "../Include/Math_Size.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Math{
		CSize::CSize() : 
			Width(0), 
			Height(0)
		{}

		CSize::CSize(const CSize& Size) : 
			Width(Size.Width), 
			Height(Size.Height)
		{}

		CSize::CSize(const CPoint& Point) : 
			Width(Point.X > 0 ? Point.X : 0), 
			Height(Point.Y > 0 ? Point.Y : 0)
		{}

		CSize::CSize(const uint32 uValue) : 
			Width(uValue), 
			Height(uValue)
		{}

		CSize::CSize(const uint32 uWidth, const uint32 uHeight) : 
			Width(uWidth), 
			Height(uHeight)
		{}

		void	CSize::SetZero(){
			this->Width = 0;
			this->Height = 0;
		}

		void	CSize::Set(const CSize& Size){
			this->Width = Size.Width;
			this->Height = Size.Height;
		}

		void	CSize::Set(const uint32 uValue){
			this->Width = uValue;
			this->Height = uValue;
		}

		void	CSize::Set(const uint32 uWidth, const uint32 uHeight){
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
			return L"Width: " + String::ToString(this->Width) + L", Height: " + String::ToString(this->Height);
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

		const uint32&	CSize::operator[](const uint32 uIndex) const{
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}

		uint32&	CSize::operator[](const uint32 uIndex){
			switch (uIndex)
			{
			case 0:	return this->Width;
			case 1:	return this->Height;
			default:
				throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}
		}
	}
}