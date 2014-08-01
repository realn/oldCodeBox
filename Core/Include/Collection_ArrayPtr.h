#pragma once

#include "Types.h"
#include "Collection_Interface.h"
#include "Exception.h"
#include "Collection_Memory.h"

namespace CB{
	namespace Collection{

		//============================================================
		//	Fixed size array. Pretty much identical in functionality
		//	to standard C++ tables, but with debug index control and
		//	build in size information.
		//============================================================
		template<typename _Type, uint32 _Length>
		class CArrayPtr :
			public ICountable<_Type>,
			public IPacked<_Type>
		{
		protected:
			_Type*	m_pData;

		public:
			CArrayPtr();
			CArrayPtr(const CArrayPtr<_Type, _Length>& Array);
			CArrayPtr(const ICountable<_Type>& Collection);
			CArrayPtr(_Type* const pData);
			~CArrayPtr();

			const uint32	GetLength() const override;

			const _Type&	Get(const uint32 uIndex) const override;
			_Type&			Get(const uint32 uIndex) override;

			void	Set(const CArrayPtr<_Type, _Length>& Array);
			void	Set(const ICountable<_Type>& Collection);
			void	Set(_Type* const pArray);

			void	SetMemory();
			void	SetMemory(const uint8 uValue);

			const _Type&	operator[](const uint32 uIndex) const override;
			_Type&			operator[](const uint32 uIndex) override;

			const CArrayPtr<_Type, _Length>&	operator=(const CArrayPtr<_Type, _Length>& Array);
			const CArrayPtr<_Type, _Length>&	operator=(const ICountable<_Type>& Collection);

			const _Type*	GetPointer() const override;
			_Type*			GetPointer() override;

			const uint32	GetSizeInBytes() const override;

			const bool	IsEmpty() const override;

			template<uint32 _RetLen = _Length>
			const CArrayPtr<_Type, _RetLen>	SubArray(const uint32 uIndex = 0) const;
		};

		//	CLASS IMPLEMENTATION	==================================================

		template<typename _Type, uint32 _Length>
		CArrayPtr<_Type, _Length>::CArrayPtr() :
			m_pData( nullptr )
		{}

		template<typename _Type, uint32 _Length>
		CArrayPtr<_Type, _Length>::CArrayPtr(const CArrayPtr<_Type, _Length>& Array) :
			m_pData( nullptr )
		{
			this->Set(Array);
		}

		template<typename _Type, uint32 _Length>
		CArrayPtr<_Type, _Length>::CArrayPtr(const ICountable<_Type>& Collection) :
			m_pData( nullptr )
		{
			this->Set(Collection);
		}

		template<typename _Type, uint32 _Length>
		CArrayPtr<_Type, _Length>::CArrayPtr(_Type* const pData) :
			m_pData( pData )
		{
		}

		template<typename _Type, uint32 _Length>
		CArrayPtr<_Type, _Length>::~CArrayPtr(){
		}

		template<typename _Type, uint32 _Length>
		const uint32	CArrayPtr<_Type, _Length>::GetLength() const{
			if( m_pData == nullptr )
				return 0;
			return _Length;
		}

		template<typename _Type, uint32 _Length>
		const _Type&	CArrayPtr<_Type, _Length>::Get(const uint32 uIndex) const{
			CR_ASSERT(uIndex < _Length, L"Index out of range.");
			CR_ASSERT(m_pData == nullptr, L"Null data pointer.");
			return this->m_pData[uIndex];
		}

		template<typename _Type, uint32 _Length>
		_Type&	CArrayPtr<_Type, _Length>::Get(const uint32 uIndex){
			CR_ASSERT(uIndex < _Length, L"Index out of range.");
			CR_ASSERT(m_pData == nullptr, L"Null data pointer.");
			return this->m_pData[uIndex];
		}

		template<typename _Type, uint32 _Length>
		void	CArrayPtr<_Type, _Length>::Set(const CArrayPtr<_Type, _Length>& Array){
			m_pData = Array.m_pData;
		}

		template<typename _Type, uint32 _Length>
		void CArrayPtr<_Type, _Length>::Set(const ICountable<_Type>& Collection){
			CR_ASSERT(m_pData == nullptr, L"Null data pointer.");
			for(uint32 uIndex = 0; uIndex < Min(_Length, Collection.GetLength()); uIndex){
				this->m_pData[uIndex] = Collection[uIndex];
			}
		}

		template<typename _Type, uint32 _Length>
		void CArrayPtr<_Type, _Length>::Set(_Type* const pData){
			this->m_pData = pData;
		}

		template<typename _Type, uint32 _Length>
		const _Type&	CArrayPtr<_Type, _Length>::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		template<typename _Type, uint32 _Length>
		_Type&	CArrayPtr<_Type, _Length>::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		template<typename _Type, uint32 _Length>
		const CArrayPtr<_Type, _Length>&	CArrayPtr<_Type, _Length>::operator=(const CArrayPtr<_Type, _Length>& Array){
			this->Set(Array);
			return *this;
		}

		template<typename _Type, uint32 _Length>
		const CArrayPtr<_Type, _Length>&	CArrayPtr<_Type, _Length>::operator=(const ICountable<_Type>& Collection){
			this->Set(Collection);
			return *this;
		}

		template<typename _Type, uint32 _Length>
		void CArrayPtr<_Type, _Length>::SetMemory(){
			Memory::SetZeroArray(this->m_pData, _Length);
		}

		template<typename _Type, uint32 _Length>
		void CArrayPtr<_Type, _Length>::SetMemory(const uint8 uValue){
			Memory::SetArray(this->m_pData, uValue, _Length);
		}

		template<typename _Type, uint32 _Length>
		const _Type*	CArrayPtr<_Type, _Length>::GetPointer() const{
			return this->m_pData;
		}

		template<typename _Type, uint32 _Length>
		_Type*			CArrayPtr<_Type, _Length>::GetPointer(){
			return this->m_pData;
		}

		template<typename _Type, uint32 _Length>
		const uint32	CArrayPtr<_Type, _Length>::GetSizeInBytes() const{
			return _Length * sizeof(_Type);
		}

		template<typename _Type, uint32 _Length>
		const bool		CArrayPtr<_Type, _Length>::IsEmpty() const{
			return m_pData == nullptr;
		}

		template<uint32 _RetLen>
		template<typename _Type, uint32 _Length>
		const CArrayPtr<_Type, _RetLen> CArrayPtr<_Type, _Length>::SubArray(const uint32 uIndex) const{
			return CArrayPtr<_Type, _RetLen>( m_pData + uIndex );
		}

		//	END OF CLASS IMPLEMENTATION	====================================================
	}
}