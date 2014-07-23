#include "stdafx.h"

#include "../Include/Math_Funcs.h"
#include "../Include/Math_Consts.h"

namespace CB{
	namespace Math{
		// returns true if two values are near equality.

		const bool	IsNearEqual(const float32 fA, const float32 fB){
			return IsNearEqual(fA, fB, EPSILON);
		}

		const bool	IsNearEqual(const float32 fA, const float32 fB, const float32 fTolerance){
			return Absolute(fA-fB) < fTolerance;
		}

		// returns true if given value is very near zero.

		const bool	IsNearZero(const float32 fValue){
			return IsNearZero(fValue, EPSILON);
		}

		const bool	IsNearZero(const float32 fValue, const float32 fTolerance){
			return Absolute(fValue) < fTolerance;
		}

		// returns given value power of two.

		inline const float32	Power2(const float32 fValue){
			return std::powf(fValue, 2.0f);
		}

		inline const float32	Power(const float32 fValue, const float32 fMag) {
			return std::powf(fValue, fMag);
		}

		// returns given value square root.

		inline const float32	SqRoot(const float32 fValue){
			return std::sqrtf(fValue);
		}

		// returns smaller value of two given.

		inline const float32 Min(const float32 fA, const float32 fB){
			if(fA <= fB){
				return fA;
			}
			return fB;
		}

		inline const float32 Min(const float32 fA, const float32 fB, const float32 fC){
			return Min(Min(fA, fB), fC);
		}

		inline const float32 Min(const float32 fA, const float32 fB, const float32 fC, const float32 fD){
			return Min(Min(fA, fB), Min(fC, fD));
		}

		inline const float32 Min(const float32 fA, const float32 fB, const float32 fC, const float32 fD, const float32 fE){
			return Min(Min(fA, fB), Min(fC, fD), fE);
		}

		// returns greather value of two given.

		inline const float32 Max(const float32 fA, const float32 fB){
			if(fA >= fB){
				return fA;
			}
			return fB;
		}

		inline const float32 Max(const float32 fA, const float32 fB, const float32 fC){
			return Max(Max(fA, fB), fC);
		}

		inline const float32 Max(const float32 fA, const float32 fB, const float32 fC, const float32 fD){
			return Max(Max(fA, fB), Max(fC, fD));
		}

		inline const float32 Max(const float32 fA, const float32 fB, const float32 fC, const float32 fD, const float32 fE){
			return Max(Max(fA, fB), Max(fC, fD), fE);
		}

		// returns value clamped between zero and one.

		inline const float32	Clamp01(const float32 fValue){
			if(fValue < 0.0f)	return 0.0f;
			if(fValue > 1.0f)	return 1.0f;
			return fValue;
		}

		// returns value clamped between zero and max value of byte.

		inline const uint32	Clamp0255(const uint32 uValue){
			if(uValue > 255)	return 255;
			return uValue;
		}

		// converts value range from floating point32 0-1 to fixed 0-255

		inline const uint32	Convert01to0255(const float32 fValue){
			return (uint32)(Clamp01(fValue) * 255.0f);
		}

		// converts value range from fixed 0-255 to floating point32 0-1

		inline const float32	Convert0255to01(const uint32 uValue){
			return ((float32)Clamp0255(uValue)) / 255.0f;
		}

		// returns absolute number from given value.

		inline const float32 Absolute(const float32 fValue){
			return std::fabsf(fValue);
		}

		inline const uint32	Absolute(const int32 iValue){
			if(iValue < 0){
				return -iValue;
			}
			return iValue;
		}

		// Swap two numbers

		inline void Swap(int32 &iA, int32 &iB){
			int	iC = iA;
			iA = iB;
			iB = iC;
		}

		inline void Swap(float32 &fA, float32 &fB){
			float32	fC = fA;
			fA = fB;
			fB = fC;
		}

		//	Returns rest from division of floating point values;

		inline const float32 Mod(const float32 fA, const float32 fB){
			return fA - ((int)(fA / fB)) * fB;
		}

		//	Returns normalized angle with value between 0 - 2*PI

		inline const float32 NormalizeAngle(const float32 fAngle){
			float32 fAng = Mod(fAngle, PI2);
			if(fAng < 0.0f){
				return PI2 + fAng;
			}
			return fAng;
		}

		//	Checks angle between two other angles.

		const bool CheckAngle(const float32 fAngle, const float32 fMinAngle, const float32 fMaxAngle){
			float32 fAng = NormalizeAngle(fAngle);
			float32 fMin = NormalizeAngle(fMinAngle);
			float32 fMax = NormalizeAngle(fMaxAngle);

			if(fMin > fMax){
				return (fAng <= fMax || fAng >= fMin);
			}
			return (fAng >= fMin && fAng <= fMax);
		}

		inline const float32	RadToDeg( const float32 radAngle ) {
			return radAngle * PIMUL180;
		}

		inline const float32	DegToRad( const float32 degAngle ) {
			return degAngle * PIDIV180;
		}


		// Calculates direction from one angle to another.

		const float32 Direction(const float32 radAngle, const float32 radDestAngle){
			float32 fA = NormalizeAngle(radAngle);
			float32 fG = NormalizeAngle(radDestAngle);

			if(fA < fG){
				if(fA + PI2 - fG < fG - fA){
					fA += PI2;
				}
			}
			else{
				if(fG + PI2 - fA < fA - fG){
					fG += PI2;
				}
			}
			return fG - fA;
		}


		inline const float32	Sin( const float32 radAngle ) {
			return std::sinf( radAngle );
		}

		inline const float32	Cos( const float32 radAngle ) {
			return std::cosf( radAngle );
		}

		void	RandInit(const uint32 uSeed){
			std::srand(uSeed);
		}

		//	Returns random value between values 0 - 1.

		const float32	Rand(){
			return float32(std::rand())/float32(RAND_MAX);
		}

		const uint32 RandUInt32(){
			return uint32(std::rand());
		}

		// Gestion de la zone neutre d'un joystick.

		//  in:   -1            0            1
		//       --|-------|----o----|-------|-->
		//                      <---->
		//                       dead
		//  out:  -1       0         0       1

		const float32 Neutral(const float32 fValue, const float32 fDead){
			if(Absolute(fValue) <= fDead){
				return 0.0f;
			}
			else if(fValue > 0.0f){
				return (fValue - fDead) / (1.0f - fDead);
			}
			return (fValue + fDead) / (1.0f - fDead);
		}


		// Calcule une valeur (radians) proportionnelle comprise
		// entre a et b (degrés).

		const float32 Prop(const float32 radAngleA, const float32 radAngleB, const float32 fP){
			float32 fAA = radAngleA;
			float32 fBB = radAngleB;

			return fAA * (fBB - fAA) * fP;
		}

		// Smooths out value progressed from start to end at given time.

		const float32 Smooth(const float32 fStart, const float32 fEnd, const float32 fTime){
			float32 fNext = fStart + (fEnd - fStart) * fTime;

			if(fEnd > fStart){
				if(fNext > fEnd){
					fNext = fEnd;
				}
			}
			if(fEnd < fStart){
				if(fNext < fEnd){
					fNext = fEnd;
				}
			}
			return fNext;
		}


		// Fait reboudir un mouvement quelconque.

		//	out
		//	 |
		//	1+------o-------o---
		//	 |    o | o   o |  | bounce
		//	 |   o  |   o---|---
		//	 |  o   |       |
		//	 | o    |       |
		//	-o------|-------+----> progress
		//	0|      |       1
		//	 |<---->|middle

		const float32	Bounce(const float32 fProgress){
			return Bounce(fProgress, 0.3f, 0.4f);
		}

		const float32	Bounce(const float32 fProgress, const float32 fMiddle){
			return Bounce(fProgress, fMiddle, 0.4f);
		}

		const float32 Bounce(const float32 fProgress, const float32 fMiddle, const float32 fBounce){
			float32 fClampProgress = 0.0f;
			if(fProgress < fMiddle){
				fClampProgress = fProgress / fMiddle;
				return 0.5f + std::sinf(fClampProgress * PI - PIDIV2) / 2.0f;
			}
			else{
				fClampProgress = (fProgress - fMiddle) / (1.0f - fMiddle);
				return (1.0f - fBounce / 2.0f) + std::sinf((0.5f + fProgress * 2.0f) * PI) * (fBounce / 2.0f);
			}
		}

		// Fait tourner un point32 autour d'un centre dans le plan.
		// L'angle est exprimé en radians.
		// Un angle positif est anti-horaire (CCW).

		void RotatePoint(const float32 fCx, const float32 fCy, const float32 fAngle, float32 &fPx, float32 &fPy){
			fPx -= fCx;
			fPy -= fCy;

			float32 fAx = fPx * std::cosf(fAngle) - fPy * std::sinf(fAngle);
			float32 fAy = fPx * std::sinf(fAngle) + fPy * std::cosf(fAngle);

			fPx = fCx + fAx;
			fPy = fCy + fAy;
		}

		inline const float32	Lerp( const float32 fA, const float32 fB, const float32 fX ) {
			return fA + (fB - fA) * fX;
		}
	}
}