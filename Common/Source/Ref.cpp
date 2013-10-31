#include "../Include/Ref.h"
#include "../Include/CBStringEx.h"

CB::IRef::IRef() : m_uRefCount(0){
	this->m_uRefCount = 0;
}

CB::IRef::~IRef(){
	if(this->m_uRefCount != 0){
		throw CB::Exception::CNotZeroReferenceException( 
			L"Reference counter is not zero while deleting object.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
}

const unsigned CB::IRef::AddRef(){
	this->m_uRefCount++;

	return this->m_uRefCount;
}

const unsigned CB::IRef::Release(){
	if(this->m_uRefCount > 0){
		this->m_uRefCount--;
	}

	if(this->m_uRefCount == 0){
		delete this;
		return 0;
	}

	return this->m_uRefCount;
}

const unsigned CB::IRef::GetRefCount() const{
	return this->m_uRefCount;
}

//	Not zero reference exception

CB::Exception::CNotZeroReferenceException::CNotZeroReferenceException(const CB::Exception::CNotZeroReferenceException& Exception)
	: CException(Exception){
}

CB::Exception::CNotZeroReferenceException::CNotZeroReferenceException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const unsigned uLine)
	: CException(strMessage, strFunction, strFile, uLine){
}

CB::Exception::CNotZeroReferenceException::CNotZeroReferenceException(const CB::CString& strMessage, const CB::CString& strFunction, const CB::CString& strFile, const unsigned uLine, const CB::Exception::CException& InnerException)
	: CException(strMessage, strFunction, strFile, uLine, InnerException){
}

const CB::CString	CB::Exception::CNotZeroReferenceException::GetMessage() const{
	return L"Reference counter of object is not zero. " + this->m_strMessage;
}

CB::Exception::CException*	CB::Exception::CNotZeroReferenceException::CreateCopy() const{
	return new CNotZeroReferenceException(*this);
}