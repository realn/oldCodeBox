#pragma once

#include "DeviceContextInterface.h"

namespace CB{
	/// <summary>
	/// Interface for shader context interaction.
	/// </summary>
	class IRenderContext{
	public:
		virtual const bool	Bind(const IDeviceContext& Context) = 0;
		virtual void		Unbind() = 0;
		virtual const bool	IsBinded() const = 0;

		virtual void* Get() const = 0;
	};
}