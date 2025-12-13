#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component;

class InputPin : public Pin
{
	Component* pComp;
	bool isConnected; //

public:
	InputPin();
	void setComponent(Component* pCmp);
	Component* getComponent();


	void setConnection(bool status) { isConnected = status; }
	bool getConnectionStatus() { return isConnected; }
};

#endif