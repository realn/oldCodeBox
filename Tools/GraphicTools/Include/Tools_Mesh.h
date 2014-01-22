#pragma once

#include "Macros.h"
#include <Math_Vector.h>
#include <Collection_List.h>

namespace CB{
	namespace Tools{
		class GRAPHICTOOLS_API CMeshRawV{
		public:
			Collection::CList<Math::CVector3D>	Vertices;
			uint32	uNumberOfPolygons;

			CMeshRawV();
			CMeshRawV(const CMeshRawV& Mesh);

			void	AddVertex(const Math::CVector3D& vPosition);
		};

		class GRAPHICTOOLS_API CMeshRawVT{
		public:
			Collection::CList<Math::CVector3D>	Vertices;
			Collection::CList<Math::CVector2D>	TexCoords;
			uint32	uNumberOfPolygons;

			CMeshRawVT();
			CMeshRawVT(const CMeshRawVT& Mesh);

			void	AddVertex(const Math::CVector3D& vPosition, const Math::CVector2D& vTexCoord);
		};

		class GRAPHICTOOLS_API CMeshRawVTN{
		public:
			Collection::CList<Math::CVector3D>	Vertices;
			Collection::CList<Math::CVector2D>	TexCoords;
			Collection::CList<Math::CVector3D>	Normals;
			uint32	uNumberOfPolygons;

			CMeshRawVTN();
			CMeshRawVTN(const CMeshRawVTN& Mesh);

			void	AddVertex(const Math::CVector3D& vPosition, const Math::CVector2D& vTexCoord, const Math::CVector3D& vNormal);
		};

		class GRAPHICTOOLS_API CMeshRawIV{
		public:
			Collection::CList<Math::CVector3D>	Vertices;
			Collection::CList<uint16>			Indices;
			uint32	uNumberOfPolygons;

			CMeshRawIV();
			CMeshRawIV(const CMeshRawIV& Mesh);

			void		Clear();
			const bool	FindVertex(const Math::CVector3D& vPos, uint16& uOutIndex) const;
			void		AddVertex(const Math::CVector3D& vPos);
		};

		class GRAPHICTOOLS_API CMeshRawIVT{
		public:
			Collection::CList<Math::CVector3D>	Vertices;
			Collection::CList<Math::CVector2D>	TexCoords;
			Collection::CList<uint16>			Indices;
			uint32	uNumberOfPolygons;

			CMeshRawIVT();
			CMeshRawIVT(const CMeshRawIVT& Mesh);

			void		Clear();
			const bool	FindVertex(const Math::CVector3D& vPos, const Math::CVector2D& vTexCoord, uint16& uOutIndex) const;
			void		AddVertex(const Math::CVector3D& vPos, const Math::CVector2D& vTexCoord);
		};

		class GRAPHICTOOLS_API CMeshRawIVTN{
		public:
			Collection::CList<Math::CVector3D>	Vertices;
			Collection::CList<Math::CVector2D>	TexCoords;
			Collection::CList<Math::CVector3D>	Normals;
			Collection::CList<uint16>			Indices;
			uint32	uNumberOfPolygons;

			CMeshRawIVTN();
			CMeshRawIVTN(const CMeshRawIVTN& Mesh);

			void		Clear();
			const bool	FindVertex(const Math::CVector3D& vPos, const Math::CVector2D& vTexCoord, const Math::CVector3D& vNormal, uint16& uOutIndex) const;
			void		AddVertex(const Math::CVector3D& vPos, const Math::CVector2D& vTexCoord, const Math::CVector3D& vNormal);
		};
	}
}