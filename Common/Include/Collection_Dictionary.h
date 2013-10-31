#pragma once

#include "Types.h"
#include "Collection_Interface.h"
#include "Collection_LinkList.h"
#include "Exception.h"

namespace CB{
	namespace Collection{
		template<typename _KeyType, typename _ValueType>
		class CPair{
		protected:
			_KeyType	m_Key;
			_ValueType	m_Value;

		public:
			CPair(const _KeyType& Key, const _ValueType& Value);
			CPair(const CPair<_KeyType, _ValueType>& Pair);
			CPair(const CPair<_ValueType, _KeyType>& Pair);
			virtual ~CPair();

			const _KeyType&		GetKey() const;
			const _ValueType&	GetValue() const;

			_KeyType&	GetKey();
			_ValueType&	GetValue();

			void	SetKey(const _KeyType& Key);
			void	SetValue(const _ValueType& Value);
			void	Set(const _KeyType& Key, const _ValueType& Value);

			const CPair<_KeyType, _ValueType>&	operator=(const CPair<_KeyType, _ValueType>& Pair);
		};

		template<typename _KeyType, typename _ValueType>
		class CDictionary : 
			public CLinkList<CPair<_KeyType, _ValueType>>
		{
		public:
			typedef CPair<_KeyType, _ValueType>	CItem;
			typedef CLinkList<CItem> CDictionaryList;

			class CEnumerator : public CDictionaryList::CEnumerator{
			public:
				CEnumerator();
				CEnumerator(const CEnumerator& Enumerator);
				CEnumerator(const CDictionary<_KeyType, _ValueType>& Dictionary);

				_KeyType&	GetKey();
				_ValueType& GetValue();

				const _KeyType&	GetKey() const;
				const _ValueType& GetValue() const;
			};

		protected:
			const bool	GetItemByKey(const _KeyType& Key, typename CEnumerator& Enumerator) const;
			_ValueType&	GetValue(const _KeyType& Key) const;
			CItem&		GetItemByIndex(const uint32 uIndex) const;

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
			void			Delete(const typename CEnumerator& Enumerator);
			void			DeleteByKey(const _KeyType& Key);

			_ValueType&		Get(const _KeyType&	Key);
			const _ValueType&	Get(const _KeyType& Key) const;

			_KeyType&		GetKey(const uint32 uIndex);
			const _KeyType&	GetKey(const uint32 uIndex) const;
			_ValueType&		GetValue(const uint32 uIndex);
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

		//================================
		//	PAIR IMPLEMENTATION
		//================================

		template<typename _KeyType, typename _ValueType>
		CPair<_KeyType, _ValueType>::CPair(const _KeyType& Key, const _ValueType& Value) : 
			m_Key(Key), 
			m_Value(Value)
		{}

		template<typename _KeyType, typename _ValueType>
		CPair<_KeyType, _ValueType>::CPair(const CPair<_KeyType, _ValueType>& Pair) : 
			m_Key(Pair.m_Key), 
			m_Value(Pair.m_Value)
		{}

		template<typename _KeyType, typename _ValueType>
		CPair<_KeyType, _ValueType>::CPair(const CPair<_ValueType, _KeyType>& Pair) : 
			m_Key(Pair.GetValue()), 
			m_Value(Pair.GetKey())
		{}

		template<typename _KeyType, typename _ValueType>
		CPair<_KeyType, _ValueType>::~CPair(){
		}

		template<typename _KeyType, typename _ValueType>
		const _KeyType&		CPair<_KeyType, _ValueType>::GetKey() const{
			return this->m_Key;
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType&	CPair<_KeyType, _ValueType>::GetValue() const{
			return this->m_Value;
		}

		template<typename _KeyType, typename _ValueType>
		_KeyType&	CPair<_KeyType, _ValueType>::GetKey(){
			return this->m_Key;
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType&	CPair<_KeyType, _ValueType>::GetValue(){
			return this->m_Value;
		}

		template<typename _KeyType, typename _ValueType>
		void	CPair<_KeyType, _ValueType>::SetKey(const _KeyType& Key){
			this->m_Key = Key;
		}

		template<typename _KeyType, typename _ValueType>
		void	CPair<_KeyType, _ValueType>::SetValue(const _ValueType& Value){
			this->m_Value = Value;
		}

		template<typename _KeyType, typename _ValueType>
		void	CPair<_KeyType, _ValueType>::Set(const _KeyType& Key, const _ValueType& Value){
			this->m_Key = Key;
			this->m_Value = Value;
		}

		template<typename _KeyType, typename _ValueType>
		const CPair<_KeyType, _ValueType>&	CPair<_KeyType, _ValueType>::operator=(const CPair<_KeyType, _ValueType>& Pair){
			this->Set(Pair.GetKey(), Pair.GetValue());
			return *this;
		}

		//=================================
		//	CDictionary::CEnumerator IMPLEMENTATION
		//=================================
		
		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CEnumerator::CEnumerator() : 
			CDictionaryList::CEnumerator()
		{}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CEnumerator::CEnumerator(const CEnumerator& Enumerator) : 
			CDictionaryList::CEnumerator(Enumerator)
		{}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CEnumerator::CEnumerator(const CDictionary<_KeyType, _ValueType>& Dictionary) : 
			CDictionaryList::CEnumerator(Dictionary)
		{}

		template<typename _KeyType, typename _ValueType>
		_KeyType&	CDictionary<_KeyType, _ValueType>::CEnumerator::GetKey(){
			return this->Get().GetKey();
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType& CDictionary<_KeyType, _ValueType>::CEnumerator::GetValue(){
			return this->Get().GetValue();
		}

		template<typename _KeyType, typename _ValueType>
		const _KeyType&	CDictionary<_KeyType, _ValueType>::CEnumerator::GetKey() const{
			return this->Get().GetKey();
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType& CDictionary<_KeyType, _ValueType>::CEnumerator::GetValue() const{
			return this->Get().GetValue();
		}

		//=================================
		//	CDictionary IMPLEMENTATION
		//=================================

		template<typename _KeyType, typename _ValueType>
		const bool	CDictionary<_KeyType, _ValueType>::GetItemByKey(const _KeyType& Key, typename CEnumerator& Enumerator) const{
			for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
				if(Enumerator.GetKey() == Key){
					return true;
				}
			}
			return false;
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType&	CDictionary<_KeyType, _ValueType>::GetValue(const _KeyType& Key) const{
			if(this->IsEmpty()){
				throw CB::Exception::CZeroLengthException(L"Dictionary",
					L"Cannot retrieve value by key from empty dictionary.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				CEnumerator Enumerator = this->GetEnumerator();
				if(this->GetItemByKey(Key, Enumerator)){
					return Enumerator.GetValue();
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for matching key.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}

			throw CB::Exception::CException(
				L"Didn't find key to return dictionary item's value.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _KeyType, typename _ValueType>
		typename CDictionary<_KeyType, _ValueType>::CItem&	CDictionary<_KeyType, _ValueType>::GetItemByIndex(const uint32 uIndex) const{
			if(this->IsEmpty()){
				throw CB::Exception::CZeroLengthException(L"Dictionary",
					L"Cannot retrieve item from empty dictionary.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(uIndex >= this->GetLength()){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
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
					L"Error while searching for item.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}

			throw CB::Exception::CInvalidVarValueException(L"uIndex", CB::String::FromUInt32(uIndex),
				L"Cannot find specified index for dictionary item.", __FUNCTIONW__, __FILEW__, __LINE__);
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
					L"Error while creating dictionary copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CDictionary(const ICountable<_KeyType>& KeyList, const ICountable<_ValueType>& ValueList){
			try{
				this->Set(KeyList, ValueList);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating dictionary list copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		CDictionary<_KeyType, _ValueType>::CDictionary(const _KeyType* pKeys, const uint32 uKeysLength, const _ValueType* pValues, const uint32 uValuesLength){
			try{
				this->Set(pKeys, uKeysLength, pValues, uValuesLength);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating dictionary raw data copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		const uint32	CDictionary<_KeyType, _ValueType>::Add(const CItem& Item){
			if(this->Contains(Item.GetKey())){
				throw CB::Exception::CException(
					L"Trying to add duplicate dictionary key.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			try{
				return CDictionaryList::Add(Item);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while adding dictionary item.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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
					L"Error while inserting dictionary item.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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
					L"Error while deleting dictionary item.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Delete(const typename CEnumerator& Enumerator){
			try{
				CDictionaryList::Delete(Enumerator);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while deleting dictionary item by enumerator.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::DeleteByKey(const _KeyType& Key){
			try{
				typename CEnumerator Enumerator = this->GetEnumerator();
				if(this->GetItemByKey(Key, Enumerator)){
					CDictionaryList::Delete(Enumerator);
				}
				else{
					throw CB::Exception::CException(
						L"Dictionary item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while deleting dictionary item by key value.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType&		CDictionary<_KeyType, _ValueType>::Get(const _KeyType&	Key){
			return this->GetValue(Key);
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType&	CDictionary<_KeyType, _ValueType>::Get(const _KeyType& Key) const{
			return this->GetValue(Key);
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
					L"Error while searching for key value.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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
				L"Error while checking for key.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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
					L"Error while searching for key.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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
					L"Error while searching for value.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		typename CDictionary<_KeyType, _ValueType>::CEnumerator	CDictionary<_KeyType, _ValueType>::GetEnumerator() const{
			return CEnumerator(*this);
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Set(const CDictionary<_KeyType, _ValueType>& Dictionary){
			try{
				CDictionaryList::Set(Dictionary);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping dictionary items.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Set(const ICountable<_KeyType>& KeyList, const ICountable<_ValueType>& ValueList){
			if(KeyList.GetLength() != ValueList.GetLength()){
				throw CB::Exception::CInvalidArgumentException(
					L"KeyList, ValueList", String::FromUInt32(KeyList.GetLength()) + L", " + String::FromUInt32(ValueList.GetLength()),
					L"Cannot create dictionary when key and value lists don't have the same number of items.", 
					__FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				this->Clear();
				for(uint32 uIndex = 0; uIndex < KeyList.GetLength(); uIndex++){
					this->Add(KeyList[uIndex], ValueList[uIndex]);
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping dictionary from key and value lists.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _KeyType, typename _ValueType>
		void	CDictionary<_KeyType, _ValueType>::Set(const _KeyType* pKeys, const uint32 uKeysLength, const _ValueType* pValues, const uint32 uValuesLength){
			if(uKeysLength != uValuesLength){
				throw CB::Exception::CInvalidArgumentException(
					L"uKeysLength, uValuesLength", String::FromUInt32(uKeysLength) + L", " + String::FromUInt32(uValuesLength),
					L"Cannot create dictionary when key and value arrays don't have the same number of items.", 
					__FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(uKeysLength == 0 || uValuesLength == 0){
				this->Clear();
				return;
			}
			if(pKeys == 0){
				throw CB::Exception::CNullArgumentException(L"pKeys",
					L"Cannot create dictionary from null pointer keys array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(pValues == 0){
				throw CB::Exception::CNullArgumentException(L"pValues",
					L"Cannot create dictionary from null pointer values array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				this->Clear();
				for(uint32 uIndex = 0; uIndex < uKeysLength && uIndex < uValuesLength; uIndex++){
					this->Add(pKeys[uIndex], pValues[uIndex]);
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping dictionary from key and value arrays.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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
					L"Error while swaping dictionary.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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