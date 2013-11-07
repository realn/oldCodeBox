#include "../Include/OGLGraphicDriver.h"
#include "../Internal/Manager.h"

CB::Graphic::IManager*	CreateManager(CB::Graphic::IDriver* pDriver){
	return new CB::COGLManager(pDriver);
}