#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
class Delete :
	public Action
{	
	Component** Components;
	int *countcomp;
	int x1, y1, x2, y2;//coordinates of object to delete
	int deletedCount;
	public:

	virtual void ReadActionParameters();
	Delete(ApplicationManager* pApp, Component* comps[], int *length);
	virtual ~Delete();
	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

