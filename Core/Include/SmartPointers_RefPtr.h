#pragma once

#include "Types.h"
#include "SmartPointers_Ptr.h"
#include "Ref.h"

namespace CB{
	template<typename _Type>
	class CRefPtr : 
		public CPtr<_Type>
	{
	public:
		CRefPtr();
		CRefPtr(const CPtr<_Type>& Ptr);
		CRefPtr(const CRefPtr<_Type>& Ptr);
		CRefPtr(const _Type* pPtr);
		~CRefPtr();

		void	AddRef();
		void	Release();

		const CRefPtr<_Type>&	operator=(const _Type* pPtr);
		const CRefPtr<_Type>&	operator=(const CPtr<_Type>& Ptr);
		const CRefPtr<_Type>&	operator=(const CRefPtr<_Type>& Ptr);

		template<typename _TCast>
		CRefPtr<_TCast>	Cast() const{
			return this->GetCast<_TCast>();
		}
	};

	template<typename _Type>
	CRefPtr<_Type>::CRefPtr() : 
		CPtr<_Type>()
	{}

	template<typename _Type>
	CRefPtr<_Type>::CRefPtr(const CPtr<_Type>& Ptr) :
		CPtr<_Type>(Ptr)
	{
		this->AddRef();
	}

	template<typename _Type>
	CRefPtr<_Type>::CRefPtr(const CRefPtr<_Type>& Ptr) : 
		CPtr<_Type>(Ptr)
	{
		this->AddRef();
	}

	template<typename _Type>
	CRefPtr<_Type>::CRefPtr(const _Type* pPtr) : 
		CPtr<_Type>(pPtr)
	{
		this->AddRef();
	}

	template<typename _Type>
	CRefPtr<_Type>::~CRefPtr(){
		this->Release();
	}

	template<typename _Type>
	void	CRefPtr<_Type>::AddRef(){
		IRef* pRef = reinterpret_cast<IRef*>(this->m_pPtr);
		if(pRef){
			pRef->AddRef();
		}
	}

	template<typename _Type>
	void	CRefPtr<_Type>::Release(){
		IRef* pRef = reinterpret_cast<IRef*>(this->m_pPtr);
		if(pRef){
			pRef->Release();
			this->m_pPtr = 0;
		}
	}

	template<typename _Type>
	const CRefPtr<_Type>&	CRefPtr<_Type>::operator=(const _Type* pPtr){
		this->Release();
		this->m_pPtr = (_Type*)pPtr;
		this->AddRef();

		return *this;
	}

	template<typename _Type>
	const CRefPtr<_Type>&	CRefPtr<_Type>::operator=(const CPtr<_Type>& Ptr){
		this->Release();
		this->m_pPtr = (_Type*)Ptr.Get();
		this->AddRef();

		return *this;
	}

	template<typename _Type>
	const CRefPtr<_Type>&	CRefPtr<_Type>::operator=(const CRefPtr<_Type>& Ptr){
		this->Release();
		this->m_pPtr = Ptr.m_pPtr;
		this->AddRef();

		return *this;
	}
}