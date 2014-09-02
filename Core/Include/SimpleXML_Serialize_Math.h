#pragma once

#include "Macros.h"
#include "Types.h"
#include "SimpleXML_Serialize.h"
#include "Math_Size2D.h"

namespace CB{
	template<>
	class CXMLSerialize<Math::CSize2D> :
		public SXML::CSerialize<Math::CSize2D>
	{
	public:
		const bool	WriteNode( SXML::CNode& node ) override;
		const bool	ReadNode( const SXML::CNode& node ) override;
	};
}