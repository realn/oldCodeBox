#include "stdafx.h"
#include "../Internal/Graphic_RCBindGuard.h"

namespace CB{
	namespace Internal{
		CRCBindGuard::CRCBindGuard() :
			m_hDC(0),
			m_hRC(0)
		{
			this->m_hDC = wglGetCurrentDC();
			this->m_hRC = wglGetCurrentContext();
		}

		CRCBindGuard::~CRCBindGuard(){
			wglMakeCurrent((HDC)this->m_hDC, (HGLRC)this->m_hRC);
		}
	}
}