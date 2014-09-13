#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	namespace Collection{
		template<typename _Type> class CLinkList;
		template<typename _Type> class CListEnumerator;

		template<typename _Type>
		class CNode{
			friend CLinkList<_Type>;
			friend CListEnumerator<_Type>;
		private:
			CNode*	m_pNext;
			CNode*	m_pPrev;
			mutable _Type	m_Value;

		public:
			CNode(const _Type& Value);
			CNode(const _Type& Value, CNode* pNext, CNode* pPrev);

			CNode*	GetNext() const;
			CNode*	GetPrev() const;

			void	SetNext(CNode* pNext);
			void	SetPrev(CNode* pPrev);

			_Type&	GetValue() const;

			void	Swap(CNode* pNode);
		};

		//=========================================
		//	CLinkList::CNode
		//=========================================

		template<typename _Type>
		CNode<_Type>::CNode(const _Type& Value) : 
			m_Value(Value), 
			m_pNext(0), 
			m_pPrev(0)
		{}

		template<typename _Type>
		CNode<_Type>::CNode(const _Type& Value, typename CNode<_Type>* pNext, typename CNode<_Type>* pPrev) : 
			m_Value(Value), 
			m_pNext(pNext), 
			m_pPrev(pPrev)
		{}

		template<typename _Type>
		typename CNode<_Type>*	CNode<_Type>::GetNext() const{	
			return this->m_pNext;	
		}

		template<typename _Type>
		typename CNode<_Type>*	CNode<_Type>::GetPrev() const{	
			return this->m_pPrev;	
		}

		template<typename _Type>
		void	CNode<_Type>::SetNext(CNode* pNext){	
			this->m_pNext = pNext;	
		}

		template<typename _Type>
		void	CNode<_Type>::SetPrev(CNode* pPrev){	
			this->m_pPrev = pPrev;	
		}

		template<typename _Type>
		_Type&	CNode<_Type>::GetValue() const{
			return this->m_Value;	
		}

		template<typename _Type>
		void	CNode<_Type>::Swap(CNode* pNode){
			CNode* pTemp = 0;

			pTemp = this->GetNext();
			this->SetNext(pNode->GetNext());
			pNode->SetNext(pTemp);

			pTemp = this->GetPrev();
			this->SetPrev(pNode->GetPrev());
			pNode->SetPrev(pTemp);
		}
	}
}