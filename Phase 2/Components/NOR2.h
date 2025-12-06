#ifndef _NOR2_H
#define _NOR2_H

#include "Gate.h"

class NOR2:public Gate
{
public:
	NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();
	virtual void Draw(Output* pOut,bool selected=false);
	virtual int GetOutPinStatus();
	virtual int GetInputPinStatus(int n);
	virtual void setInputPinStatus(int n, STATUS s);
	virtual void save(ofstream& file);
	virtual void load(ifstream& file);
};

#endif
