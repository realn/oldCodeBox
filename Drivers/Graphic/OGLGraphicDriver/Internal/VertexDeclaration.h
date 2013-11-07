#pragma once

#include "Device.h"

namespace CB{
	class CStreamElement{
	public:
		CString	strParamName;
		GLenum	uType;
		uint32	uNumber;
		uint32	uSize;
		uint32	uOffset;
	};

	class CStreamDefinition{
	public:
		Collection::CList<CStreamElement>	Elements;
		uint32	uStride;
	};

	class COGLVertexDeclaration : 
		public Graphic::IVertexDeclaration,
		public Manage::IManagedObject<COGLDevice, COGLVertexDeclaration>
	{
	private:
		Collection::CList<CStreamDefinition>	m_Streams;

	public:
		COGLVertexDeclaration(CRefPtr<COGLDevice> pDevice, const Collection::ICountable<Graphic::CVertexElement>& Elements);
		~COGLVertexDeclaration();

		const CStreamDefinition&	GetStream(const uint32 uStream) const;

		const uint32	GetApiId() const override;

		CRefPtr<Graphic::IDevice>	GetDevice() const override;
		
		const Collection::CList<Graphic::CVertexElement>	GetElements(CRefPtr<Graphic::IShader> pVertexShader) const override;
	};
}