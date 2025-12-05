#ifndef _ADD_NAND_GATE_2_H
#define _ADD_NAND_GATE_2_H

#include "Action.h"
#include "..\Components\NAND2.h"

class AddNANDgate2 :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddNANDgate2(ApplicationManager *pApp);
	virtual ~AddNANDgate2(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif
