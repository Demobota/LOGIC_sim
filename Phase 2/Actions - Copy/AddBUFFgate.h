#ifndef _ADD_BUFF_GATE_H
#define _ADD_BUFF_GATE_H

#include "Action.h"
#include "..\Components\BUFF.h"

class AddBUFFgate :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddBUFFgate(ApplicationManager *pApp);
	virtual ~AddBUFFgate(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif
