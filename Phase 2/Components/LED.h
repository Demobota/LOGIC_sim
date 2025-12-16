#ifndef _LED_H
#define _LED_H

#include "Component.h"
#include "InputPin.h"
#include <fstream>
using namespace std;

class LED : public Component
{
private:
	InputPin m_InputPin;
	STATUS m_Status;
public:
	LED(const GraphicsInfo& r_GfxInfo);
	virtual void Operate();
	virtual void Draw(Output* pOut, bool selected = false);

	virtual int GetOutPinStatus();
	virtual int GetInputPinStatus(int n);

	// --- FIX: Added "STATUS s" to match the Component base class ---
	virtual void setInputPinStatus(int n, STATUS s);

	virtual void save(ofstream& file);
	virtual void load(ifstream& file);

	InputPin* GetInputPin() { return &m_InputPin; }
};

#endif