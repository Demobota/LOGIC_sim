#ifndef _SWITCH_H
#define _SWITCH_H

#include "Component.h"
#include "OutputPin.h"
#include <fstream>
using namespace std;

class Switch : public Component
{
private:
	OutputPin* m_OutputPin;	// Switch has one output pin
	STATUS m_Status;		// Current status (HIGH = ON, LOW = OFF)
public:
	Switch(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();	// Switch doesn't need to operate, but required by Component
	virtual void Draw(Output* pOut, bool selected = false);
	
	virtual int GetOutPinStatus();	// Returns the switch status
	virtual int GetInputPinStatus(int n);	// Returns -1 (Switch has no input pins)
	virtual void setInputPinStatus(int n, STATUS s);	// Changes switch status (n is ignored)
	
	virtual void save(ofstream& file);
	virtual void load(ifstream& file);
	void set_state(STATUS s);

	// Additional method to toggle switch
	void Toggle();
	
	// Get the output pin for connections
	OutputPin* GetOutputPin() { return m_OutputPin; }
	
	// Destructor
	virtual ~Switch();
};

#endif

