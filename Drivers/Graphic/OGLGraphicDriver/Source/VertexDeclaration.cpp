#include "../Internal/VertexDeclaration.h"
#include "../Internal/Utils.h"

namespace CB{
	COGLVertexDeclaration::COGLVertexDeclaration(CRefPtr<COGLDevice> pDevice, const Collection::ICountable<Graphic::CVertexElement>& Elements) :
		Manage::IManagedObject<COGLDevice, COGLVertexDeclaration>(pDevice)
	{
		this->m_Streams.Resize(this->GetParent()->GetNumberOfStreams());
		for(uint32 uIndex = 0; uIndex < Elements.GetLength(); uIndex++){
			const Graphic::CVertexElement& el = Elements[uIndex];

			if(el.uStream >= this->m_Streams.GetLength()){
				CR_THROW(L"Stream number exceeds max number.");
			}

			CStreamElement stream;

			stream.strParamName = el.strParam;
			stream.uType		= GLUtils::ToVertexType(el.uType);
			stream.uNumber		= GLUtils::ToVertexTypeNumber(el.uType) * el.uTypeNumber;
			stream.uOffset		= el.uOffset;
			stream.uSize		= GLUtils::GetTypeSize(stream.uType) * stream.uNumber;

			this->m_Streams[el.uStream].Elements.Add(stream);
			if(this->m_Streams[el.uStream].uStride < stream.uOffset + stream.uSize){
				this->m_Streams[el.uStream].uStride = stream.uOffset + stream.uSize;
			}
		}

	}

	COGLVertexDeclaration::~COGLVertexDeclaration(){
		
	}

	const CStreamDefinition&	COGLVertexDeclaration::GetStream(const uint32 uStream) const{
		return this->m_Streams[uStream];
	}

	const uint32	COGLVertexDeclaration::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IDevice>	COGLVertexDeclaration::GetDevice() const{
		return this->m_pParent.Cast<Graphic::IDevice>();
	}

	const Collection::CList<Graphic::CVertexElement>	COGLVertexDeclaration::GetElements(CRefPtr<Graphic::IShader> pVertexShader) const{
		CR_THROWNOTIMPLEMENTED();
	}
}