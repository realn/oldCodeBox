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

		const CString	ToString(const Window::VirtualKey uKey){
			switch (uKey)
			{
			#define CR_DEFVK(_KEY,B)	case Window::VirtualKey::_KEY:	return L#_KEY;
			#include "../Include/VirtualKeys.incl"
			#undef CR_DEFVK
			default:
				return L"Undefined";
			}
		}

		const Window::VirtualKey	FromString(const CString& strKey){
			#define CR_DEFVK(_KEY, B)	if(strKey == L#_KEY) return Window::VirtualKey::_KEY;
			#include "../Include/VirtualKeys.incl"
			#undef CR_DEFVK
			return Window::VirtualKey::Undefined;
		}
	}
}