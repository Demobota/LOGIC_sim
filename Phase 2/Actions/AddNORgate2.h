#ifndef _ADD_NOR_GATE_2_H
#define _ADD_NOR_GATE_2_H

#include "Action.h"
#include "..\Components\NOR2.h"

class AddNORgate2 :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddNORgate2(ApplicationManager *pApp);
	virtual ~AddNORgate2(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif
