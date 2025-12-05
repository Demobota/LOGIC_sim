#pragma once
#include "Component.h"
#include<string>
class Label :
    public Component
{	//The parameters required to draw a component
	string label ="";
public:
	Label(const GraphicsInfo& r_GfxInfo,string label);
	virtual void Operate() {}	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut, bool selected = false);	//for each component to Draw itself
	virtual int GetOutPinStatus() { return -99; }//invalid in label	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n) { return -99; }//irrelevant in label	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s) {}//invalid ib label	//set status of Inputpin # n, to be used by connection class.

	virtual void save(std::ofstream& file) override;
	virtual void load(std::ifstream& file) override;

	Label() : Component(GraphicsInfo{ 0,0,0,0 }) {}

	//Destructor must be virtual
	virtual ~Label();
};

