#ifndef _ADD_CONECTION_H
#define _ADD_CONECTION_H

#include "Action.h" 


class Add_connection : public Action
{
private:
	int x1, y1; // Source coords
	int x2, y2; // Dest coords

public:
	Add_connection(ApplicationManager* pApp);
	virtual ~Add_connection(void);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif