#include "../Include/Ref.h"
#include "../Include/CBStringEx.h"

namespace CB{
	IRef::IRef() : 
		m_uRefCount(0)
	{}

	IRef::~IRef(){
		try{
			// Exception throw kept for VS2012 exception lookup.
			if(this->m_uRefCount != 0){
				throw Exception::CNotZeroReferenceException( 
					L"Reference counter is not zero while deleting object.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
		catch(Exception::CException&){}
	}

	const uint32 IRef::AddRef(){
		this->m_uRefCount++;

		return this->m_uRefCount;
	}

	const uint32 IRef::Release(){
		if(this->m_uRefCount > 0){
			this->m_uRefCount--;
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

	//	Not zero reference exception

	Exception::CNotZeroReferenceException::CNotZeroReferenceException(const Exception::CNotZeroReferenceException& Exception)
		: CException(Exception)
	{}

	Exception::CNotZeroReferenceException::CNotZeroReferenceException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine)
		: CException(strMessage, strFunction, strFile, uLine)
	{}

	Exception::CNotZeroReferenceException::CNotZeroReferenceException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const Exception::CException& InnerException)
		: CException(strMessage, strFunction, strFile, uLine, InnerException)
	{}

	const CString	Exception::CNotZeroReferenceException::GetMessage() const{
		return L"Reference counter of object is not zero. " + this->m_strMessage;
	}

	Exception::CException*	Exception::CNotZeroReferenceException::CreateCopy() const{
		return new CNotZeroReferenceException(*this);
	}
}