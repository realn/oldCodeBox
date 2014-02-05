#pragma once

#include "Math_Point.h"
#include "Math_Size.h"
#include "Math_Rectangle.h"
#include "Math_Vector.h"
#include "Math_Color.h"
#include "Math_Matrix.h"

namespace CB{
	namespace Math{
		extern COMMON_API const float32	g_fPi;
		extern COMMON_API const float32	g_fPi2;
		extern COMMON_API const float32	g_fPiDiv2;
		extern COMMON_API const float32	g_fPiDiv4;
		extern COMMON_API const float32	g_fPiInv;
		extern COMMON_API const float32	g_fHuge;
		extern COMMON_API const float32	g_fEpsilon;
		extern COMMON_API const float32	g_fDegToRad;
		extern COMMON_API const float32	g_fRadToDeg;

		extern COMMON_API const bool	IsNearZero(const float32 fValue);
		extern COMMON_API const bool	IsNearZero(const float32 fValue, const float32 fTolerance);
		extern COMMON_API const bool	IsNearEqual(const float32 fValue1, const float32 fValue2);
		extern COMMON_API const bool	IsNearEqual(const float32 fValue1, const float32 fValue2, const float32 fTolerance);

		extern COMMON_API const float32	Power2(const float32 fValue);
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
		extern COMMON_API void	Swap(CVector2D& vVecA, CVector2D& vVecB);

		extern COMMON_API const float32	Mod(const float32 fOp1, const float32 fOp2);
		extern COMMON_API const float32	NormalizeAngle(const float32 fAngle);
		extern COMMON_API const bool	TestAngle(const float32 fAngle, const float32 fMinAngle, const float32 fMaxAngle);

		extern COMMON_API const float32	Direction(const float32 fA, const float32 fG);

		extern COMMON_API const CVector2D	RotatePoint(const CVector2D& vCenter, const float32 fAngle, const CVector2D& vPoint);
		extern COMMON_API const CVector2D	RotatePoint(const float32 fAngle, const CVector2D& vPoint);
		extern COMMON_API const CVector2D	RotatePoint(const float32 fAngle, const float32 fDistance);

		extern COMMON_API const float32	RotateAngle(const CVector2D& vPosition);
		extern COMMON_API const float32	RotateAngle(const float32 fX, const float32 fY);
		extern COMMON_API const float32	RotateAngle(const CVector2D& vCenter, const CVector2D& vPoint1, const CVector2D& vPoint2);

		extern COMMON_API const float32		MidPoint(const CVector2D& vPoint1, const CVector2D& vPoint2, const float32 fPX);
		extern COMMON_API const CVector3D	SegmentDist(const CVector3D& vPoint1, const CVector3D& cPoint2, const float32 fAdvanceDistance);
		extern COMMON_API const bool		IsInsideTriangle(const CVector2D& vA, const CVector2D& vB, const CVector2D& vC, const CVector2D& vPoint);
		extern COMMON_API const bool		Intersect(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC, const CVector3D& vLineStart, const CVector3D& vLineEnd, CVector3D& vOutIntersection);
		extern COMMON_API const bool		IntersectY(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC, CVector3D& vOutIntersection);
		extern COMMON_API void				RotatePoint(const float32 fCx, const float32 fCy, const float32 fAngle, float32& fPx, float32& fPy);
		extern COMMON_API void				RotatePoint(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertical, CVector3D& vPoint);
		extern COMMON_API void				RotatePoint2(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertical, CVector3D &vPoint);
		extern COMMON_API const CVector3D	RotateView(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertival, const float32 fDistance);
		extern COMMON_API const CVector3D	LookAtPoint(const CVector3D& vEye, const float32 fAngleHorizontal, const float32 fAngleVertical, const float32 fLength);

		extern COMMON_API const float32		Distance(const CVector2D& vA, const CVector2D& vB);		
		extern COMMON_API const float32		Distance(const CVector3D& vA, const CVector3D& vB);
		extern COMMON_API const float32		Distance2D(const CVector3D &a, const CVector3D &b);

		extern COMMON_API const float32		Angle(const CVector3D& vU, const CVector3D& vV);
		extern COMMON_API const CVector3D	ComputeNormal(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC);
		extern COMMON_API const CVector3D	Projection(const CVector3D &a, const CVector3D &b, const CVector3D &p);

		extern COMMON_API const float32	SinRad(const float32 fAngle);
		extern COMMON_API const float32	SinDeg(const float32 fAngle);
		extern COMMON_API const float32	CosRad(const float32 fAngle);
		extern COMMON_API const float32	CosDeg(const float32 fAngle);

		extern COMMON_API const bool	LineFunction(const CVector2D& vLineStart, const CVector2D& vLineEnd, float32 &fOutA, float32 &fOutB);
		extern COMMON_API const float32	DistancePlanPoint(const CVector3D &vTriA, const CVector3D &vTriB, const CVector3D &vTriC, const CVector3D &vPoint);
		extern COMMON_API const bool	IsSamePlane(const CVector3D* pPlan1, const CVector3D* pPlan2);

		extern COMMON_API void			RandInit(const uint32 uSeed);
		extern COMMON_API const float32	Rand();
		extern COMMON_API const uint32	RandUInt32();
		extern COMMON_API const float32	Neutral(const float32 fValue, const float32 fDead);

		extern COMMON_API const float32	Prop(const int32 iA, const int32 iB, const float32 fP);
		extern COMMON_API const float32	Smooth(const float32 fStart, const float32 fEnd, const float32 fTime);
		extern COMMON_API const float32	Bounce(const float32 fProgress); // middle = 0.3, bounce = 0.4
		extern COMMON_API const float32	Bounce(const float32 fProgress, const float32 fMiddle); // bounce = 0.4
		extern COMMON_API const float32	Bounce(const float32 fProgress, const float32 fMiddle, const float32 fBounce);

		extern COMMON_API const CColor	FromRGBA(const uint32 uColor);
		extern COMMON_API const CColor	FromARGB(const uint32 uColor);
		extern COMMON_API const CColor	FromBGRA(const uint32 uColor);
		extern COMMON_API const CColor	FromABGR(const uint32 uColor);
		
		extern COMMON_API const CColorHSV	RGB2HSV(const CColor& Color);
		extern COMMON_API const CColor		HSV2RGB(const CColorHSV& Color);
	}
}



