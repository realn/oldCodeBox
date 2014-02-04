#include "../Internal/CGContext.h"
#include <Exception.h>

namespace CB{
	CCGContext::CCGContext() :
		m_Context(0)
	{
		this->m_Context = cgCreateContext();
		if(this->m_Context == 0){
			CR_THROW(L"Failed to create CG context.");
		}
	}

	CCGContext::CCGContext(CGcontext Context) :
		m_Context(Context)
	{}

	CCGContext::~CCGContext(){
		if(cgIsContext(this->m_Context)){
			cgDestroyContext(this->m_Context);
			this->m_Context = 0;
		}
	}

	CGcontext&	CCGContext::Get() const{
		return this->m_Context;
	}
}