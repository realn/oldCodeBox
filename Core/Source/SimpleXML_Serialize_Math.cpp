#include "stdafx.h"
#include "../Include/SimpleXML_Serialize_Math.h"
#include "../Include/SimpleXML.h"

namespace CB{
	const bool	CXMLSerialize<Math::CSize2D>::WriteNode( SXML::CNode& node ){
		node.SetAttributeValue( L"Width", String::ToString( this->m_Object.Width ) );
		node.SetAttributeValue( L"Height", String::ToString( this->m_Object.Height ) );

		return true;
	}

	const bool	CXMLSerialize<Math::CSize2D>::ReadNode( const SXML::CNode& node ){
		this->m_Object.Width = String::ToUInt32( node.Attributes[L"Width"].GetValue() );
		this->m_Object.Width = String::ToUInt32( node.Attributes[L"Height"].GetValue() );

		return true;
	}
}