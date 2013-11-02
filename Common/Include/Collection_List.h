#pragma once

#include "Macros.h"
#include "Types.h"
#include "Exception.h"
#include "Collection_Interface.h"
#include "Memory.h"
#include "Collection_Memory.h"

#include <new>

#define CR_LIST_GRANULITY 20

namespace CB{
	namespace Collection{

		//====================================================================
		//	An dynamic table, packed in memory, with reserving functionality.
		//====================================================================
		template<typename _Type>
		class CList : 
			public ICountable<_Type>,
			public IPacked<_Type>
		{
		protected:
			_Type*	m_pList;
			uint32	m_uLength;
			uint32	m_uReserved;

			_Type&	GetValue(const uint32 uIndex) const;
			_Type&	GetFirst() const;
			_Type&	GetLast() const;

		public:
			CList();
			CList(const CList<_Type>& Array);
			CList(const ICountable<_Type>& List);
			CList(const uint32 uLength);
			CList(const uint32 uLength, const _Type* pData);
			~CList();

			void	Reserve(const uint32 uLength);
			void	Resize(const uint32 uLength);
			void	Clear();
			void	Free();

			const uint32	GetLength() const;
			const bool		IsEmpty() const;

			const uint32	Add(const _Type& Item);
			void	Insert(const uint32 uIndex, const _Type& Item);
			const _Type	Remove(const uint32 uIndex);
			const _Type	Remove();

			void	Set(const uint32 uLength, const _Type* pData);
			void	Set(const CList<_Type>& Array);
			void	Set(const ICountable<_Type>& Array);

			const _Type&	Get(const uint32 uIndex) const;
			_Type&			Get(const uint32 uIndex);

			_Type&	First();
			const _Type&	First() const;
			_Type&	Last();
			const _Type&	Last() const;

			void				Sub(typename CList<_Type>& Array, const uint32 uIndex) const;
			void				Sub(typename CList<_Type>& Array, const uint32 uIndex, const uint32 uRange) const;
			const CList<_Type>	Sub(const uint32 uIndex) const;
			const CList<_Type>	Sub(const uint32 uIndex, const uint32 uRange) const;
			void				SubIndexed(CList<_Type>& Array, const uint32 uStartIndex, const uint32 uEndIndex) const;
			const CList<_Type>	SubIndexed(const uint32 uStartIndex, const uint32 uEndIndex) const;

			CList<_Type>&	operator=(const CList<_Type>& Array);
			CList<_Type>&	operator=(const ICountable<_Type>& List);

			const _Type&	operator[](const uint32 uIndex) const;
			_Type&			operator[](const uint32 uIndex);

			const _Type*	GetPointer() const override;
			_Type*			GetPointer() override;

			const uint32	GetSizeInBytes() const override;
		};
		
		//	CLASS IMPLEMENTATION	====================================================

		template<typename _Type>
		_Type&	CList<_Type>::GetValue(const uint32 uIndex) const{
			if(uIndex >= this->m_uLength){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex), 
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return this->m_pList[uIndex];
		}

		template<typename _Type>
		_Type&	CList<_Type>::GetFirst() const{
			if(this->m_pList){
				return *this->m_pList;
			}
			throw CB::Exception::CNullPointerException(L"m_pList",
				L"No first item in array.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _Type>
		_Type&	CList<_Type>::GetLast() const{
			if(this->m_pList){
				return *(this->m_pList + this->m_uLength - 1);
			}
			throw CB::Exception::CNullPointerException(L"m_pList",
				L"No last item in array.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		template<typename _Type>
		CList<_Type>::CList() : 
			m_pList(0), 
			m_uLength(0),
			m_uReserved(0)
		{}

		template<typename _Type>
		CList<_Type>::CList(const CList<_Type>& Array) : 
			m_pList(0), 
			m_uLength(0)
		{
			try{
				this->Set(Array);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while making array copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		CList<_Type>::CList(const ICountable<_Type>& List) : 
			m_pList(0), 
			m_uLength(0)
		{
			try{
				this->Set(List);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while making array copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		CList<_Type>::CList(const uint32 uLength) : 
			m_pList(0), 
			m_uLength(0),
			m_uReserved(0)
		{
			try{
				this->Resize(uLength);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while initializng array with size.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		CList<_Type>::CList(const uint32 uLength, const _Type* pData) : 
			m_pList(0), 
			m_uLength(0),
			m_uReserved(0)
		{
			try{
				this->Set(uLength, pData);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating raw data array copy.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		CList<_Type>::~CList(){
			this->Free();
		}

		template<typename _Type>
		void	CList<_Type>::Reserve(const uint32 uLength){
			if(uLength == this->m_uReserved)
				return;

			_Type* pList = Memory::AllocArray<_Type>(uLength);

			uint32 uCopyLength = Min(this->m_uLength, uLength);
			if(uCopyLength > 0){
				Memory::CopyArray<_Type>(this->m_pList, pList, uCopyLength);
			}
			if(uCopyLength < this->m_uLength){
				for(uint32 uIndex = uCopyLength; uIndex < this->m_uLength; uIndex++){
					this->m_pList[uIndex].~_Type();
				}
			}

			Memory::Free(this->m_pList);
			this->m_uLength = uCopyLength;
			this->m_uReserved = uLength;
			this->m_pList = pList;
		}

#pragma warning(disable : 4345)
		template<typename _Type>
		void	CList<_Type>::Resize(const uint32 uLength){
			if(uLength == 0){
				throw CB::Exception::CZeroLengthArgumentException(L"uLength",
					L"Cannot create array with no length.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(this->m_uLength == uLength){
				return;
			}

			if(uLength > this->m_uReserved){
				this->Reserve(((uLength / CR_LIST_GRANULITY) + 1) * CR_LIST_GRANULITY);
			}

			for(uint32 uIndex = this->m_uLength; uIndex < uLength; uIndex++){
				new (&this->m_pList[uIndex]) _Type();
			}
			this->m_uLength = uLength;
		}

		template<typename _Type>
		void	CList<_Type>::Clear(){
			if(this->m_pList){
				for(uint32 uIndex = 0; uIndex < this->m_uLength; uIndex++){
					this->m_pList[uIndex].~_Type();
				}
				this->m_uLength = 0;
			}
		}

		template<typename _Type>
		void	CList<_Type>::Free(){
			this->Clear();
			if(this->m_pList){
				Memory::Free(this->m_pList);
				this->m_uReserved = 0;
			}
		}

		template<typename _Type>
		const uint32	CList<_Type>::GetLength() const{
			return this->m_uLength;
		}

		template<typename _Type>
		const bool	CList<_Type>::IsEmpty() const{
			return this->m_pList == 0 || this->m_uLength == 0;
		}

		template<typename _Type>
		const uint32	CList<_Type>::Add(const _Type& Item){
			if(this->m_uLength + 1 > this->m_uReserved){
				this->Reserve((((this->m_uLength + 1) / CR_LIST_GRANULITY) + 1) * CR_LIST_GRANULITY);
			}
			new (&this->m_pList[this->m_uLength]) _Type(Item);
			this->m_uLength++;
			return this->m_uLength - 1;
		}

		template<typename _Type>
		void	CList<_Type>::Insert(const uint32 uIndex, const _Type& Item){
			CR_ASSERT(uIndex <= this->m_uLength, L"Index out of range.");

			if(this->m_uLength == uIndex){
				this->Add(Item);
				return;
			}

			//TODO:	Implement an "Memory pointer" to release memory on scope-out.
			_Type* pList = this->m_pList;
			uint32 uLength = this->m_uLength;

			this->m_pList = 0;
			this->m_uLength = 0;
			this->m_uReserved = 0;

			this->Reserve((((uLength + 1)  / CR_LIST_GRANULITY) + 1) * CR_LIST_GRANULITY);

			if(uIndex > 0){
				Memory::CopyArray(pList, this->m_pList, uIndex);
			}
			new (&this->m_pList[uIndex]) _Type(Item);
			if(uLength - uIndex - 1 > 0){
				Memory::CopyArray(pList + uIndex, this->m_pList + uIndex + 1, uLength - uIndex);
			}

			this->m_uLength = uLength + 1;
			Memory::Free(pList);	//Troublesome to remember.
		}

		template<typename _Type>
		const _Type	CList<_Type>::Remove(){
			CR_ASSERT(!this->IsEmpty(), L"Cannot remove item from empty array.");

			this->m_uLength--;
			_Type temp(this->m_pList[this->m_uLength]);
			this->m_pList[this->m_uLength].~_Type();
			return temp;
		}

		template<typename _Type>
		const _Type	CList<_Type>::Remove(const uint32 uIndex){
			CR_ASSERT(uIndex < this->m_uLength, L"Index out of range.");

			_Type* pList = this->m_pList;
			uint32 uLength = this->m_uLength;

			this->m_pList = 0;
			this->m_uLength = 0;
			this->m_uReserved = 0;

			this->Reserve((((uLength - 1) / CR_LIST_GRANULITY) + 1 ) * CR_LIST_GRANULITY);

			_Type temp(pList[uIndex]);

			if(uIndex > 0){
				Memory::CopyArray<_Type>(pList, this->m_pList, uIndex);
			}
			pList[uIndex].~_Type();
			if(uLength - uIndex - 1 > 0){
				Memory::CopyArray(pList + uIndex + 1, this->m_pList + uIndex, uLength - uIndex - 1);
			}
			this->m_uLength = uLength - 1;

			return temp;
		}

		template<typename _Type>
		void	CList<_Type>::Set(const uint32 uLength, const _Type* pData){
			if(uLength == 0){
				this->Clear();
				return;
			}
			if(pData == 0){
				throw CB::Exception::CNullArgumentException(L"pData", 
					L"Got null pointer as data.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			try{
				this->Clear();
				this->Reserve(uLength);

				for(uint32 uIndex = 0; uIndex < uLength; uIndex++){
					new (&this->m_pList[uIndex]) _Type(pData[uIndex]);
				}
				this->m_uLength = uLength;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping data from array.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		void	CList<_Type>::Set(const CList<_Type>& Array){
			this->Set(Array.m_uLength, Array.m_pList);
		}

		template<typename _Type>
		void	CList<_Type>::Set(const ICountable<_Type>& Array){
			if(Array.GetLength() == 0){
				this->Clear();
				return;
			}
			try{
				this->Clear();
				this->Reserve(Array.GetLength());

				for(uint32 uIndex = 0; uIndex < Array.GetLength(); uIndex++){
					new (&this->m_pList[uIndex]) _Type(Array[uIndex]);
				}
				this->m_uLength = Array.GetLength();
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while coping data from array.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		const _Type&	CList<_Type>::Get(const uint32 uIndex) const{
			return this->GetValue(uIndex);
		}

		template<typename _Type>
		_Type&	CList<_Type>::Get(const uint32 uIndex){
			return this->GetValue(uIndex);
		}

		template<typename _Type>
		_Type&	CList<_Type>::First(){
			return this->GetFirst();
		}

		template<typename _Type>
		const _Type&	CList<_Type>::First() const{
			return this->GetFirst();
		}

		template<typename _Type>
		_Type&	CList<_Type>::Last(){
			return this->GetLast();
		}

		template<typename _Type>
		const _Type&	CList<_Type>::Last() const{
			return this->GetLast();
		}

		template<typename _Type>
		void	CList<_Type>::Sub(typename CList<_Type>& Array, const uint32 uIndex) const{
			this->Sub(Array, uIndex, this->m_uLength - uIndex);
		}

		template<typename _Type>
		void	CList<_Type>::Sub(typename CList<_Type>& Array, const uint32 uIndex, const uint32 uRange) const{
			if(uIndex >= this->m_uLength){
				throw CB::Exception::CInvalidArgumentException(L"uIndex", CB::String::FromUInt32(uIndex),
					L"Index out of range.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(uIndex + uRange > this->m_uLength){
				throw CB::Exception::CInvalidArgumentException(L"uRange", CB::String::FromUInt32(uRange),
					L"Range too long.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				Array.Resize(uRange);

				for(uint32 uArrayIndex = 0; uArrayIndex < uRange; uArrayIndex++){
					Array[uArrayIndex] = this->m_pList[uIndex + uArrayIndex];
				}
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while creating sub array.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		template<typename _Type>
		const CList<_Type>	CList<_Type>::Sub(const uint32 uIndex) const{
			return this->Sub(uIndex, this->m_uLength - uIndex);
		}

		template<typename _Type>
		const CList<_Type>	CList<_Type>::Sub(const uint32 uIndex, const uint32 uRange) const{
			CList<_Type> Array;
			this->Sub(Array, uIndex, uRange);
			return Array;
		}

		template<typename _Type>
		void	CList<_Type>::SubIndexed(CList<_Type>& Array, const uint32 uStartIndex, const uint32 uEndIndex) const{
			this->Sub(Array, uStartIndex, uEndIndex - uStartIndex);
		}

		template<typename _Type>
		const CList<_Type>	CList<_Type>::SubIndexed(const uint32 uStartIndex, const uint32 uEndIndex) const{
			return this->Sub(uStartIndex, uEndIndex - uStartIndex);
		}

		template<typename _Type>
		CList<_Type>&	CList<_Type>::operator=(const CList<_Type>& Array){
			this->Set(Array);
			return *this;
		}

		template<typename _Type>
		CList<_Type>&	CList<_Type>::operator=(const ICountable<_Type>& List){
			this->Set(List);
			return *this;
		}

		template<typename _Type>
		const _Type&	CList<_Type>::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		template<typename _Type>
		_Type&	CList<_Type>::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		template<typename _Type>
		const _Type*	CList<_Type>::GetPointer() const{
			if(this->m_uLength == 0)
				return 0;
			return this->m_pList;
		}

		template<typename _Type>
		_Type*			CList<_Type>::GetPointer(){
			if(this->m_uLength == 0)
				return 0;
			return this->m_pList;
		}

		template<typename _Type>
		const uint32	CList<_Type>::GetSizeInBytes() const{
			return this->m_uLength * sizeof(_Type);
		}

		//	END OF CLASS IMPLEMENTATION	=====================================================
	}
}