#ifndef _AND3_H
#define _AND3_H

#include "Gate.h"

class AND3:public Gate
{
public:
	AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();
	virtual void Draw(Output* pOut,bool selected=false);
	virtual int GetOutPinStatus();
	virtual int GetInputPinStatus(int n);
	virtual void setInputPinStatus(int n, STATUS s);
};

#endif
