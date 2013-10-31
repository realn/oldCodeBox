#pragma once

#include "Math_Point.h"
#include "Math_Size.h"
#include "Math_Rectangle.h"
#include "Math_Vector.h"
#include "Math_Color.h"
#include "Math_Matrix.h"

namespace CB{
	namespace Math{
		extern COMMON_API const float	g_fPi;
		extern COMMON_API const float	g_fPi2;
		extern COMMON_API const float	g_fPiDiv2;
		extern COMMON_API const float	g_fPiDiv4;
		extern COMMON_API const float	g_fPiInv;
		extern COMMON_API const float	g_fHuge;
		extern COMMON_API const float	g_fEpsilon;
		extern COMMON_API const float	g_fDegToRad;
		extern COMMON_API const float	g_fRadToDeg;

		extern COMMON_API const bool	IsNearZero(const float fValue);
		extern COMMON_API const bool	IsNearZero(const float fValue, const float fTolerance);
		extern COMMON_API const bool	IsNearEqual(const float fValue1, const float fValue2);
		extern COMMON_API const bool	IsNearEqual(const float fValue1, const float fValue2, const float fTolerance);

		extern COMMON_API const float	Power2(const float fValue);
		extern COMMON_API const float	SqRoot(const float fValue);

		extern COMMON_API const float	Min(const float a, const float b);
		extern COMMON_API const float	Min(const float a, const float b, const float c);
		extern COMMON_API const float	Min(const float a, const float b, const float c, const float d);
		extern COMMON_API const float	Min(const float a, const float b, const float c, const float d, const float e);

		extern COMMON_API const float	Max(const float a, const float b);
		extern COMMON_API const float	Max(const float a, const float b, const float c);
		extern COMMON_API const float	Max(const float a, const float b, const float c, const float d);
		extern COMMON_API const float	Max(const float a, const float b, const float c, const float d, const float e);

		extern COMMON_API const float		Clamp01(const float fValue);
		extern COMMON_API const unsigned	Clamp0255(const unsigned uValue);

		extern COMMON_API const unsigned	Convert01to0255(const float fValue);
		extern COMMON_API const float		Convert0255to01(const unsigned uValue);

		extern COMMON_API const float		Absolute(const float fValue);
		extern COMMON_API const unsigned	Absolute(const int iValue);

		extern COMMON_API void	Swap(int &a, int &b);
		extern COMMON_API void	Swap(float &a, float &b);
		extern COMMON_API void	Swap(CVector2D& vVecA, CVector2D& vVecB);

		extern COMMON_API const float	Mod(const float fOp1, const float fOp2);
		extern COMMON_API const float	NormalizeAngle(const float fAngle);
		extern COMMON_API const bool	TestAngle(const float fAngle, const float fMinAngle, const float fMaxAngle);

		extern COMMON_API const float	Direction(const float fA, const float fG);

		extern COMMON_API const CVector2D	RotatePoint(const CVector2D& vCenter, const float fAngle, const CVector2D& vPoint);
		extern COMMON_API const CVector2D	RotatePoint(const float fAngle, const CVector2D& vPoint);
		extern COMMON_API const CVector2D	RotatePoint(const float fAngle, const float fDistance);

		extern COMMON_API const float	RotateAngle(const CVector2D& vPosition);
		extern COMMON_API const float	RotateAngle(const float fX, const float fY);
		extern COMMON_API const float	RotateAngle(const CVector2D& vCenter, const CVector2D& vPoint1, const CVector2D& vPoint2);

		extern COMMON_API const float		MidPoint(const CVector2D& vPoint1, const CVector2D& vPoint2, const float fPX);
		extern COMMON_API const CVector3D	SegmentDist(const CVector3D& vPoint1, const CVector3D& cPoint2, const float fAdvanceDistance);
		extern COMMON_API const bool		IsInsideTriangle(const CVector2D& vA, const CVector2D& vB, const CVector2D& vC, const CVector2D& vPoint);
		extern COMMON_API const bool		Intersect(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC, const CVector3D& vLineStart, const CVector3D& vLineEnd, CVector3D& vOutIntersection);
		extern COMMON_API const bool		IntersectY(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC, CVector3D& vOutIntersection);
		extern COMMON_API void				RotatePoint(const float fCx, const float fCy, const float fAngle, float& fPx, float& fPy);
		extern COMMON_API void				RotatePoint(const CVector3D& vCenter, const float fAngleHorizontal, const float fAngleVertical, CVector3D& vPoint);
		extern COMMON_API void				RotatePoint2(const CVector3D& vCenter, const float fAngleHorizontal, const float fAngleVertical, CVector3D &vPoint);
		extern COMMON_API const CVector3D	RotateView(const CVector3D& vCenter, const float fAngleHorizontal, const float fAngleVertival, const float fDistance);
		extern COMMON_API const CVector3D	LookAtPoint(const CVector3D& vEye, const float fAngleHorizontal, const float fAngleVertical, const float fLength);

		extern COMMON_API const float		Distance(const CVector2D& vA, const CVector2D& vB);		
		extern COMMON_API const float		Distance(const CVector3D& vA, const CVector3D& vB);
		extern COMMON_API const float		Distance2D(const CVector3D &a, const CVector3D &b);

		extern COMMON_API const float		Angle(const CVector3D& vU, const CVector3D& vV);
		extern COMMON_API const CVector3D	ComputeNormal(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC);
		extern COMMON_API const CVector3D	Projection(const CVector3D &a, const CVector3D &b, const CVector3D &p);

		extern COMMON_API const float	SinRad(const float fAngle);
		extern COMMON_API const float	SinDeg(const float fAngle);
		extern COMMON_API const float	CosRad(const float fAngle);
		extern COMMON_API const float	CosDeg(const float fAngle);

		extern COMMON_API const bool	LineFunction(const CVector2D& vLineStart, const CVector2D& vLineEnd, float &fOutA, float &fOutB);
		extern COMMON_API const float	DistancePlanPoint(const CVector3D &vTriA, const CVector3D &vTriB, const CVector3D &vTriC, const CVector3D &vPoint);
		extern COMMON_API const bool	IsSamePlane(const CVector3D* pPlan1, const CVector3D* pPlan2);

		extern COMMON_API void			RandInit(const unsigned uSeed);
		extern COMMON_API const float	Rand();
		extern COMMON_API const unsigned RandUInt32();
		extern COMMON_API const float	Neutral(const float fValue, const float fDead);

		extern COMMON_API const float	Prop(const int iA, const int iB, const float fP);
		extern COMMON_API const float	Smooth(const float fStart, const float fEnd, const float fTime);
		extern COMMON_API const float	Bounce(const float fProgress); // middle = 0.3, bounce = 0.4
		extern COMMON_API const float	Bounce(const float fProgress, const float fMiddle); // bounce = 0.4
		extern COMMON_API const float	Bounce(const float fProgress, const float fMiddle, const float fBounce);

		extern COMMON_API const CColor	FromRGBA(const unsigned uColor);
		extern COMMON_API const CColor	FromARGB(const unsigned uColor);
		extern COMMON_API const CColor	FromBGRA(const unsigned uColor);
		extern COMMON_API const CColor	FromABGR(const unsigned uColor);
		
		extern COMMON_API const CColorHSV	RGB2HSV(const CColor& Color);
		extern COMMON_API const CColor		HSV2RGB(const CColorHSV& Color);
	}
}



