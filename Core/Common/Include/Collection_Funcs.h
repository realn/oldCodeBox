#pragma once

#include "Types.h"
#include "Collection_Interface.h"
#include "Exception.h"

namespace CB{
	namespace Collection{
		template<typename _Type1, typename _Type2>
		const bool		TryFind(const typename ICountable<_Type1>& Array, const bool (*Compare)(const _Type1& ArrayItem, const _Type2& Comparable), const _Type2& Param, uint32& uOutIndex){
			for(uint32 uIndex = 0; uIndex < Array.GetLength(); uIndex++){
				if(Compare(Array[uIndex], Param)){
					uOutIndex = uIndex;
					return true;
				}
			}
			return false;
		}

		template<typename _Type>
		const bool		TryFind(const typename ICountable<_Type>& Array, const _Type& Item, uint32& uOutIndex){
			for(uint32 uIndex = 0; uIndex < Array.GetLength(); uIndex++){
				if(Array[uIndex] == Item){
					uOutIndex = uIndex;
					return true;
				}
			}
			return false;
		}

		template<typename _Type1, typename _Type2>
		const bool		TryFindLast(const typename ICountable<_Type1>& Array, const bool (*Compare)(const _Type1& ArrayItem, const _Type2& Comparable), const _Type2& Param, uint32& uOutIndex){
			for(uint32 uIndex = Array.GetLength(); uIndex > 0; uIndex--){
				if(Compare(Array[uIndex-1], Param)){
					uOutIndex = uIndex-1;
					return true;
				}
			}
			return false;
		}

		template<typename _Type>
		const bool		TryFindLast(const typename ICountable<_Type>& Array, const _Type& Item, uint32& uOutIndex){
			for(uint32 uIndex = Array.GetLength(); uIndex > 0; uIndex--){
				if(Array[uIndex-1] == Item){
					uOutIndex = uIndex-1;
					return true;
				}
			}
			return false;
		}

		template<typename _Type>
		const uint32	Find(const typename ICountable<_Type>& Array, const _Type& Item){
			uint32 uIndex = 0;
			if(!TryFind<_Type>(Array, Item, uIndex)){
				throw CB::Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return uIndex;
		}

		template<typename _Type1, typename _Type2>
		const uint32	Find(const typename ICountable<_Type1>& Array, const bool (*Compare)(const _Type1& ArrayItem, const _Type2& Comparable), const _Type2& Param){
			uint32 uIndex = 0;
			if(!TryFind(Array, Compare, Param, uIndex)){
				throw Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return uIndex;
		}

		template<typename _Type>
		const uint32	FindLast(const typename ICountable<_Type>& Array, const _Type& Item){
			uint32 uIndex = 0;
			if(!TryFindLast<_Type>(Array, Item, uIndex)){
				throw CB::Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return uIndex;
		}

		template<typename _Type1, typename _Type2>
		const uint32	FindLast(const typename ICountable<_Type1>& Array, const bool (*Compare)(const _Type1& ArrayItem, const _Type2& Comparable), const _Type2& Param){
			uint32 uIndex = 0;
			if(!TryFindLast(Array, Compare, Param, uIndex)){
				throw Exception::CException(
					L"Item not found.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			return uIndex;
		}

		template<typename _Type>
		const bool	TrySearch(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item), _Type& OutItem, uint32& uOutIndex){
			for(uint32 uIndex = 0; uIndex < Array.GetLength(); uIndex++){
				if(Predicate(Array[uIndex])){
					uOutIndex = uIndex;
					OutItem = Array[uIndex];
					return true;
				}
			}
			return false;
		}

		template<typename _Type>
		const bool	TrySearch(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item), _Type& OutItem){
			uint32 uOutIndex = 0;
			return TrySearch(Array, Predicate, OutItem, uOutIndex);
		}

		template<typename _Type>
		const typename _Type	Search(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item), uint32& uOutIndex){
			for(uint32 uIndex = 0; uIndex < Array.GetLength(); uIndex++){
				if(Predicate(Array[uIndex])){
					uOutIndex = uIndex;
					return Array[uIndex];
				}
			}
			return _Type();
		}		

		template<typename _Type>
		const typename _Type Search(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item)){
			uint32 uOutIndex = 0;
			return Search(Array, Predicate, uOutIndex);
		}

		template<typename _Type>
		const bool	TrySearchLast(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item), _Type& OutItem, uint32& uOutIndex){
			for(uint32 uIndex = Array.GetLength(); uIndex > 0; uIndex--){
				if(Predicate(Array[uIndex-1])){
					uOutIndex = uIndex-1;
					OutItem = Array[uIndex-1];
					return true;
				}
			}
			return false;
		}

		template<typename _Type>
		const bool	TrySearchLast(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item), _Type& OutItem){
			uint32 uOutIndex = 0;
			return TrySearchLast(Array, Predicate, OutItem, uOutIndex);
		}

		template<typename _Type>
		const typename _Type	SearchLast(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item), uint32& uOutIndex){
			for(uint32 uIndex = Array.GetLength(); uIndex > 0; uIndex--){
				if(Predicate(Array[uIndex-1])){
					uOutIndex = uIndex-1;
					return Array[uIndex-1];
				}
			}
			return _Type();
		}		

		template<typename _Type>
		const typename _Type SearchLast(const typename ICountable<_Type>& Array, const bool (*Predicate)(const _Type& Item)){
			uint32 uOutIndex = 0;
			return SearchLast(Array, Predicate, uOutIndex);
		}

		template<typename _Type>
		const bool		Contains(const typename ICountable<_Type>& Array, const _Type& Item){
			uint32 uIndex = 0;
			return TryFind<_Type>(Array, Item, uIndex);
		}

		template<typename _Type1, typename _Type2>
		const bool		Contains(const typename ICountable<_Type1>& Array, const bool (*Compare)(const _Type1& ArrayItem, const _Type2& Comparable), const _Type2& Param){
			uint32 uIndex = 0;
			return TryFind<_Type1, _Type2>(Array, Compare, Param, uIndex);
		}
	}
}