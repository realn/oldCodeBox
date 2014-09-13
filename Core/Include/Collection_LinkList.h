#pragma once

#include "Macros.h"
#include "Types.h"
#include "Collection_Interface.h"
#include "Collection_LinkList_Node.h"
#include "Collection_LinkList_Enumerator.h"
#include "Exception.h"
#include "CBString_Funcs.h"

namespace CB{
	namespace Collection{
		template<typename _Type>
		class CLinkList : 
			public ICountable<_Type>
		{
		public:
			typedef _Type CItem;
			typedef CListEnumerator<_Type> CEnumerator;

		protected:
			CNode<_Type>*	m_pFirst;
			CNode<_Type>*	m_pLast;
			uint32			m_uLength;

			CNode<_Type>*	FindLink(const uint32 uIndex) const;
			CNode<_Type>*	Unlink(CNode<_Type>* pItem);
			CNode<_Type>*	RemoveLink(const uint32 uIndex);
			_Type&	GetValue(const uint32 uIndex) const;
			_Type&	GetFirst() const;
			_Type&	GetLast() const;

		public:
			CLinkList();
			CLinkList(const CLinkList<_Type>& List);
			CLinkList(const ICountable<_Type>&	List);
			CLinkList(const _Type* pData, const uint32 uLength);
			virtual ~CLinkList();

			const uint32	Add(const _Type& Value);
			void			Insert(const _Type& Value);
			void			Insert(const uint32 uIndex, const _Type& Value);
			const _Type		Remove();
			const _Type		Remove(const uint32 uIndex);
			const _Type		Remove(CListEnumerator<_Type>& Enumerator);
			void			Delete(const uint32 uIndex);
			void			Delete(CListEnumerator<_Type>& Enumerator);

			const _Type&	Get(const uint32 uIndex) const;
			_Type&			Get(const uint32 uIndex);

			_Type&			First();
			const _Type&	First() const;
			_Type&			Last();
			const _Type&	Last() const;

			CListEnumerator<_Type>	GetEnumerator() const;

			void	Clear();

			const uint32	GetLength() const;
			const bool		IsEmpty() const;

			void	Set(const _Type* pData, const uint32 uLength);
			void	Set(const ICountable<_Type>& Array);
			void	Set(const CLinkList<_Type>& List);

			void	operator=(const CLinkList<_Type>& List);
			void	operator=(const ICountable<_Type>& Array);

			const _Type&	operator[](const uint32 uIndex) const;
			_Type&			operator[](const uint32 uIndex);
		};


		//============================================
		//	CLinkList
		//============================================

		template<typename _Type>
		CNode<_Type>*	CLinkList<_Type>::FindLink(const uint32 uIndex) const{
			if( this->IsEmpty() )
				return nullptr;

			if(uIndex == 0){
				return this->m_pFirst;
			}
			if(uIndex + 1 == this->m_uLength){
				return this->m_pLast;
			}

			if(uIndex < this->m_uLength / 2){
				CListEnumerator<_Type> Enum( this, this->m_pFirst );
					
				for(uint32 uCur = 0; uCur < this->m_uLength && Enum.IsValid(); uCur++){
					if(uCur == uIndex){
						return Enum.m_pCurrent;
					}
					Enum.Next();
				}
			}
			else{
				CListEnumerator<_Type> Enum( this, this->m_pLast );

				for(uint32 uCur = this->m_uLength - 1; uCur > 0 && Enum.IsValid(); uCur--){
					if( uCur == uIndex ){
						return Enum.m_pCurrent;
					}
					Enum.Prev();
				}
			}

			throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
				L"Cannot find specified index - wtf?", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _Type>
		CNode<_Type>*	CLinkList<_Type>::Unlink(CNode<_Type>* pItem){
			if(pItem->GetPrev()){
				pItem->GetPrev()->SetNext(pItem->GetNext());
			}
			else{
				this->m_pFirst = pItem->GetNext();
			}

			if(pItem->GetNext()){
				pItem->GetNext()->SetPrev(pItem->GetPrev());
			}
			else{
				this->m_pLast = pItem->GetPrev();
			}

			return pItem;
		}

		template<typename _Type>
		typename CNode<_Type>*	CLinkList<_Type>::RemoveLink(const uint32 uIndex){
			CNode<_Type>* pItem = this->FindLink(uIndex);
			return this->Unlink(pItem);
		}

		template<typename _Type>
		_Type&			CLinkList<_Type>::GetValue(const uint32 uIndex) const{
			if(this->IsEmpty()){
				throw CB::Exception::CZeroLengthException(L"List", 
					L"Cannot retrieve item from empty list.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(uIndex >= this->m_uLength){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				CNode<_Type>* pLink = this->FindLink(uIndex);
				return pLink->GetValue();
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while retriving list item.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}
		
		template<typename _Type>
		_Type&			CLinkList<_Type>::GetFirst() const{
			if(this->m_pFirst){
				return this->m_pFirst->GetValue();
			}
			throw CB::Exception::CNullPointerException(L"m_pFirst",
				L"No first item in list.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _Type>
		_Type&			CLinkList<_Type>::GetLast() const{
			if(this->m_pLast){
				return this->m_pLast->GetValue();
			}
			throw CB::Exception::CNullPointerException(L"m_pFirst",
				L"No last item in list.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _Type>
		CLinkList<_Type>::CLinkList() : 
			m_pFirst( nullptr ), 
			m_pLast( nullptr), 
			m_uLength( 0 )
		{}

		template<typename _Type>
		CLinkList<_Type>::CLinkList(const CLinkList<_Type>& List) : 
			m_pFirst( nullptr ), 
			m_pLast( nullptr), 
			m_uLength(0)
		{
			try{
				this->Set(List);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating list copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		CLinkList<_Type>::CLinkList(const ICountable<_Type>& List) : 
			m_pFirst( nullptr ), 
			m_pLast( nullptr ), 
			m_uLength( 0 )
		{
			try{
				this->Set(List);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating array copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		CLinkList<_Type>::CLinkList(const _Type* pData, const uint32 uLength) : 
			m_pFirst( nullptr ), 
			m_pLast( nullptr ), 
			m_uLength( 0 )
		{
			try{
				this->Set(pData, uLength);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating raw data copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		CLinkList<_Type>::~CLinkList(){
			this->Clear();
		}

		template<typename _Type>
		const uint32	CLinkList<_Type>::Add(const _Type& Value){
			try{
				CNode<_Type>* pCurrent	= new CNode<_Type>(Value);
				if(this->m_pLast){
					this->m_pLast->SetNext(pCurrent);
					pCurrent->SetPrev(this->m_pLast);

					this->m_pLast = pCurrent;
					return this->m_uLength++;
				}
				else{
					this->m_pFirst	= pCurrent;
					this->m_pLast	= pCurrent;
					this->m_uLength	= 1;

					return 0;
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while adding new element to list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		void	CLinkList<_Type>::Insert(const _Type& Value){
			this->Insert(0, Value);
		}

		template<typename _Type>
		void	CLinkList<_Type>::Insert(const uint32 uIndex, const _Type& Value){
			if(uIndex > this->m_uLength){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(uIndex == this->m_uLength){
				this->Add(Value);
				return;
			}

			try{
				CNode<_Type>* pCurrent	= new CNode<_Type>(Value);
				CNode<_Type>* pItem	= this->FindLink(uIndex);

				pCurrent->SetNext(pItem);
				pCurrent->SetPrev(pItem->GetPrev());

				if(pItem->GetPrev()){
					pItem->GetPrev()->SetNext(pCurrent);
				}
				else{
					this->m_pFirst = pCurrent;
				}
				pItem->SetPrev(pCurrent);

				this->m_uLength++;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"There was an error while inserting new element to list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		const _Type		CLinkList<_Type>::Remove(){
			if(this->m_uLength == 0){
				throw CB::Exception::CZeroLengthException(L"CLinkList", 
					L"Trying to remove from empty list.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return this->Remove(this->m_uLength - 1);
		}

		template<typename _Type>
		const _Type		CLinkList<_Type>::Remove(const uint32 uIndex){
			if(uIndex >= this->m_uLength){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			try{
				CNode<_Type>* pItem = this->RemoveLink(uIndex);

				_Type Value(pItem->GetValue());
					
				delete pItem;
				this->m_uLength--;
					
				return Value;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while removing item from list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		const _Type		CLinkList<_Type>::Remove(CListEnumerator<_Type>& Enumerator){
			if(Enumerator.m_pList != this){
				throw CB::Exception::CException(
					L"Enumerator is from another list.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(!Enumerator.m_pCurrent){
				throw CB::Exception::CNullArgumentException(L"Eunumerator.m_pCurrent",
					L"Enumerator must be set on a valid item, to remove it.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			CNode<_Type>* pLink = this->Unlink(Enumerator.m_pCurrent);
			_Type Value(pLink->GetValue());

			Enumerator.m_pCurrent = pLink->m_pNext;
			Enumerator.m_bPast = true;

			delete pLink;
			this->m_uLength--;

			return Value;
		}

		template<typename _Type>
		void	CLinkList<_Type>::Delete(const uint32 uIndex){
			if(uIndex >= this->m_uLength){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				CNode<_Type>* pItem = this->RemoveLink(uIndex);
				delete pItem;
				this->m_uLength--;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while deleting item from list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		void	CLinkList<_Type>::Delete(CListEnumerator<_Type>& Enumerator){
			if(Enumerator.m_pList != this){
				throw CB::Exception::CException(
					L"Enumerator is from another list.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(!Enumerator.m_pCurrent){
				throw CB::Exception::CNullArgumentException(L"Enumerator.m_pCurrent",
					L"Enumerator must be set on a valid item to delete it.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			CNode<_Type>* pLink = this->Unlink(Enumerator.m_pCurrent);

			Enumerator.m_pCurrent = pLink->m_pNext;
			Enumerator.m_bPast = true;

			this->m_uLength--;
			delete pLink;
		}

		template<typename _Type>
		const _Type&	CLinkList<_Type>::Get(const uint32 uIndex) const{
			return this->GetValue(uIndex);
		}

		template<typename _Type>
		_Type&	CLinkList<_Type>::Get(const uint32 uIndex){
			return this->GetValue(uIndex);
		}

		template<typename _Type>
		_Type&	CLinkList<_Type>::First(){
			return this->GetFirst();
		}
		
		template<typename _Type>
		const _Type&	CLinkList<_Type>::First() const{
			return this->GetFirst();
		}

		template<typename _Type>
		_Type&	CLinkList<_Type>::Last(){
			return this->GetLast();
		}

		template<typename _Type>
		const _Type&	CLinkList<_Type>::Last() const{
			return this->GetLast();
		}

		template<typename _Type>
		CListEnumerator<_Type>	CLinkList<_Type>::GetEnumerator() const{
			return CListEnumerator<_Type>( this, this->m_pFirst );
		}

		template<typename _Type>
		void	CLinkList<_Type>::Clear(){
			if(this->m_pFirst){
				try{
					CNode<_Type>* pCurrent	= this->m_pFirst;
					CNode<_Type>* pNext		= 0;
					while(pCurrent){
						pNext = pCurrent->GetNext();
						delete	pCurrent;
						pCurrent = pNext;
					}
				}
				catch(CB::Exception::CException& Exception){
					throw CB::Exception::CException(
						L"Error while clearing list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
				}
			}
			this->m_pFirst	= 0;
			this->m_pLast	= 0;
			this->m_uLength	= 0;
		}

		template<typename _Type>
		const uint32	CLinkList<_Type>::GetLength() const{
			return this->m_uLength;
		}

		template<typename _Type>
		const bool		CLinkList<_Type>::IsEmpty() const{
			return this->m_pFirst == 0 || this->m_pLast == 0 || this->m_uLength == 0;
		}

		template<typename _Type>
		void	CLinkList<_Type>::Set(const _Type* pData, const uint32 uLength){
			if(uLength == 0){
				this->Clear();
				return;
			}
			if(pData == 0){
				throw CB::Exception::CNullArgumentException(L"pData", 
					L"Empty data pointer for raw list copy.", __FUNCTIONW__, __FILEW__, __LINE__);
			}				
			try{
				this->Clear();
				for(uint32 uIndex = 0; uIndex < uLength; uIndex++){
					this->Add(pData[uIndex]);
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating raw data copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		void	CLinkList<_Type>::Set(const ICountable<_Type>& List){
			try{
				this->Clear();
				for(uint32 uIndex = 0; uIndex < List.GetLength(); uIndex++){
					this->Add(List[uIndex]);
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating array copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		void	CLinkList<_Type>::Set(const CLinkList<_Type>& List){
			try{
				this->Clear();
				CListEnumerator<_Type>	Enumerator = List.GetEnumerator();
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
					this->Add(Enumerator.Get());
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating list copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		void	CLinkList<_Type>::operator=(const CLinkList<_Type>& List){
			this->Set(List);
		}

		template<typename _Type>
		void	CLinkList<_Type>::operator=(const ICountable<_Type>& List){
			this->Set(List);
		}

		template<typename _Type>
		const _Type&	CLinkList<_Type>::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		template<typename _Type>
		_Type&	CLinkList<_Type>::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}


		//=============================
		//	LINK LIST FUNCTIONS
		//=============================

		template<typename _Type>
		const bool		TryGetEnumerator(const typename CLinkList<_Type>&, const _Type& Item, typename CListEnumerator<_Type>& Enumerator){
			for(; Enumerator.IsValid(); Enumerator.Next()){
				if(Enumerator.Get() == Item){
					return true;
				}
			}
			return false;
		}

		template<typename _Type>
		typename CListEnumerator<_Type>	GetEnumerator(typename const CLinkList<_Type>& List, const _Type& Item){
			typename CListEnumerator<_Type> Enumerator = List.GetEnumerator();
			Enumerator.ToFirst();
			if(!TryGetEnumerator<_Type>(Item, Enumerator)){
				throw CB::Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return Enumerator;
		}

		template<typename _Type>
		const bool		TryFind(const typename CLinkList<_Type>& List, const _Type& Item, unsigned& uOutIndex){
			unsigned uIndex = 0;
			typename CListEnumerator<_Type> Enumerator = List.GetEnumerator();
			for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
				if(Enumerator.Get() == Item){
					uOutIndex = uIndex;
					return true;
				}
				uIndex++;
			}
			return false;
		}

		template<typename _Type1, typename _Type2>
		const bool		TryFind(const typename CLinkList<_Type1>& List, const bool (*Compare)(const _Type1& ListItem, const _Type2& Comparable), const _Type2& Param, unsigned& uOutIndex){
			auto Enumerator = List.GetEnumerator();
			unsigned uIndex = 0;
			for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
				if(Compare(Enumerator.Get(), Param)){
					uOutIndex = uIndex;
					return true;
				}
				uIndex++;
			}
			return false;
		}

		template<typename _Type>
		const unsigned	Find(typename const CLinkList<_Type>& List, const _Type& Item){
			unsigned uIndex = 0;
			if(!TryGetIndex(List, Item, uIndex)){
				throw CB::Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return uIndex;
		}

		template<typename _Type1, typename _Type2>
		const bool		TryFind(const typename CLinkList<_Type1>& List, const bool (*Compare)(const _Type1& ListItem, const _Type2& Comparable), const _Type2& Param, typename CListEnumerator<_Type1>& Enumerator){
			for(; Enumerator.IsValid(); Enumerator.Next()){
				if(Compare(Enumerator.Get(), Param)){
					return true;
				}
			}
			return false;
		}

		template<typename _Type1, typename _Type2>
		const unsigned	Find(const typename CLinkList<_Type1>& List, const bool (*Compare)(const _Type1& ListItem, const _Type2& Comparable), const _Type2& Param){
			unsigned uIndex = 0;
			if(!TryFind(List, Compare, Param, uIndex)){
				throw Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return uIndex;
		}

		template<typename _Type1, typename _Type2>
		typename CLinkList<_Type1>::CListEnumerator	GetEnumerator(const typename CLinkList<_Type1>& List, const bool (*Compare)(const _Type1& ListItem, const _Type2& Comparable), const _Type2& Param){
			auto Enumerator = List.GetEnumerator();
			Enumerator.ToFirst();
			if(!TryFind(List, Compare, Param, Enumerator)){
				throw Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return Enumerator;
		}

		template<typename _Type>
		const bool		Contains(typename const CLinkList<_Type>& List, const _Type& Item){
			unsigned uIndex = 0;
			return TryFind(List, Item, uIndex);
		}

		template<typename _Type1, typename _Type2>
		const bool		Contains(typename const CLinkList<_Type1>& List, const bool (*Compare)(const _Type1& ListItem, const _Type2& Comparable), const _Type2& Param){
			auto Enumerator = List.GetEnumerator();
			Enumerator.ToFirst();
			return TryFind(List, Compare, Param, Enumerator);
		}
	}
}