#ifndef _ADD_CONECTION_H
#define _ADD_CONECTION_H

#include "Action.h"
#include "..\Components\Connection.h"

class Add_conection : public Action
{
private:
	int x1, y1;	// Source Pin Coordinates
	int x2, y2;	// Destination Pin Coordinates

public:
	Add_conection(ApplicationManager* pApp);
	virtual ~Add_conection(void);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif