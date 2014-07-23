#include "stdafx.h"
#include "../Include/Math_Vector.h"
#include "../Include/Math_Consts.h"
#include "../Include/Math_Funcs.h"

namespace CB{
	namespace Math{
		// Permute deux points.

		inline void Swap(CVector2D& vA, CVector2D& vB){
			CVector2D vC = vA;
			vA = vB;
			vB = vC;
		}


		// Fait tourner un point32 autour d'un centre.
		// L'angle est exprimé en radians.
		// Un angle positif est anti-horaire (CCW).

		const CVector2D	RotatePoint(const CVector2D& vCenter, const float32 fAngle, const CVector2D& vPoint){
			CVector2D	vA, vB;

			vA = vPoint - vCenter;

			vB.X = vA.X * std::cosf(fAngle) - vA.Y * std::sinf(fAngle);
			vB.Y = vA.X * std::sinf(fAngle) + vA.Y * std::cosf(fAngle);

			vB += vCenter;

			return vB;
		}

		// Fait tourner un point32 autour de l'origine.
		// L'angle est exprimé en radians.
		// Un angle positif est anti-horaire (CCW).

		const CVector2D RotatePoint(const float32 fAngle, const CVector2D& vPoint){
			CVector2D vA;

			vA.X = vPoint.X * std::cosf(fAngle) - vPoint.Y * std::sinf(fAngle);
			vA.Y = vPoint.X * std::sinf(fAngle) + vPoint.Y * std::cosf(fAngle);

			return vA;
		}

		// Fait tourner un vecteur (dist;0).
		// L'angle est exprimé en radians.
		// Un angle positif est anti-horaire (CCW).

		const CVector2D RotatePoint(const float32 fAngle, const float32 fDistance){
			return CVector2D(fDistance * std::cosf(fAngle), fDistance * std::sinf(fAngle));
		}

		// Calcule l'angle d'un triangle rectangle.
		// L'angle est anti-horaire (CCW), compris entre 0 et 2*PI.
		// Pour obtenir un angle horaire (CW), il suffit de passer -y.
		//
		//      ^
		//      |
		//    y o----o
		//      |  / |
		//      |/)a |
		//  ----o----o-->
		//      |    x 
		//      |

		const float32 RotateAngle_Check(const bool bIs, const float32 fMulPi1, const float32 fMulPi2, const CVector2D& vPos){
			if(bIs){
				return PI * fMulPi1 + std::atanf(vPos.Y / vPos.X);
			}
			return PI * fMulPi2 - std::atanf(vPos.X / vPos.Y);
		}

		const float32 RotateAngle(const CVector2D& vPosition){
			if(vPosition.IsZero()){
				return 0.0f;
			}
			if(vPosition.X >= 0.0){
				if(vPosition.Y >= 0.0f){
					return RotateAngle_Check(vPosition.X > vPosition.Y, 0.0f, 0.5f, vPosition);
				}
				else {
					return RotateAngle_Check(vPosition.X > -vPosition.Y, 2.0f, 1.5f, vPosition);
				}
			}
			else{
				if(vPosition.Y >= 0.0f){
					return RotateAngle_Check(-vPosition.X > vPosition.Y, 1.0f, 0.5f, vPosition);
				}
				else{
					return RotateAngle_Check(-vPosition.X > -vPosition.Y, 1.0f, 1.5f, vPosition);
				}
			}
		}

		const float32 RotateAngle(const float32 fX, const float32 fY){
			return RotateAngle(CVector2D(fX, fY));
		}

		// Calcule l'angle entre deux points et un centre.
		// L'angle est exprimé en radians.
		// Un angle positif est anti-horaire (CCW).

		const float32 RotateAngle(const CVector2D& vCenter, const CVector2D& vPoint1, const CVector2D& vPoint2){
			if(vPoint1 == vCenter || vPoint2 == vCenter){
				return 0.0f;
			}
			float32	fA1, fA2, fA;

			fA1 = std::asinf((vPoint1.Y - vCenter.Y) / Distance(vPoint1, vCenter));
			fA2 = std::asinf((vPoint2.Y - vCenter.Y) / Distance(vPoint2, vCenter));

			if(vPoint1.X < vCenter.X){
				fA1 = PI - fA1;
			}
			if(vPoint2.X < vCenter.X){
				fA2 = PI - fA2;
			}

			fA = fA2 - fA1;
			if(fA < 0.0f){
				fA += PI2;
			}
			return fA;
		}

		// Retourne py placé sur la droite ab.

		const float32 MidPoint(const CVector2D& vPoint1, const CVector2D& vPoint2, const float32 fPX){
			if(IsNearEqual(vPoint1.X, vPoint2.X)){
				if(vPoint1.Y < vPoint2.Y){
					return HUGE;
				}
				return -HUGE;
			}
			CVector2D vA = vPoint2 - vPoint1;
			return vA.Y * (fPX - vPoint1.X) / vA.X + vPoint1.Y;
		}

		//	Verifies if point is inside an 2D triangle.

		const bool	IsInsideTriangle_Check(const CVector2D& vA, const CVector2D& vB, const CVector2D& vC, const CVector2D& vPoint){
			float32 fN = MidPoint(vA, vB, vPoint.X);
			float32 fM = MidPoint(vA, vC, vPoint.X);
			if((fN > vPoint.Y || vPoint.Y > fM) && (fN < vPoint.Y || vPoint.Y < fM)){
				return false;
			}
			return true;
		}

		const bool IsInsideTriangle(const CVector2D& vTriangleA, const CVector2D& vTriangleB, const CVector2D& vTriangleC, const CVector2D& vPoint){
			CVector2D vA = vTriangleA;
			CVector2D vB = vTriangleB;
			CVector2D vC = vTriangleC;

			if(vPoint.X < vA.X && vPoint.X < vB.X && vPoint.X < vC.X)	return false;
			if(vPoint.X > vA.X && vPoint.X > vB.X && vPoint.X > vC.X)	return false;
			if(vPoint.Y < vA.Y && vPoint.Y < vB.Y && vPoint.Y < vC.Y)	return false;
			if(vPoint.Y > vA.Y && vPoint.Y > vB.Y && vPoint.Y > vC.Y)	return false;

			if(vA.X > vB.X)	Swap(vA, vB);
			if(vA.X > vC.X)	Swap(vA, vC);
			if(vC.X < vA.X)	Swap(vC, vA);
			if(vC.X < vB.X)	Swap(vC, vB);

			if(!IsInsideTriangle_Check(vA, vB, vC, vPoint))	return false;
			if(!IsInsideTriangle_Check(vC, vB, vA, vPoint))	return false;

			return true;
		}

		// Returns distance between two points on plane.

		const float32 Distance(const CVector2D& vA, const CVector2D& vB){
			return (vA - vB).GetVectorLength();
		}

		// Calcule les paramètres a et b du segment passant par
		// les points p1 et p2, sachant que :
		//		f(x) = ax+b
		// Retourne FALSE si la droite est verticale.

		const bool LineFunction(const CVector2D& vLineStart, const CVector2D& vLineEnd, float32 &fOutA, float32 &fOutB){
			if(IsNearZero(vLineStart.X - vLineEnd.X)){
				fOutA = HUGE;
				fOutB = vLineEnd.X;
				return false;
			}

			CVector2D vLine = vLineEnd - vLineStart;
			fOutA = vLine.Y / vLine.X;
			fOutB = vLineEnd.Y - vLineEnd.X * fOutA;
			return true;
		}

		const CVector2D	Lerp( const CVector2D& vA, const CVector2D& vB, const float32 fX ) {
			return vA + (vB - vA) * fX;
		}
	}
}