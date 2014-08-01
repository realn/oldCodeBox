#include "stdafx.h"
#include "../Include/Math_Vector3D.h"
#include "../Include/Math_Vector2D.h"
#include "../Include/Math_Vector4D.h"
#include "../Include/Math_Funcs.h"
#include "../Include/Math_Consts.h"

namespace CB{
	namespace Math{
		// Calcule l'intersection "i" de la droite "de" avec le plan "abc".

		const bool Intersect(
			const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC,
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



		// Fait tourner un point32 autour d'un centre dans l'espace.
		// L'angles sont exprimés en radians.
		// Un angle positif est anti-horaire (CCW).

		void RotatePoint(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertical, CVector3D& vPoint){
			CVector3D	vA;
	
			vPoint -= vCenter;

			float32 csV = std::cosf(fAngleVertical);
			float32 csH = std::cosf(fAngleHorizontal);
			float32 siV = std::sinf(fAngleVertical);
			float32 siH = std::sinf(fAngleHorizontal);

			vA.X = vPoint.X * csH	- vPoint.Z * siH;
			vA.Y = vPoint.Z * siV	+ vPoint.Y * csV;
			vA.Z = vPoint.X * siH	+ vPoint.Z * csH;
	
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

		//const CVector3D RotateView(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertival, const float32 fDistance){
		//	CMatrix	mRes, mRotH, mRotV;

		//	mRotV.SetRotation(AxisOrientation::AxisX, -fAngleVertival);
		//	mRotH.SetRotation(AxisOrientation::AxisY, -fAngleHorizontal);

		//	mRes = mRotV * mRotH;

		//	return mRes * CVector3D(fDistance, 0.0f, 0.0f) + vCenter;
		//}

		// Calcule le point32 d'arrivée.

		const CVector3D LookatPoint(const CVector3D& vEye, const float32 fAngleHorizontal, const float32 fAngleVertical, const float32 fLength){
			CVector3D vLookAt = vEye;
			vLookAt.Z += fLength;

			RotatePoint(vEye, fAngleHorizontal, fAngleVertical, vLookAt);

			return vLookAt;
		}

		// Returns distance between two points in space.

		const float32 Distance(const CVector3D& vA, const CVector3D& vB){
			return (vA - vB).GetVectorLength();
		}

		// Returns distance between two points projected on XZ plane.

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
			if(fDistance > EPSILON){
				return false;
			}

			return true;
		}


		const CVector3D	Lerp(const CVector3D& vA, const CVector3D& vB, const float32 fX){
			return vA + (vB - vA) * fX;
		}
	}
}