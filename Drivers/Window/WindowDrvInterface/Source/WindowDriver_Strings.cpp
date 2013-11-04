#include "../Include/WindowDriver.h"

namespace CB{
	namespace String{
		const CString ToString(const Window::Style uStyle){
			switch (uStyle)
			{
			case Window::Style::Pure:				return L"Pure";
			case Window::Style::Single:				return L"Single";
			case Window::Style::Sizeable:			return L"Sizeable";
			case Window::Style::SizeableToolWindow:	return L"Sizeable Toolwindow";
			case Window::Style::ToolWindow:			return L"ToolWindow";
			default:
				return L"Style: " + ToHexString(static_cast<uint32>(uStyle));
			}
		}
	}
}