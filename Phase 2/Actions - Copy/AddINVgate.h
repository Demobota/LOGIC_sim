#ifndef _ADD_INV_GATE_H
#define _ADD_INV_GATE_H

#include "Action.h"
#include "..\Components\INV.h"

class AddINVgate :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddINVgate(ApplicationManager *pApp);
	virtual ~AddINVgate(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif
