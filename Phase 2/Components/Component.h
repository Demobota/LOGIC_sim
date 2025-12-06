#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include <string>
#include <fstream>

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
	bool selected = false;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut,bool selected =false) = 0;	//for each component to Draw itself
	GraphicsInfo GetGFXinfo();//to get gfx info for select//new;
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	void SetSelect();//added by  A
	bool GetSelect();//added by A
	virtual void save(ofstream& file) = 0; //save function
	virtual void load(ifstream& file) = 0; //load function
	//set and get label
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	string GetLabel() { return m_Label; } // <--- Add this line
	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif