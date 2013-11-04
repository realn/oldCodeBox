#include "../Include/Math.h"
#include <cmath>
#include <cstdlib>

namespace CB{
	namespace Math{

		const float32	g_fPi		= 3.14159265358979323846f;
		const float32	g_fPi2		= 6.28318530717958623200f;
		const float32	g_fPiDiv2	= 1.57079632679489655800f;
		const float32	g_fPiDiv4	= 0.78539816339744827900f;
		const float32	g_fPiInv	= 0.31830988618379069122f;
		const float32	g_fHuge		= 1e+6f;
		const float32	g_fEpsilon	= 1e-6f;
		const float32	g_fDegToRad	= 0.01745329251994329547f;
		const float32	g_fRadToDeg	= 57.29577951308232286465f;


		// returns true if two values are near equality.

		const bool	IsNearEqual(const float32 fA, const float32 fB){
			return IsNearEqual(fA, fB, g_fEpsilon);
		}

		const bool	IsNearEqual(const float32 fA, const float32 fB, const float32 fTolerance){
			return Absolute(fA-fB) < fTolerance;
		}

		// returns true if given value is very near zero.

		const bool	IsNearZero(const float32 fValue){
			return IsNearZero(fValue, g_fEpsilon);
		}

		const bool	IsNearZero(const float32 fValue, const float32 fTolerance){
			return Absolute(fValue) < fTolerance;
		}

		// returns given value power of two.

		inline const float32	Power2(const float32 fValue){
			return std::powf(fValue, 2.0f);
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

		// converts value range from float32ing point32 0-1 to fixed 0-255

		inline const uint32	Convert01to0255(const float32 fValue){
			return (uint32)(Clamp01(fValue) * 255.0f);
		}

		// converts value range from fixed 0-255 to float32ing point32 0-1

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

		// Permute deux entiers.

		inline void Swap(int32 &iA, int32 &iB){
			int	iC = iA;
			iA = iB;
			iB = iC;
		}

		// Permute deux réels.

		inline void Swap(float32 &fA, float32 &fB){
			float32	fC = fA;
			fA = fB;
			fB = fC;
		}

		// Permute deux points.

		inline void Swap(CVector2D& vA, CVector2D& vB){
			CVector2D vC = vA;
			vA = vB;
			vB = vC;
		}

		// Retourne le modulo d'un nombre flottant.
		//	Mod(8.1, 4) = 0.1
		//	Mod(n, 1) = partie fractionnaire de n

		inline const float32 Mod(const float32 fA, const float32 fB){
			return fA - ((int)(fA / fB)) * fB;
		}

		// Retourne un angle normalisé, c'est-à-dire compris entre
		// 0 et 2*PI.

		inline const float32 NormalizeAngle(const float32 fAngle){
			float32 fAng = Mod(fAngle, g_fPi2);
			if(fAng < 0.0f){
				return g_fPi2 + fAng;
			}
			return fAng;
		}

		// Teste si un angle est compris entre 2 bornes.

		const bool TestAngle(const float32 fAngle, const float32 fMinAngle, const float32 fMaxAngle){
			float32 fAng = NormalizeAngle(fAngle);
			float32 fMin = NormalizeAngle(fMinAngle);
			float32 fMax = NormalizeAngle(fMaxAngle);

			if(fMin > fMax){
				return (fAng <= fMax || fAng >= fMin);
			}
			return (fAng >= fMin && fAng <= fMax);
		}

		// Calcule l'angle permettant de tourner de l'angle a vers l'angle g.
		// Un angle positif est anti-horaire (CCW).

		const float32 Direction(const float32 fAngle, const float32 fGer){
			float32 fA = NormalizeAngle(fAngle);
			float32 fG = NormalizeAngle(fGer);

			if(fA < fG){
				if(fA + g_fPi2 - fG < fG - fA){
					fA += g_fPi2;
				}
			}
			else{
				if(fG + g_fPi2 - fA < fA - fG){
					fG += g_fPi2;
				}
			}
			return fG - fA;
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
				return g_fPi * fMulPi1 + std::atanf(vPos.Y / vPos.X);
			}
			return g_fPi * fMulPi2 - std::atanf(vPos.X / vPos.Y);
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
				fA1 = g_fPi - fA1;
			}
			if(vPoint2.X < vCenter.X){
				fA2 = g_fPi - fA2;
			}

			fA = fA2 - fA1;
			if(fA < 0.0f){
				fA += g_fPi2;
			}
			return fA;
		}

		// Retourne py placé sur la droite ab.

		const float32 MidPoint(const CVector2D& vPoint1, const CVector2D& vPoint2, const float32 fPX){
			if(IsNearEqual(vPoint1.X, vPoint2.X)){
				if(vPoint1.Y < vPoint2.Y){
					return g_fHuge;
				}
				return -g_fHuge;
			}
			CVector2D vA = vPoint2 - vPoint1;
			return vA.Y * (fPX - vPoint1.X) / vA.X + vPoint1.Y;
		}

		// Avance de "dist" le long du segment p1-p2.

		const CVector3D	SegmentDist(const CVector3D& vPoint1, const CVector3D& vPoint2, const float32 fAdvanceDistance){
			return vPoint1 + (vPoint2 - vPoint1).GetNormalized() * fAdvanceDistance;
		}

		// Vérifie si un point32 est dans un triangle.

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

		// Calcule l'intersection "i" de la droite "de" avec le plan "abc".

		const bool Intersect(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC,
									   const CVector3D& vLineStart, const CVector3D& vLineEnd, CVector3D& vOutIntersection)
		{
			CVector3D vTriCross = (vTriB - vTriA).Cross(vTriC - vTriA);
	
			float32 fD2 = (vLineStart - vLineEnd).Dot(vTriCross);
			if(fD2 == 0.0f){
				return false;
			}

			float32 fD1 = (vLineStart - vTriA).Dot(vTriCross);

			vOutIntersection = vLineStart + (vLineEnd - vLineStart) * (fD1/fD2);
			return true;
		}

		// Calcule l'intersection de la droite passant par p(x,z) parallèle
		// à l'axe y, avec le plan abc. Retourne p.y.

		const bool IntersectY(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC, CVector3D& vOutIntersection){

			CVector3D vBA = vTriB - vTriA;
			CVector3D vCA = vTriC - vTriA;
			CVector3D vPA = vOutIntersection - vTriA;

			float32 fD = vBA.X * vCA.Z - vCA.X * vBA.Z;
			if(fD == 0.0f){
				return false;
			}

			float32 fD1 = vPA.X * vCA.Z - vCA.X * vPA.Z;
			float32 fD2 = vBA.X * vPA.Z - vPA.X * vBA.Z;

			vOutIntersection.Y = vTriA.Y + (fD1/fD) * vBA.Y + (fD2/fD) * vCA.Y;
			return true;
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

		// Fait tourner un point32 autour d'un centre dans l'espace.
		// L'angles sont exprimés en radians.
		// Un angle positif est anti-horaire (CCW).

		void RotatePoint(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertical, CVector3D& vPoint){
			CVector3D	vA;
	
			vPoint -= vCenter;

			vA.X = vPoint.X * std::cosf(fAngleHorizontal)	- vPoint.Z * std::sinf(fAngleHorizontal);
			vA.Y = vPoint.Z * std::sinf(fAngleVertical)		+ vPoint.Y * std::cosf(fAngleVertical);
			vA.Z = vPoint.X * std::sinf(fAngleHorizontal)	+ vPoint.Z * std::cosf(fAngleHorizontal);
	
			vPoint = vCenter + vA;
		}

		// Fait tourner un point32 autour d'un centre dans l'espace.
		// L'angles sont exprimés en radians.
		// Un angle positif est anti-horaire (CCW).

		void RotatePoint2(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertical, CVector3D &vPoint){
			CVector3D vA, vB;

			vPoint -= vCenter;

			vA.X = vPoint.X * std::cosf(fAngleHorizontal)	- vPoint.Z * std::sinf(fAngleHorizontal);
			vA.Y = vPoint.Y;
			vA.Z = vPoint.X * std::sinf(fAngleHorizontal)	+ vPoint.Z * std::cosf(fAngleHorizontal);

			vB.X = vA.X;
			vB.Y = vA.Z * std::sinf(fAngleVertical)	+ vA.Y * std::cosf(fAngleVertical);
			vB.Z = vA.Z * std::cosf(fAngleVertical) - vA.Y * std::sinf(fAngleVertical);

			vPoint = vCenter + vB;
		}

		// Calcul le point32 de vue permettant de regarder un centre selon deux
		// angles et à une certaine distance.

		const CVector3D RotateView(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertival, const float32 fDistance){
			CMatrix	mRes, mRotH, mRotV;

			mRotV.SetRotation(AxisOrientation::AxisX, -fAngleVertival);
			mRotH.SetRotation(AxisOrientation::AxisY, -fAngleHorizontal);

			mRes = mRotV * mRotH;

			return mRes * CVector3D(fDistance, 0.0f, 0.0f) + vCenter;
		}

		// Calcule le point32 d'arrivée.

		const CVector3D LookatPoint(const CVector3D& vEye, const float32 fAngleHorizontal, const float32 fAngleVertical, const float32 fLength){
			CVector3D vLookAt = vEye;
			vLookAt.Z += fLength;

			RotatePoint(vEye, fAngleHorizontal, fAngleVertical, vLookAt);

			return vLookAt;
		}


		// Retourne la distance entre deux points.

		const float32 Distance(const CVector2D& vA, const CVector2D& vB){
			return (vA - vB).GetVectorLength();
		}

		// Retourne la distance entre deux points.

		const float32 Distance(const CVector3D& vA, const CVector3D& vB){
			return (vA - vB).GetVectorLength();
		}

		// Retourne la distance "à plat" entre deux points.

		const float32 Distance2D(const CVector3D& vA, const CVector3D& vB){
			CVector3D vAB = vA - vB;
			return CVector2D(vAB.X, vAB.Z).GetVectorLength();
		}

		// Retourne l'angle formé par deux vecteurs.

		const float32 Angle(const CVector3D& vU, const CVector3D& vV){
			float32 fLen = vU.GetVectorLength() * vV.GetVectorLength();
			float32 fA = std::acosf(vU.Dot(vV) / fLen);
			//float32 fB = std::asinf(vU.Cross(vV).GetLength() / fLen);
			return fA;
		}

		// Retourne le vecteur normal d'une face triangulaire.

		const CVector3D	ComputeNormal(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC){
			CVector3D u = vTriC - vTriA;
			CVector3D v = vTriB - vTriA;

			return u.Cross(v).GetNormalized();
		}


		// Calcule la projection d'un point32 P sur une droite AB.

		const CVector3D	Projection(const CVector3D& vA, const CVector3D& vB, const CVector3D& vPoint){
			CVector3D vBA = vB - vA;
			CVector3D vPA = vPoint - vA;

			float32 fK = vBA.Dot(vPA) / vBA.Dot(vBA);

			return vA + vBA * fK;
		}

		const float32	SinRad(const float32 fAngle){
			return std::sinf(fAngle);
		}

		const float32 SinDeg(const float32 fAngle){
			return std::sinf(fAngle * g_fDegToRad);
		}

		const float32 CosRad(const float32 fAngle){
			return std::cosf(fAngle);
		}

		const float32 CosDeg(const float32 fAngle){
			return std::cosf(fAngle * g_fDegToRad);
		}

		// Calcule les paramètres a et b du segment passant par
		// les points p1 et p2, sachant que :
		//		f(x) = ax+b
		// Retourne FALSE si la droite est verticale.

		const bool LineFunction(const CVector2D& vLineStart, const CVector2D& vLineEnd, float32 &fOutA, float32 &fOutB){
			if(IsNearZero(vLineStart.X - vLineEnd.X)){
				fOutA = g_fHuge;
				fOutB = vLineEnd.X;
				return false;
			}

			CVector2D vLine = vLineEnd - vLineStart;
			fOutA = vLine.Y / vLine.X;
			fOutB = vLineEnd.Y - vLineEnd.X * fOutA;
			return true;
		}


		// Calcule la distance entre un plan ABC et un point32 P.

		const float32 DistancePlanPoint(const CVector3D& vTriA, const CVector3D& vTriB,
												const CVector3D& vTriC, const CVector3D& vPoint)
		{
			CVector3D	vNormal = ComputeNormal(vTriA, vTriB, vTriC);
			CVector4D	vVec(vNormal, -vNormal.Dot(vTriA));

			return Absolute(vVec.Dot(CVector4D(vPoint, 1.0f)));
		}

		// Vérifie si deux plans définis par 3 points font partie
		// du même plan.

		const bool	IsSamePlane(const CVector3D* pPlan1, const CVector3D* pPlan2){
			CVector3D vNormal1 = ComputeNormal(pPlan1[0], pPlan1[1], pPlan1[2]);
			CVector3D vNormal2 = ComputeNormal(pPlan2[0], pPlan2[1], pPlan2[2]);

			if(!(vNormal1-vNormal2).IsNearZero()){
				return false;
			}

			float32 fDistance = DistancePlanPoint(pPlan1[0], pPlan1[1], pPlan1[2], pPlan2[0]);
			if(fDistance > g_fEpsilon){
				return false;
			}

			return true;
		}

		// Retourne une valeur aléatoire comprise entre 0 et 1.

		void	RandInit(const uint32 uSeed){
			std::srand(uSeed);
		}

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

		const float32 Prop(const int32 iA, const int32 iB, const float32 fP){
			float32 fAA = float32(iA) * g_fDegToRad;
			float32 fBB = float32(iB) * g_fDegToRad;

			return fAA * (fBB - fAA) * fP;
		}

		// Fait progresser mollement une valeur souhaitée à partir de
		// sa valeur actuelle. Plus le temps est grand et plus la
		// progression est rapide.

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
				return 0.5f + std::sinf(fClampProgress * g_fPi - g_fPiDiv2) / 2.0f;
			}
			else{
				fClampProgress = (fProgress - fMiddle) / (1.0f - fMiddle);
				return (1.0f - fBounce / 2.0f) + std::sinf((0.5f + fProgress * 2.0f) * g_fPi) * (fBounce / 2.0f);
			}
		}

		const CColor	FromABGR(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[3], pColor[2], pColor[1], pColor[0]);

			return cResult;
		}

		const CColor	FromARGB(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[1], pColor[2], pColor[3], pColor[0]);
	
			return cResult;
		}

		const CColor	FromBGRA(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[2], pColor[1], pColor[0], pColor[3]);

			return cResult;
		}

		const CColor	FromRGBA(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[0], pColor[1], pColor[2], pColor[3]);

			return cResult;
		}

		// Conversion RGB vers HSV.

		const CColorHSV RGB2HSV(const CColor& Color){
			CColorHSV	dest;
			float32	min, max, delta;

			min = Min(Color.Red, Color.Green, Color.Blue);
			max = Max(Color.Red, Color.Green, Color.Blue);

			dest.V = max;

			if(max == 0.0f){
				dest.S = 0.0f;
				dest.H = 0.0f;
			}
			else{
				delta = max - min;
				dest.S = delta / max;
				if(Color.Red == max){
					dest.H = (Color.Green - Color.Blue) / delta;
				}
				else if(Color.Green == max){
					dest.H = 2.0f + (Color.Blue - Color.Red) / delta;
				}
				else{
					dest.H = 4.0f + (Color.Red - Color.Green) / delta;
				}

				dest.H *= 60.0f;
				if(dest.H < 0.0f){
					dest.H += 360.0f;
				}
				dest.H /= 360.0f;
			}

			return dest;
		}

		// Conversion HSV vers RGB.

		const CColor	HSV2RGB(const CColorHSV& Color){
			CColor		dest;
			CColorHSV	src;
			int		i;
			float32	f,v,p,q,t;

			src.H = Clamp01(Color.H) * 360.0f;
			src.S = Clamp01(Color.S);
			src.V = Clamp01(Color.V);

			if(src.S == 0.0f){
				dest.Set(src.V, src.V, src.V);
			}
			else{
				if(src.H == 360.0f){
					src.H = 0.0f;
				}
				src.H /= 60.0f;
				i = (int)src.H;
				f = src.H - i;

				v = src.V;
				p = src.V * (1.0f - src.S);
				q = src.V * (1.0f - (src.S * f));
				t = src.V * (1.0f - (src.S * (1.0f - f)));

				switch(i){
				case 0:	dest.Set(v, t, p);	break;
				case 1:	dest.Set(q, v, p);	break;
				case 2:	dest.Set(p, v, t);	break;
				case 3:	dest.Set(p, q, v);	break;
				case 4:	dest.Set(t, p, v);	break;
				case 5:	dest.Set(v, p, q);	break;
				}
			}
			return dest;
		}
	}
}