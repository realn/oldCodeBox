#pragma once

#include "Types.h"
#include "Collection_Interface.h"
#include "Collection_LinkList.h"
#include "Collection_List.h"
#include "Collection_Dictionary_Enumerator.h"
#include "Exception.h"

namespace CB{
	namespace Collection{
		template<typename _KeyType, typename _ValueType>
		class CDictionary : 
			public CLinkList<CPair<_KeyType, _ValueType>>
		{
		public:
			typedef CPair<_KeyType, _ValueType>	CItem;
			typedef CLinkList<CItem> CDictionaryList;
			typedef CDictEnumerator<_KeyType, _ValueType> CEnumerator;

		protected:
			const bool	GetItemByKey(const _KeyType& Key, CDictEnumerator<_KeyType, _ValueType>& Enumerator) const;
			CItem&	GetItemByKey( const _KeyType& Key ) const;
			_ValueType&	GetValue(const _KeyType& Key) const;
			CItem&	GetItemByIndex(const uint32 uIndex) const;

		public:
			CDictionary();
			CDictionary(const CDictionary<_KeyType, _ValueType>& Dictionary);
			CDictionary(const ICountable<_KeyType>& KeyList, const ICountable<_ValueType>& ValueList);
			CDictionary(const _KeyType* pKeys, const uint32 uKeysLength, const _ValueType* pValues, const uint32 uValuesLength);

			const uint32	Add(const CItem& Item);
			const uint32	Add(const _KeyType& Key, const _ValueType& Value);
			void			Insert(const CItem& Item);
			void			Insert(const _KeyType& Key, const _ValueType& Value);
			void			Insert(const uint32 uIndex, const CItem& Item);
			void			Insert(const uint32 uIndex, const _KeyType& Key, const _ValueType& Value);
			void			Delete(const uint32 uIndex);
			void			Delete(CDictEnumerator<_KeyType, _ValueType>& Enumerator);
			void			DeleteByKey(const _KeyType& Key);
			const _ValueType	RemoveByKey(const _KeyType& Key);

			_ValueType&			Get(const _KeyType&	Key);
			const _ValueType&	Get(const _KeyType& Key) const;

			_KeyType&			GetKey(const uint32 uIndex);
			const _KeyType&		GetKey(const uint32 uIndex) const;
			_ValueType&			GetValue(const uint32 uIndex);
			const _ValueType&	GetValue(const uint32 uIndex) const;

			const bool	Find(const _KeyType& Key, _ValueType& Value) const;

			const bool	Contains(const _KeyType& Key) const;

			const bool	FindKey(const _KeyType& Key, uint32& uOutIndex) const;
			const bool	FindValue(const _ValueType& Value, uint32& uOutIndex) const;

			CEnumerator	GetEnumerator() const;

			void	Set(const CDictionary<_KeyType, _ValueType>& Dictionary);
			void	Set(const ICountable<_KeyType>& KeyList, const ICountable<_ValueType>& ValueList);
			void	Set(const _KeyType* pKeys, const uint32 uKeysLength, const _ValueType* pValues, const uint32 uValuesLength);

			void									Swap(CDictionary<_ValueType, _KeyType>& Dictionary) const;
			const CDictionary<_ValueType, _KeyType>	Swap() const;

			const CDictionary<_KeyType, _ValueType>&	operator=(const CDictionary<_KeyType, _ValueType>& Dictionary);

			const _ValueType&	operator[](const _KeyType& Key) const;
			_ValueType&			operator[](const _KeyType& Key);
		};

		//=================================
		//	CDictionary IMPLEMENTATION
		//=================================

		template<typename _KeyType, typename _ValueType>
		const bool	CDictionary<_KeyType, _ValueType>::GetItemByKey(const _KeyType& Key, CDictEnumerator<_KeyType, _ValueType>& Enumerator) const{
			for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
				if(Enumerator.GetKey() == Key){
					return true;
				}
			}
			return false;
		}

		template<typename _KeyType, typename _ValueType>
		typename CDictionary<_KeyType, _ValueType>::CItem&	CDictionary<_KeyType, _ValueType>::GetItemByKey(const _KeyType& Key) const{
			CDictEnumerator<_KeyType, _ValueType> Enum = this->GetEnumerator();
			if( !this->GetItemByKey( Key, Enum ) ){
				CR_THROW( L"Key not found." );
			}
			return Enum.Get();
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType&	CDictionary<_KeyType, _ValueType>::GetValue(const _KeyType& Key) const{
			if(this->IsEmpty()){
				throw CB::Exception::CZeroLengthException(L"Dictionary",
					L"Cannot retrieve value by key from empty dictionary.", CR_INFO());
			}

			try{
				CEnumerator Enumerator = this->GetEnumerator();
				if(this->GetItemByKey(Key, Enumerator)){
					return Enumerator.GetValue();
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for matching key.", CR_INFO(), Exception);
			}

			throw CB::Exception::CException(
				L"Didn't find key to return dictionary item's value.", CR_INFO());
		}

		template<typename _KeyType, typename _ValueType>
		typename CDictionary<_KeyType, _ValueType>::CItem&	CDictionary<_KeyType, _ValueType>::GetItemByIndex(const uint32 uIndex) const{
			if(this->IsEmpty()){
				throw CB::Exception::CZeroLengthException(L"Dictionary",
					L"Cannot retrieve item from empty dictionary.", CR_INFO());
			}
			if(uIndex >= this->GetLength()){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", CR_INFO());
			}

			try{
				CEnumerator Enumerator = this->GetEnumerator();
				uint32 uIdx = 0;
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
					if(uIdx == uIndex){
						return Enumerator.Get();
					}
					uIdx++;
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for item.", CR_INFO(), Exception);
			}

			throw CB::Exception::CInvalidVarValueException(L"uIndex", CB::String::FromUInt32(uIndex),
				L"Cannot find specified index for dictionary item.", CR_INFO());
		}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CDictionary() : 
			CDictionaryList()
		{}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CDictionary(const CDictionary<_KeyType, _ValueType>& Dictionary){
			try{
				this->Set(Dictionary);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating dictionary copy.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CDictionary(const ICountable<_KeyType>& KeyList, const ICountable<_ValueType>& ValueList){
			try{
				this->Set(KeyList, ValueList);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating dictionary list copy.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CDictionary(const _KeyType* pKeys, const uint32 uKeysLength, const _ValueType* pValues, const uint32 uValuesLength){
			try{
				this->Set(pKeys, uKeysLength, pValues, uValuesLength);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating dictionary raw data copy.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const uint32	CDictionary<_KeyType, _ValueType>::Add(const CItem& Item){
			if(this->Contains(Item.GetKey())){
				throw CB::Exception::CException(
					L"Trying to add duplicate dictionary key.", CR_INFO());
			}
			try{
				return CDictionaryList::Add(Item);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while adding dictionary item.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const uint32	CDictionary<_KeyType, _ValueType>::Add(const _KeyType& Key, const _ValueType& Value){
			return this->Add(CItem(Key, Value));
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Insert(const CItem& Item){
			this->Insert(0, Item);
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Insert(const _KeyType& Key, const _ValueType& Value){
			this->Insert(0, Key, Value);
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Insert(const uint32 uIndex, const CItem& Item){
			try{
				CDictionaryList::Insert(uIndex, Item);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while inserting dictionary item.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Insert(const uint32 uIndex, const _KeyType& Key, const _ValueType& Value){
			this->Insert(uIndex, CItem(Key, Value));
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Delete(const uint32 uIndex){
			try{
				CDictionaryList::Delete(uIndex);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while deleting dictionary item.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Delete(CDictEnumerator<_KeyType, _ValueType>& Enumerator){
			try{
				CDictionaryList::Delete(Enumerator);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while deleting dictionary item by enumerator.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::DeleteByKey(const _KeyType& Key){
			try{
				CEnumerator Enumerator = this->GetEnumerator();
				if(this->GetItemByKey(Key, Enumerator)){
					CDictionaryList::Delete(Enumerator);
				}
				else{
					throw CB::Exception::CException(
						L"Dictionary item not found.", CR_INFO());
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while deleting dictionary item by key value.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType	CDictionary<_KeyType, _ValueType>::RemoveByKey(const _KeyType& Key){
			try{
				typename CEnumerator Enumerator = this->GetEnumerator();
				if(this->GetItemByKey(Key, Enumerator)){
					return CDictionaryList::Remove(Enumerator).GetValue();
				}
				else{
					throw CB::Exception::CException(
						L"Dictionary item not found.", CR_INFO());
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while deleting dictionary item by key value.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType&		CDictionary<_KeyType, _ValueType>::Get(const _KeyType&	Key){
			return this->GetItemByKey(Key).GetValue();
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType&	CDictionary<_KeyType, _ValueType>::Get(const _KeyType& Key) const{
			return this->GetItemByKey(Key).GetValue();
		}

		template<typename _KeyType, typename _ValueType>
		_KeyType&		CDictionary<_KeyType, _ValueType>::GetKey(const uint32 uIndex){
			return this->GetItemByIndex(uIndex).GetKey();
		}

		template<typename _KeyType, typename _ValueType>
		const _KeyType&	CDictionary<_KeyType, _ValueType>::GetKey(const uint32 uIndex) const{
			return this->GetItemByIndex(uIndex).GetKey();
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType&		CDictionary<_KeyType, _ValueType>::GetValue(const uint32 uIndex){
			return this->GetItemByIndex(uIndex).GetValue();
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType&	CDictionary<_KeyType, _ValueType>::GetValue(const uint32 uIndex) const{
			return this->GetItemByIndex(uIndex).GetValue();
		}

		template<typename _KeyType, typename _ValueType>
		const bool	CDictionary<_KeyType, _ValueType>::Find(const _KeyType& Key, _ValueType& Value) const{
			if(this->IsEmpty()){
				return false;
			}
			try{
				CEnumerator	Enumerator = this->GetEnumerator();
				if(this->GetItemByKey(Key, Enumerator)){
					Value = Enumerator.GetValue();
					return true;
				}
				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for key value.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const bool	CDictionary<_KeyType, _ValueType>::Contains(const _KeyType& Key) const{
			if(this->IsEmpty()){
				return false;
			}
			try{
				CEnumerator	Enumerator = this->GetEnumerator();
				return this->GetItemByKey(Key, Enumerator);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
				L"Error while checking for key.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const bool	CDictionary<_KeyType, _ValueType>::FindKey(const _KeyType& Key, uint32& uOutIndex) const{
			if(this->IsEmpty()){
				return false;
			}
			try{
				CEnumerator	Enumerator = this->GetEnumerator();
				uint32 uIndex = 0;
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
					if(Enumerator.GetKey() == Key){
						uOutIndex = uIndex;
						return true;
					}
					uIndex++;
				}
				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for key.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const bool	CDictionary<_KeyType, _ValueType>::FindValue(const _ValueType& Value, uint32& uOutIndex) const{
			if(this->IsEmpty()){
				return false;
			}
			try{
				CEnumerator	Enumerator = this->GetEnumerator();
				uint32 uIndex = 0;
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
					if(Enumerator.GetValue() == Value){
						uOutIndex = uIndex;
						return true;
					}
					uIndex++;
				}
				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for value.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		typename CDictEnumerator<_KeyType, _ValueType>	CDictionary<_KeyType, _ValueType>::GetEnumerator() const{
			return CEnumerator( this, this->m_pFirst );
		} 

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Set(const CDictionary<_KeyType, _ValueType>& Dictionary){
			try{
				CDictionaryList::Set(Dictionary);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping dictionary items.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Set(const ICountable<_KeyType>& KeyList, const ICountable<_ValueType>& ValueList){
			if(KeyList.GetLength() != ValueList.GetLength()){
				throw CB::Exception::CInvalidArgumentException(
					L"KeyList, ValueList", String::FromUInt32(KeyList.GetLength()) + L", " + String::FromUInt32(ValueList.GetLength()),
					L"Cannot create dictionary when key and value lists don't have the same number of items.", 
					CR_INFO());
			}

			try{
				this->Clear();
				for(uint32 uIndex = 0; uIndex < KeyList.GetLength(); uIndex++){
					this->Add(KeyList[uIndex], ValueList[uIndex]);
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping dictionary from key and value lists.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Set(const _KeyType* pKeys, const uint32 uKeysLength, const _ValueType* pValues, const uint32 uValuesLength){
			if(uKeysLength != uValuesLength){
				throw CB::Exception::CInvalidArgumentException(
					L"uKeysLength, uValuesLength", String::FromUInt32(uKeysLength) + L", " + String::FromUInt32(uValuesLength),
					L"Cannot create dictionary when key and value arrays don't have the same number of items.", 
					CR_INFO());
			}
			if(uKeysLength == 0 || uValuesLength == 0){
				this->Clear();
				return;
			}
			if(pKeys == 0){
				throw CB::Exception::CNullArgumentException(L"pKeys",
					L"Cannot create dictionary from null pointer keys array.", CR_INFO());
			}
			if(pValues == 0){
				throw CB::Exception::CNullArgumentException(L"pValues",
					L"Cannot create dictionary from null pointer values array.", CR_INFO());
			}

			try{
				this->Clear();
				for(uint32 uIndex = 0; uIndex < uKeysLength && uIndex < uValuesLength; uIndex++){
					this->Add(pKeys[uIndex], pValues[uIndex]);
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping dictionary from key and value arrays.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Swap(CDictionary<_ValueType, _KeyType>& Dictionary) const{
			try{
				Dictionary.Clear();
				CEnumerator Enumerator = this->GetEnumerator();
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
					Dictionary.Add(Enumerator.GetValue(), Enumerator.GetKey());
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while swaping dictionary.", CR_INFO(), Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const CDictionary<_ValueType, _KeyType>	CDictionary<_KeyType, _ValueType>::Swap() const{
			CDictionary<_ValueType, _KeyType> Dictionary;
			this->Swap(Dictionary);
			return Dictionary;
		}

		template<typename _KeyType, typename _ValueType>
		const CDictionary<_KeyType, _ValueType>&	CDictionary<_KeyType, _ValueType>::operator=(const CDictionary<_KeyType, _ValueType>& Dictionary){
			this->Set(Dictionary);
			return *this;
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType&	CDictionary<_KeyType, _ValueType>::operator[](const _KeyType& Key) const{
			return this->Get(Key);
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType&		CDictionary<_KeyType, _ValueType>::operator[](const _KeyType& Key){
			return this->Get(Key);
		}
	}
}