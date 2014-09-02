#pragma once

#include "Types.h"
#include "Exception.h"

namespace CB{
	template<typename _Type>
	class CPtr{
	protected:
		mutable _Type*	m_pPtr;

	public:
		CPtr();
		CPtr(const CPtr<_Type>& Ptr);
		CPtr(const _Type* pPtr);
		virtual ~CPtr();

		const _Type*	Get() const;
		_Type*	Get();
		_Type*	Reset();

		const bool	IsNull() const;
		const bool	IsValid() const;

		const bool	IsEqual(const CPtr<_Type>& Ptr) const;

		const CPtr<_Type>&	operator=(const CPtr<_Type>& Ptr);

		const bool	operator==(const CPtr<_Type>& Ptr) const;
		const bool	operator!=(const CPtr<_Type>& Ptr) const;

		const _Type&	operator*() const;
		_Type&	operator*();

		const _Type*	operator->() const;
		_Type*	operator->();

		template<typename _TCast>
		const _TCast*	GetCast() const{
			return dynamic_cast<const _TCast*>(this->m_pPtr);
		}

		template<typename _TCast>
		operator _TCast*(){
			return dynamic_cast<_TCast*>(this->m_pPtr);
		}
	};

	template<typename _Type>
	CPtr<_Type>::CPtr() : 
		m_pPtr(0)
	{}

	template<typename _Type>
	CPtr<_Type>::CPtr(const CPtr<_Type>& Ptr) : 
		m_pPtr(Ptr.m_pPtr)
	{}

	template<typename _Type>
	CPtr<_Type>::CPtr(const _Type* pPtr) : 
		m_pPtr((_Type*)pPtr)
	{
		if(this->m_pPtr == 0){
			throw CB::Exception::CNullArgumentException(L"pPtr",
				L"Trying to initialize smart pointer with null value.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	template<typename _Type>
	CPtr<_Type>::~CPtr(){
	}

	template<typename _Type>
	const _Type*	CPtr<_Type>::Get() const{
		return this->m_pPtr;
	}

	template<typename _Type>
	_Type*	CPtr<_Type>::Get(){
		return this->m_pPtr;
	}

	template<typename _Type>
	_Type*	CPtr<_Type>::Reset(){
		_Type* pPtr = this->m_pPtr;
		this->m_pPtr = 0;
		return pPtr;
	}

	template<typename _Type>
	const bool	CPtr<_Type>::IsNull() const{
		return this->m_pPtr == 0;
	}

	template<typename _Type>
	const bool	CPtr<_Type>::IsValid() const{
		return this->m_pPtr != 0;
	}

	template<typename _Type>
	const bool	CPtr<_Type>::IsEqual(const CPtr<_Type>& Ptr) const{
		return this->m_pPtr == Ptr.m_pPtr;
	}


	template<typename _Type>
	const CPtr<_Type>&	CPtr<_Type>::operator=(const CPtr<_Type>& Ptr){
		this->m_pPtr = Ptr.m_pPtr;
		return *this;
	}

	template<typename _Type>
	const bool	CPtr<_Type>::operator==(const CPtr<_Type>& Ptr) const{
		return this->IsEqual(Ptr);
	}

	template<typename _Type>
	const bool	CPtr<_Type>::operator!=(const CPtr<_Type>& Ptr) const{
		return !this->IsEqual(Ptr);
	}

	template<typename _Type>
	const _Type&	CPtr<_Type>::operator*() const{
		if(this->m_pPtr){
			return *this->m_pPtr;
		}
		throw CB::Exception::CNullPointerException(L"m_pPtr",
			L"Trying to access object from null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	template<typename _Type>
	_Type&	CPtr<_Type>::operator*(){
		if(this->m_pPtr){
			return *this->m_pPtr;
		}
		throw CB::Exception::CNullPointerException(L"m_pPtr",
			L"Trying to access object from null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	template<typename _Type>
	const _Type*	CPtr<_Type>::operator->() const{
		if(this->m_pPtr){
			return this->m_pPtr;
		}
		throw CB::Exception::CNullPointerException(L"m_pPtr",
			L"Trying to access object members by null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	template<typename _Type>
	_Type*	CPtr<_Type>::operator->(){
		if(this->m_pPtr){
			return this->m_pPtr;
		}
		throw CB::Exception::CNullPointerException(L"m_pPtr",
			L"Trying to access object members by null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
}