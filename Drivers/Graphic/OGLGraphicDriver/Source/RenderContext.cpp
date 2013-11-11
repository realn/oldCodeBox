#include "../Internal/RenderContext.h"
#include "../Internal/OpenGL_WGL.h"
#include <Exception.h>

namespace CB{
	CRenderContext::CRenderContext() :
		m_GLContext(0)
	{}

	CRenderContext::CRenderContext(const IDeviceContext& DC) : 
		m_GLContext(0)
	{
		this->CreateContext(DC);
	}

	CRenderContext::~CRenderContext(){
		this->Free();
	}

	void	CRenderContext::Free(){
		if(this->m_GLContext){
			wglMakeCurrent(0, 0);
			wglDeleteContext(this->m_GLContext);
			this->m_GLContext = 0;
		}
	}

	void	CRenderContext::Bind(const IDeviceContext& DC){
		if(!wglMakeCurrent(DC.Get(), this->m_GLContext)){
			CR_THROWWIN(GetLastError(), L"Failed to make gl render context current.");
		}
	}

	void	CRenderContext::Unbind(){
		wglMakeCurrent(0, 0);
	}

	HGLRC&	CRenderContext::Get() const {
		return this->m_GLContext;
	}

	void	CRenderContext::CreateContext(const IDeviceContext& DC){
		this->m_GLContext = wglCreateContext(DC.Get());
		if(this->m_GLContext == 0){
			CR_THROWWIN(GetLastError(), L"Failed to create GL Legacy Context.");
		}
	}
}