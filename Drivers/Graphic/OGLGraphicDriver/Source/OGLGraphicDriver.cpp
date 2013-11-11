#include "../Include/OGLGraphicDriver.h"
#include "../Internal/Manager.h"

CB::Graphic::IManager*	CreateManager(CB::Graphic::IDriver* pDriver, CB::Window::IManager* pManager){
	return new CB::COGLManager(pDriver, pManager);
}