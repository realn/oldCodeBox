#pragma once

#include "Macros.h"
#include "Types.h"

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
	}
}