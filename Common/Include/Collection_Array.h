#pragma once

#include "Types.h"
#include "Collection_Interface.h"
#include "Exception.h"
#include "Memory.h"
#include "Collection_Memory.h"

namespace CB{
	namespace Collection{

		//============================================================
		//	Fixed size array. Pretty much identical in functionality
		//	to standard C++ tables, but with debug index control and
		//	build in size information.
		//============================================================
		template<typename _Type, uint32 _Length>
		class CArray :
			public ICountable<_Type>,
			public IPacked<_Type>
		{
		protected:
			_Type	m_pData[_Length];

		public:
			CArray();
			CArray(const CArray<_Type, _Length>& Array);
			CArray(const ICountable<_Type>& Collection);
			~CArray();

			const uint32	GetLength() const override;

			const _Type&	Get(const uint32 uIndex) const override;
			_Type&			Get(const uint32 uIndex) override;

			void	Set(const CArray<_Type, _Length>& Array);
			void	Set(const ICountable<_Type>& Collection);

			void	SetMemory();
			void	SetMemory(const uint8 uValue);

			const _Type&	operator[](const uint32 uIndex) const override;
			_Type&			operator[](const uint32 uIndex) override;

			const CArray<_Type, _Length>&	operator=(const CArray<_Type, _Length>& Array);
			const CArray<_Type, _Length>&	operator=(const ICountable<_Type>& Collection);

			const _Type*	GetPointer() const override;
			_Type*			GetPointer() override;

			const uint32	GetSizeInBytes() const override;

			const bool	IsEmpty() const override;
		};

		//	CLASS IMPLEMENTATION	==================================================

		template<typename _Type, uint32 _Length>
		CArray<_Type, _Length>::CArray(){}

		template<typename _Type, uint32 _Length>
		CArray<_Type, _Length>::CArray(const CArray<_Type, _Length>& Array){
			this->Set(Array);
		}

		template<typename _Type, uint32 _Length>
		CArray<_Type, _Length>::CArray(const ICountable<_Type>& Collection){
			this->Set(Collection);
		}

		template<typename _Type, uint32 _Length>
		CArray<_Type, _Length>::~CArray(){
		}

		template<typename _Type, uint32 _Length>
		const uint32	CArray<_Type, _Length>::GetLength() const{
			return _Length;
		}

		template<typename _Type, uint32 _Length>
		const _Type&	CArray<_Type, _Length>::Get(const uint32 uIndex) const{
			CR_ASSERT(uIndex < _Length, L"Index out of range.");
			return this->m_pData[uIndex];
		}

		template<typename _Type, uint32 _Length>
		_Type&	CArray<_Type, _Length>::Get(const uint32 uIndex){
			CR_ASSERT(uIndex < _Length, L"Index out of range.");
			return this->m_pData[uIndex];
		}

		template<typename _Type, uint32 _Length>
		void	CArray<_Type, _Length>::Set(const CArray<_Type, _Length>& Array){
			for(uint32 uIndex = 0; uIndex < _Length; uIndex++){
				this->m_pData[uIndex] = Array.m_pData[uIndex];
			}
		}

		template<typename _Type, uint32 _Length>
		void CArray<_Type, _Length>::Set(const ICountable<_Type>& Collection){
			for(uint32 uIndex = 0; uIndex < Min(_Length, Collection.GetLength()); uIndex){
				this->m_pData[uIndex] = Collection[uIndex];
			}
		}

		template<typename _Type, uint32 _Length>
		const _Type&	CArray<_Type, _Length>::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		template<typename _Type, uint32 _Length>
		_Type&	CArray<_Type, _Length>::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		template<typename _Type, uint32 _Length>
		const CArray<_Type, _Length>&	CArray<_Type, _Length>::operator=(const CArray<_Type, _Length>& Array){
			this->Set(Array);
			return *this;
		}

		template<typename _Type, uint32 _Length>
		const CArray<_Type, _Length>&	CArray<_Type, _Length>::operator=(const ICountable<_Type>& Collection){
			this->Set(Collection);
			return *this;
		}

		template<typename _Type, uint32 _Length>
		void CArray<_Type, _Length>::SetMemory(){
			Memory::SetZeroArray(this->m_pData, _Length);
		}

		template<typename _Type, uint32 _Length>
		void CArray<_Type, _Length>::SetMemory(const uint8 uValue){
			Memory::SetArray(this->m_pData, uValue, _Length);
		}

		template<typename _Type, uint32 _Length>
		const _Type*	CArray<_Type, _Length>::GetPointer() const{
			return this->m_pData;
		}

		template<typename _Type, uint32 _Length>
		_Type*			CArray<_Type, _Length>::GetPointer(){
			return this->m_pData;
		}

		template<typename _Type, uint32 _Length>
		const uint32	CArray<_Type, _Length>::GetSizeInBytes() const{
			return _Length * sizeof(_Type);
		}

		template<typename _Type, uint32 _Length>
		const bool		CArray<_Type, _Length>::IsEmpty() const{
			return false;
		}

		//	END OF CLASS IMPLEMENTATION	====================================================
	}
}