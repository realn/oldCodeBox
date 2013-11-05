#include "../Internal/Window.h"
#include "../Internal/Manager.h"

CB::Window::IManager*	CreateManager(CB::Window::IDriver* pDriver){
	return new CB::CWindowManager(pDriver);
}