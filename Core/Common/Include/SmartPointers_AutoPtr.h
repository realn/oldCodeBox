#pragma once

#include "Types.h"
#include "Exception.h"
#include "SmartPointers_Ptr.h"

namespace CB{
	template<typename _Type>
	class CAutoPtr : 
		public CPtr<_Type>
	{
	private:
		CAutoPtr(const CAutoPtr<_Type>& Ptr){}
		const CAutoPtr<_Type>&	operator=(const CAutoPtr<_Type>& Ptr){ return *this; }
		const CAutoPtr<_Type>&	operator=(const CPtr<_Type>& Ptr){ return *this;	}

	public:
		CAutoPtr();
		CAutoPtr(const _Type* pPtr);
		CAutoPtr(const CPtr<_Type>& pPtr);
		~CAutoPtr();

		void	Destroy();

		const CAutoPtr<_Type>&	operator=(const _Type* pPtr);
	};

	template<typename _Type>
	CAutoPtr<_Type>::CAutoPtr(){
	}

	template<typename _Type>
	CAutoPtr<_Type>::CAutoPtr(const _Type* pPtr) : 
		CPtr<_Type>(pPtr)
	{}

	template<typename _Type>
	CAutoPtr<_Type>::CAutoPtr(const CPtr<_Type>& pPtr) :
		CPtr<_Type>(pPtr)
	{}

	template<typename _Type>
	CAutoPtr<_Type>::~CAutoPtr(){
		this->Destroy();
	}

	template<typename _Type>
	void	CAutoPtr<_Type>::Destroy(){
		if(this->m_pPtr){
			delete this->m_pPtr;
			this->m_pPtr = 0;
		}
	}

	template<typename _Type>
	const CAutoPtr<_Type>&	CAutoPtr<_Type>::operator=(const _Type* pPtr){
		if(this->m_pPtr){
			throw CB::Exception::CException(
				L"Tried to assign raw pointer to not released auto pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
		this->m_pPtr = pPtr;
		return *this;
	}
}