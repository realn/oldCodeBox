#include "../Include/Memory.h"
#include <memory>

void*	CB::Memory::Alloc(const uint32 uSize){
	return std::malloc(uSize);
}

void*	CB::Memory::AllocArray(const uint32 uSize, const uint32 uNumber){
	return std::malloc(uSize * uNumber);
}

void	CB::Memory::Free(void* pData){
	free(pData);
}

void	CB::Memory::Set(void* pData, const uint8 iValue, const uint32 uSize){
	std::memset(pData, iValue, uSize);
}

void	CB::Memory::SetArray(void* pData, const uint8 iValue, const uint32 uSize, const uint32 uNumber){
	std::memset(pData, iValue, uSize * uNumber);
}

void	CB::Memory::SetZero(void* pData, const uint32 uSize){
	std::memset(pData, 0, uSize);
}

void	CB::Memory::SetZeroArray(void* pData, const uint32 uSize, const uint32 uNumber){
	std::memset(pData, 0, uSize * uNumber);
}

void	CB::Memory::Copy(const void* pSource, void* pDestination, const uint32 uSize){
	std::memcpy(pDestination, pSource, uSize);
}

void	CB::Memory::CopyArray(const void* pSource, void* pDestination, const uint32 uSize, const uint32 uNumber){
	std::memcpy(pDestination, pSource, uSize * uNumber);
}

const int	CB::Memory::Compare(const void* pLeft, const void* pRight, const uint32 uSize){
	return std::memcmp(pLeft, pRight, uSize);
}

const int	CB::Memory::CompareArray(const void* pLeft, const void* pRight, const uint32 uSize, const uint32 uNumber){
	return std::memcmp(pLeft, pRight, uSize * uNumber);
}