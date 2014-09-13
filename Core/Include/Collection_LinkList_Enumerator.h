#pragma once

#include "Macros.h"
#include "Types.h"
#include "Collection_LinkList_Node.h"
#include "Exception.h"

namespace CB{
	namespace Collection{
		template<typename _Type> class CLinkList;

		template<typename _Type>
		class CListEnumerator{
			friend CLinkList<_Type>;
		private:
			CLinkList<_Type>*	m_pList;
			CNode<_Type>*	m_pCurrent;
			bool	m_bPast;

		protected:
			CListEnumerator(const CLinkList<_Type>* pList, const CNode<_Type>* pCurrent);

		public:
			CListEnumerator(const CListEnumerator<_Type>& Enumerator);
			virtual ~CListEnumerator();

			void	ToFirst();
			void	ToLast();

			const bool	IsLast() const;
			const bool	IsFirst() const;

			const bool	IsEnd() const;
			const bool	IsReverseEnd() const;

			const bool	IsEmpty() const;
			const bool	IsValid() const;

			const bool	IsEqual(const CListEnumerator& Enumerator) const;

			const bool	HasNext() const;
			const bool	HasPrev() const;

			const bool	Next();
			const bool	Prev();

			const _Type&	Get() const;
			_Type&			Get();

			void		Set(const CListEnumerator& Enumerator);
			void		Swap(CListEnumerator& Enumerator);

			const CListEnumerator&	operator=(const CListEnumerator& Enumerator);

			const bool	operator==(const CListEnumerator& Enumerator) const;
			const bool	operator!=(const CListEnumerator& Enumerator) const;
		};


		//==============================================
		//	CLinkList::CListEnumerator
		//==============================================

		template<typename _Type>
		CListEnumerator<_Type>::CListEnumerator( const CLinkList<_Type>* pList, const CNode<_Type>* pNode ) :
			m_pList( const_cast<CLinkList<_Type>*>( pList ) ),
			m_pCurrent( const_cast<CNode<_Type>*>( pNode ) ),
			m_bPast( false )
		{}

		template<typename _Type>
		CListEnumerator<_Type>::CListEnumerator(const CListEnumerator<_Type>& Enumerator) : 
			m_pList(Enumerator.m_pList), 
			m_pCurrent(Enumerator.m_pCurrent),
			m_bPast(Enumerator.m_bPast)
		{}

		template<typename _Type>
		CListEnumerator<_Type>::~CListEnumerator(){
		}

		template<typename _Type>
		void	CListEnumerator<_Type>::ToFirst(){	
			while( !this->IsFirst() && this->IsValid() ){
				this->Prev();
			}
		}

		template<typename _Type>
		void	CListEnumerator<_Type>::ToLast(){	
			while( !this->IsLast() && this->IsValid() ){
				this->Next();
			}
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::IsLast() const{
			if( this->m_pCurrent == nullptr )
				return false;

			return this->m_pCurrent->m_pNext == nullptr && !m_bPast;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::IsFirst() const{
			if( this->m_pCurrent == nullptr )
				return false;

			return this->m_pCurrent->m_pPrev == nullptr && !m_bPast;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::IsEnd() const{
			if( this->m_pCurrent == nullptr )
				return true;

			return this->m_pCurrent->m_pNext == nullptr && m_bPast;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::IsReverseEnd() const{
			if( this->m_pCurrent == nullptr )
				return true;

			return this->m_pCurrent->m_pPrev == nullptr && m_bPast;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::IsEmpty() const{
			return this->m_pCurrent == nullptr;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::IsValid() const{
			return this->m_pCurrent != nullptr && !this->m_bPast;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::IsEqual(const CListEnumerator<_Type>& Enumerator) const{
			return this->m_pList == Enumerator.m_pList && this->m_pCurrent == Enumerator.m_pCurrent;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::HasNext() const{
			if( this->m_pCurrent == nullptr )
				return false;

			return this->m_pCurrent->m_pNext != nullptr && !this->m_bPast;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::HasPrev() const{
			if( this->m_pCurrent == nullptr )
				return false;

			return this->m_pCurrent->m_pPrev != nullptr && !this->m_bPast;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::Next(){
			if( this->m_pCurrent == nullptr ){
				return false;
			}
			if( this->m_pCurrent->m_pNext != nullptr ){
				if( !this->m_bPast )
					this->m_pCurrent = this->m_pCurrent->m_pNext;
				else
					this->m_bPast = false;
			}
			else if( !this->m_bPast )
				this->m_bPast = true;

			return this->IsValid();
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::Prev(){
			if( this->m_pCurrent == nullptr )
				return false;

			if( this->m_pCurrent->m_pPrev != nullptr ){
				if( !this->m_bPast )
					this->m_pCurrent = this->m_pCurrent->m_pPrev;
				else
					this->m_bPast = false;
			}
			else if( !this->m_bPast )
				this->m_bPast = true;

			return this->IsValid();
		}

		template<typename _Type>
		const _Type&	CListEnumerator<_Type>::Get() const{
			if(this->m_pCurrent){
				return this->m_pCurrent->GetValue();
			}
			throw CB::Exception::CNullPointerException(L"m_pCurrent",
				L"Enumerator doesn't have an set current item.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _Type>
		_Type&	CListEnumerator<_Type>::Get(){
			if(this->m_pCurrent){
				return this->m_pCurrent->GetValue();
			}
			throw CB::Exception::CNullPointerException(L"m_pCurrent",
				L"Enumerator doesn't have an set current item.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _Type>
		void	CListEnumerator<_Type>::Set(const CListEnumerator& Enumerator){
			this->m_pList		= Enumerator.m_pList;
			this->m_pCurrent	= Enumerator.m_pCurrent;
			this->m_bPast		= Enumerator.m_bPast;
		}

		template<typename _Type>
		void	CListEnumerator<_Type>::Swap(CListEnumerator& Enumerator){
			if(this->m_pCurrent == 0){
				throw CB::Exception::CNullPointerException(L"m_pCurrent",
					L"Enumerator pointer cannot be null for swapping.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(Enumerator.m_pCurrent == 0){
				throw CB::Exception::CNullArgumentException(L"Enumerator.m_pCurrent",
					L"Given enumerator cannot have a null pointer for swapping.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			this->m_pCurrent->Swap(Enumerator.m_pCurrent);
		}

		template<typename _Type>
		const typename CListEnumerator<_Type>&	CListEnumerator<_Type>::operator=(const CListEnumerator& Enumerator){
			this->Set(Enumerator);
			return *this;
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::operator==(const CListEnumerator& Enumerator) const{
			return this->IsEqual(Enumerator);
		}

		template<typename _Type>
		const bool	CListEnumerator<_Type>::operator!=(const CListEnumerator& Enumerator) const{
			return !this->IsEqual(Enumerator);
		}
	}
}