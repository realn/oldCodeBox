#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	namespace Math{
		extern COMMON_API const bool	IsNearZero(const float32 fValue);
		extern COMMON_API const bool	IsNearZero(const float32 fValue, const float32 fTolerance);
		extern COMMON_API const bool	IsNearEqual(const float32 fValue1, const float32 fValue2);
		extern COMMON_API const bool	IsNearEqual(const float32 fValue1, const float32 fValue2, const float32 fTolerance);

		extern COMMON_API const float32	Power2(const float32 fValue);
		extern COMMON_API const float32 Power(const float32 fValue, const float32 fMag);
		extern COMMON_API const float32	SqRoot(const float32 fValue);

		extern COMMON_API const float32	Min(const float32 a, const float32 b);
		extern COMMON_API const float32	Min(const float32 a, const float32 b, const float32 c);
		extern COMMON_API const float32	Min(const float32 a, const float32 b, const float32 c, const float32 d);
		extern COMMON_API const float32	Min(const float32 a, const float32 b, const float32 c, const float32 d, const float32 e);

		extern COMMON_API const float32	Max(const float32 a, const float32 b);
		extern COMMON_API const float32	Max(const float32 a, const float32 b, const float32 c);
		extern COMMON_API const float32	Max(const float32 a, const float32 b, const float32 c, const float32 d);
		extern COMMON_API const float32	Max(const float32 a, const float32 b, const float32 c, const float32 d, const float32 e);

		extern COMMON_API const float32	Clamp01(const float32 fValue);
		extern COMMON_API const uint32	Clamp0255(const uint32 uValue);

		extern COMMON_API const uint32	Convert01to0255(const float32 fValue);
		extern COMMON_API const float32	Convert0255to01(const uint32 uValue);

		extern COMMON_API const float32	Absolute(const float32 fValue);
		extern COMMON_API const uint32	Absolute(const int32 iValue);

		extern COMMON_API void	Swap(int32 &a, int32 &b);
		extern COMMON_API void	Swap(float32 &a, float32 &b);

		extern COMMON_API const float32	Mod(const float32 fOp1, const float32 fOp2);

		extern COMMON_API const float32	Direction(const float32 radAngle, const float32 radDestAngle);

		extern COMMON_API const float32	NormalizeAngle(const float32 radAngle);
		extern COMMON_API const bool	CheckAngle(const float32 radAngle, const float32 radMinAngle, const float32 radMaxAngle);

		extern COMMON_API const float32 DegToRad( const float32 degAngle );
		extern COMMON_API const float32 RadToDeg( const float32 radAngle );

		extern COMMON_API const float32	Sin(const float32& radAngle);
		extern COMMON_API const float32 Cos(const float32& radAngle);

		extern COMMON_API void			RandInit(const uint32 uSeed);
		extern COMMON_API const float32	Rand();
		extern COMMON_API const uint32	RandUInt32();
		extern COMMON_API const float32	Neutral(const float32 fValue, const float32 fDead);

		extern COMMON_API const float32	Prop(const float32 radAngleA, const float32 radAngleB, const float32 fP);
		
		extern COMMON_API const float32	Smooth(const float32 fStart, const float32 fEnd, const float32 fTime);
		extern COMMON_API const float32	Bounce(const float32 fProgress); // middle = 0.3, bounce = 0.4
		extern COMMON_API const float32	Bounce(const float32 fProgress, const float32 fMiddle); // bounce = 0.4
		extern COMMON_API const float32	Bounce(const float32 fProgress, const float32 fMiddle, const float32 fBounce);

		extern COMMON_API void			RotatePoint(const float32 fCx, const float32 fCy, const float32 fAngle, float32& fPx, float32& fPy);

		extern COMMON_API const float32	Lerp( const float32 fA, const float32 fB, const float32 fX );
	}
}