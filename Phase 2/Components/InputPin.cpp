#include "InputPin.h"

InputPin::InputPin()
{
	isConnected = false; // 
}

void InputPin::setComponent(Component* pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}