#include "../Internal/RenderContext.h"
#include "../Internal/OpenGL_WGL.h"
#include <Exception.h>
#include <Collection_List.h>
#include <Logger.h>

namespace CB{
	CRenderContext::CRenderContext() :
		m_GLContext(0)
	{}

	CRenderContext::~CRenderContext(){
		this->Free();
	}

	void	CRenderContext::Free(){
		if(this->m_GLContext){
			if(this->IsBinded()){
				wglMakeCurrent(0, 0);
			}
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

	const bool	CRenderContext::IsBinded() const{
		return wglGetCurrentContext() == this->m_GLContext;
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

	const bool	CRenderContext::CreateContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs){
		if(!WGL::Loader::IsSupported(WGL::Loader::Extension::CreateContext)){
			return false;
		}
		if(Attribs.GetLength() % 2 != 0){
			CR_THROW(L"Incorrect length attrib array for render context creation (not multiple of 2).");
		}

		Collection::CList<int32> newAttribs(Attribs);

		if(!WGL::Loader::IsSupported(WGL::Loader::Extension::CreateContextProfile)){
			Log::Write(L"Context Profile extension unsupproted, removing attributes from array.");

			for(uint32 uIndex = newAttribs.GetLength(); uIndex > 0; uIndex -= 2){
				if(newAttribs[uIndex - 1] == WGL::WGL_CONTEXT_PROFILE_MASK){
					newAttribs.Remove(uIndex - 1);
					newAttribs.Remove(uIndex - 1);
				}
			}
		}

		uint32 uLen = newAttribs.GetLength();
		if(newAttribs.GetLength() > 0 && newAttribs[uLen - 1] != 0 && newAttribs[uLen - 2] != 0){
			newAttribs.Add(0);
			newAttribs.Add(0);
		}

		this->m_GLContext = WGL::wglCreateContextAttribs(DC.Get(), 0, newAttribs.GetPointer());
		if(this->m_GLContext == 0){
			CR_THROWWIN(GetLastError(), L"Failed to create GL Core Context.");
		}

		return true;
	}
}