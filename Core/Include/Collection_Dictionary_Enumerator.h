#pragma once

#include "Macros.h"
#include "Types.h"
#include "Collection_LinkList_Enumerator.h"
#include "Collection_Pair.h"

namespace CB{
	namespace Collection{
		template<typename _KeyType, typename _ValueType> class CDictionary;
		template<typename _Type> class CNode;

		template<typename _KeyType, typename _ValueType>
		class CDictEnumerator : 
			public CListEnumerator<CPair<_KeyType, _ValueType>>
		{
			friend CDictionary<_KeyType, _ValueType>;
		protected:
			CDictEnumerator(const CDictionary<_KeyType, _ValueType>* dict, const CNode<CPair<_KeyType, _ValueType>>* pNode );

		public:
			CDictEnumerator(const CDictEnumerator<_KeyType, _ValueType>& Enumerator);

			_KeyType&	GetKey();
			_ValueType& GetValue();

			const _KeyType&	GetKey() const;
			const _ValueType& GetValue() const;
		};


		//=================================
		//	CDictionary::CListEnumerator IMPLEMENTATION
		//=================================
		
		template<typename _KeyType, typename _ValueType>
		CDictEnumerator<_KeyType, _ValueType>::CDictEnumerator( const CDictionary<_KeyType, _ValueType>* dict, const CNode<CPair<_KeyType, _ValueType>>* pNode) : 
			CListEnumerator( dict, pNode )
		{}

		template<typename _KeyType, typename _ValueType>
		CDictEnumerator<_KeyType, _ValueType>::CDictEnumerator(const CDictEnumerator<_KeyType, _ValueType>& Enumerator) : 
			CListEnumerator( Enumerator )
		{}

		template<typename _KeyType, typename _ValueType>
		_KeyType&	CDictEnumerator<_KeyType, _ValueType>::GetKey(){
			return this->Get().GetKey();
		}

		template<typename _KeyType, typename _ValueType>
		_ValueType& CDictEnumerator<_KeyType, _ValueType>::GetValue(){
			return this->Get().GetValue();
		}

		template<typename _KeyType, typename _ValueType>
		const _KeyType&	CDictEnumerator<_KeyType, _ValueType>::GetKey() const{
			return this->Get().GetKey();
		}

		template<typename _KeyType, typename _ValueType>
		const _ValueType& CDictEnumerator<_KeyType, _ValueType>::GetValue() const{
			return this->Get().GetValue();
		}
	}
}