#pragma once

#include "Types.h"
#include "Collection_Interface.h"
#include "Memory.h"

namespace CB{
	namespace Memory{
		template<typename _Type>
		void	SetArray(Collection::IPacked<_Type>& Array, const byte iValue){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot set memory of zero length array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			SetArray((void*)Array.GetPointer(), iValue, sizeof(_Type), Array.GetLength());
		}

		template<typename _Type>
		void	SetZeroArray(Collection::IPacked<_Type>& Array){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot set memory of zero length array to zero.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			SetZeroArray((void*)Array.GetPointer(), sizeof(_Type), Array.GetLength());
		}

		template<typename _SourceType, typename _DestinationType>
		void	CopyArray(const Collection::IPacked<_SourceType>& SourceArray, Collection::IPacked<_DestinationType>& DestinationArray){
			if(sizeof(_SourceType) != sizeof(_DestinationType)){
				throw CB::Exception::CException(
					L"Source and Destination types aren't same size.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(SourceArray.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"SourceArray",
					L"Cannot copy from empty array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(SourceArray.GetLength() != DestinationArray.GetLength()){
				throw CB::Exception::CException(
					L"Source and Destination arrays aren't same length.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			CopyArray((void*)SourceArray.GetPointer(), (void*)DestinationArray.GetPointer(), sizeof(_SourceType), SourceArray.GetLength());
		}

		template<typename _Type>
		void	CopyArray(const Collection::IPacked<_Type>& SourceArray, Collection::IPacked<_Type>& DestinationArray){
			if(SourceArray.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"SourceArray",
					L"Cannot copy from empty array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(SourceArray.GetLength() != DestinationArray.GetLength()){
				throw CB::Exception::CException(
					L"Source and Destination arrays aren't same length.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			CopyArray((void*)SourceArray.GetPointer(), (void*)DestinationArray.GetPointer(), sizeof(_Type), SourceArray.GetLength());
		}
	}
}