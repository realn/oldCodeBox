#pragma once

#include <Types.h>

namespace CB{
	namespace Math{
		class CRectangle;
	}

	namespace Graphic{
		class IOutputWindow{
		protected:
			IOutputWindow(){}

		public:
			virtual ~IOutputWindow(){}

			virtual void*	GetHandle() const = 0;
			virtual void	SetRect( const Math::CRectangle& rect ) = 0;
			virtual const Math::CRectangle	GetRect() const = 0;
		};
	}
}