#include "../Internal/ContextBindGuard.h"
#include "../Internal/WinPlatform.h"

namespace CB{
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