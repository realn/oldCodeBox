#include "../Include/Ref.h"
#include "../Include/CBStringEx.h"

namespace CB{
	IRef::IRef() : 
		m_uRefCount(0)
	{}

	IRef::~IRef() {}

	const uint32 IRef::AddRef(){
		this->m_uRefCount++;

		return this->m_uRefCount;
	}

	const uint32 IRef::Release(){
		if(this->m_uRefCount > 0){
			this->m_uRefCount--;
		}
		else{
			throw Exception::CInvalidVarValueException(L"m_uRefCount", L"0",
				L"Release should not EVER be called when reference counter is 0!", CR_INFO());
		}

		if(this->m_uRefCount == 0){
			delete this;
			return 0;
		}

		return this->m_uRefCount;
	}

	const uint32 IRef::GetRefCount() const{
		return this->m_uRefCount;
	}
}