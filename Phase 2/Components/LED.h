#ifndef _LED_H
#define _LED_H

#include "Component.h"
#include "InputPin.h"
#include <fstream>
using namespace std;

class LED : public Component
{
private:
	InputPin m_InputPin;	// LED has one input pin
	STATUS m_Status;		// Current status (HIGH = ON, LOW = OFF)
public:
	LED(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();	// LED updates its status based on input pin
	virtual void Draw(Output* pOut, bool selected = false);
	
	virtual int GetOutPinStatus();	// Returns -1 (LED has no output pin)
	virtual int GetInputPinStatus(int n);	// Returns the LED status
	virtual void setInputPinStatus(int n, STATUS s);	// Sets the input pin status (n is ignored)
	
	virtual void save(ofstream& file);
	virtual void load(ifstream& file);
	
	// Get the input pin for connections
	InputPin* GetInputPin() { return &m_InputPin; }
};

#endif

