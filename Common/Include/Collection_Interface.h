#pragma once

#include "Types.h"

namespace CB{
	namespace Collection{
		template<typename _Type>
		class ICountable{
		public:
			virtual ~ICountable(){}

			virtual const uint32	GetLength() const = 0;

			virtual const _Type&	Get(const uint32 uIndex) const = 0;
			virtual _Type&			Get(const uint32 uIndex) = 0;

			virtual const _Type&	operator[](const uint32 uIndex) const = 0;
			virtual _Type&			operator[](const uint32 uIndex) = 0;

			virtual const bool		IsEmpty() const = 0;
		};

		template<typename _Type>
		class IPacked{
		public:
			virtual ~IPacked(){}

			virtual const uint32	GetLength() const = 0;

			virtual const _Type&	Get(const uint32 uIndex) const = 0;
			virtual _Type&			Get(const uint32 uIndex) = 0;

			virtual const _Type&	operator[](const uint32 uIndex) const = 0;
			virtual _Type&			operator[](const uint32 uIndex) = 0;

			virtual const _Type*	GetPointer() const = 0;
			virtual _Type*			GetPointer() = 0;

			virtual const uint32	GetSizeInBytes() const = 0;

			virtual const bool		IsEmpty() const = 0;
		};
	}
}