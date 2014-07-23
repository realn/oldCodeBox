#pragma once

#include "Types.h"
#include "Exception.h"

namespace CB{
	namespace Memory{
		//===============
		//	Memory manipulation functions externs.
		//===============
		extern COMMON_API void*		Alloc(const uint32 uSize);
		extern COMMON_API void*		AllocArray(const uint32 uSize, const uint32 uNumber);
		extern COMMON_API void		Free(void* pData);
		extern COMMON_API void		Set(void* pData, const uint8 iValue, const uint32 uSize);
		extern COMMON_API void		SetArray(void* pData, const uint8 iValue, const uint32 uSize, const uint32 uNumber);
		extern COMMON_API void		SetZero(void* pData, const uint32 uSize);
		extern COMMON_API void		SetZeroArray(void* pData, const uint32 uSize, const uint32 uNumber);
		extern COMMON_API void		Copy(const void* pSource, void* pDestination, const uint32 uSize);
		extern COMMON_API void		CopyArray(const void* pSource, void* pDestination, const uint32 uSize, const uint32 uNumber);
		extern COMMON_API const int	Compare(const void* pLeft, const void* pRight, const uint32 uSize);
		extern COMMON_API const int	CompareArray(const void* pLeft, const void* pRight, const uint32 uSize, const uint32 uNumber);

		/// <summary>
		/// Allocates memory for specified one instance of type (no constructor).
		/// </summary>
		/// <returns>
		/// Raw memory pointer.
		/// </returns>
		template<typename _Type>
		inline _Type*	Alloc(){
			return reinterpret_cast<_Type*>(Alloc(sizeof(_Type)));
		}

		/// <summary>
		/// Allocates memory for specified instances of types in an flat array (no constructor).
		/// </summary>
		/// <param name="uNumber">Number of instances.</param>
		/// <returns>
		/// Raw memory pointer to an array.
		/// </returns>
		template<typename _Type>
		inline _Type*	AllocArray(const uint32 uNumber){
			return reinterpret_cast<_Type*>(AllocArray(sizeof(_Type), uNumber));
		}

		/// <summary>
		/// Set specified object instance memory data to specified value.
		/// </summary>
		/// <param name="Data">Data to be set.</param>
		/// <param name="iValue">Value to set memory to.</param>
		template<typename _Type>
		inline void	Set(_Type& Data, const uint8 iValue){
			Set((void*)&Data, iValue, sizeof(_Type));
		}

		/// <summary>
		/// Sets spcified array of elements memory to specified value.
		/// </summary>
		/// <param name="pData">Data array memory pointer.</param>
		/// <param name="iValue">Value to set memory to.</param>
		/// <param name="uNumber">Number of elements in array.</param>
		template<typename _Type>
		inline void	SetArray(_Type* pData, const uint8 iValue, const uint32 uNumber){
			SetArray((void*)pData, iValue, sizeof(_Type), uNumber);
		}

		/// <summary>
		/// Sets memory of specified object to zero.
		/// </summary>
		/// <param name="Data">Instance of object.</param>
		template<typename _Type>
		inline void	SetZero(_Type& Data){
			SetZero((void*)&Data, sizeof(_Type));
		}

		/// <summary>
		/// Sets specified array of elements memory to zero.
		/// </summary>
		/// <param name="pData">Array of elements.</param>
		/// <param name="uNumber">Number of elements in array.</param>
		template<typename _Type>
		inline void	SetZeroArray(_Type* pData, const uint32 uNumber){
			SetZeroArray((void*)pData, sizeof(_Type), uNumber);
		}

		/// <summary>
		/// Copies data from specified source object to destination object.
		/// </summary>
		/// <remarks>Sizes of specified objects must be equal, or there will be thrown an exception od debug builds.</remarks>
		/// <param name="Source">Source object to be copied from.</param>
		/// <param name="Destination">Destination object to be copied to.</param>
		template<typename _SourceType, typename _DestinationType>
		inline void	Copy(const _SourceType& Source, _DestinationType& Destination){
			CR_ASSERT(sizeof(_SourceType) == sizeof(_DestinationType), L"Source and Destination type don't have same sizes.");

			Copy((void*)&Source, (void*)&Destination, sizeof(_SourceType));
		}

		/// <summary>
		/// Copies data from array of elements source to destitnation object.
		/// </summary>
		///	<remarks>Sizes of object types must be equal, or there will be thrown an exception on debug builds.</remarks>
		/// <param name="pSource">Source array to be copied from.</param>
		/// <param name="pDestination">Destination array to be copied to.</param>
		/// <param name="uNumber">Number of elements in arrays.</param>
		template<typename _SourceType, typename _DestinationType>
		inline void	CopyArray(const _SourceType* pSource, _DestinationType* pDestination, const uint32 uNumber){
			CR_ASSERT(sizeof(_SourceType) == sizeof(_DestinationType), L"Source and Destination type don't have same sizes.");

			CopyArray((void*)pSource, (void*)pDestination, sizeof(_SourceType), uNumber);
		}

		/// <summary>
		/// Copies data from array of elements to destination array.
		/// </summary>
		/// <param name="pSource">Source array of elements.</param>
		/// <param name="pDestination">Destination array of elements.</param>
		/// <param name="uNumber">The authentication number.</param>
		template<typename _Type>
		inline void	CopyArray(const _Type* pSource, _Type* pDestination, const uint32 uNumber){
			CopyArray((void*)pSource, (void*)pDestination, sizeof(_Type), uNumber);
		}

		template<typename _LeftType, typename _RightType>
		inline const int	Compare(const _LeftType& Left, const _RightType& Right){
			CR_ASSERT(sizeof(_LeftType) != sizeof(_RightType), L"Left and Right type don't have same sizes.");

			return Compare((void*)&Left, (void*)&Right, sizeof(_LeftType));
		}

		template<typename _Type>
		inline const int	Compare(const _Type& Left, const _Type& Right){
			return Compare((void*)&Left, (void*)&Right, sizeof(_Type));
		}

		template<typename _LeftType, typename _RightType>
		inline const int	CompareArray(const _LeftType* pLeft, const _RightType* pRight, const uint32 uNumber){
			CR_ASSERT(sizeof(_LeftType) != sizeof(_RightType), L"Left and Right type don't have same sizes.");

			CompareArray((void*)pLeft, (void*)pRight, sizeof(_LeftType), uNumber);
		}

		template<typename _Type>
		inline const int	CompareArray(const _Type* pLeft, const _Type* pRight, const uint32 uNumber){
			return CompareArray((void*)pLeft, (void*)pRight, sizeof(_Type), uNumber);
		}
	}
}