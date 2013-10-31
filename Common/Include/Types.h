#pragma once

typedef signed	char		int8;
typedef signed	short		int16;
typedef signed int			int32;
typedef signed	__int64		int64;

typedef	unsigned char		uint8;
typedef	unsigned short		uint16;
typedef	unsigned int		uint32;
typedef	unsigned __int64	uint64;

typedef float	float32;
typedef double	float64;

typedef unsigned char	byte;
typedef wchar_t			wchar;

template<typename _Type>
inline static _Type Min(_Type A, _Type B){
	return A < B ? A : B;
}

template<typename _Type>
inline static _Type Max(_Type A, _Type B){
	return A > B ? A : B;
}

template<typename _Type>
inline static const bool ContainsBit(_Type uCheck, _Type uValue){
	return (uCheck & uValue) > 0;
}