#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
class Select: public Action
{
private:
	int px=0, py=0;	//Point clicked
	Component** Components;
	int countcomp =0;
public:
	Select(ApplicationManager* pApp, Component* comps[], int length=0);
	virtual ~Select(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

