#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class COMMON_API CHiddenPtr{
	private:
		void* m_pPtr;

	public:
		CHiddenPtr() : m_pPtr(0){}
		CHiddenPtr(const CHiddenPtr& Ptr) : m_pPtr(Ptr.m_pPtr){}

		template<typename _Type>
		void	Set(_Type* pPtr){
			this->m_pPtr = reinterpret_cast<void*>(pPtr);
		}
		template<typename _Type>
		void	SetCast(_Type pPtr){
			this->m_pPtr = reinterpret_cast<void*>(pPtr);
		}
		template<typename _Type>
		_Type*	Get() const{
			return reinterpret_cast<_Type*>(this->m_pPtr);
		}
		template<typename _Type>
		void	Delete(){
			_Type* pPtr = reinterpret_cast<_Type*>(this->m_pPtr);
			delete pPtr;
			this->m_pPtr = 0;
		}
		template<typename _Type>
		_Type*	Reset(){
			_Type* pPtr = reinterpret_cast<_Type*>(this->m_pPtr);
			this->m_pPtr = 0;
			return pPtr;
		}
		template<typename _Type>
		_Type	ResetCast(){
			_Type pPtr = reinterpret_cast<_Type>(this->m_pPtr);
			this->m_pPtr = 0;
			return pPtr;
		}

		template<typename _Type>
		_Type	GetCast() const{
			return reinterpret_cast<_Type>(this->m_pPtr);
		}

		const bool	IsValid() const{
			return this->m_pPtr != 0;
		}
		const bool	IsNull() const{
			return this->m_pPtr == 0;
		}
	};
}