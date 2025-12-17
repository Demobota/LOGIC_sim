#pragma once
#include "Action.h"

class TruthTable : public Action
{	
	public:
	TruthTable(ApplicationManager *pApp);
		virtual ~TruthTable(void);
		//Reads parameters required for action to execute
		virtual void ReadActionParameters();
		//Execute action (code depends on action type)
		virtual void Execute();
		//To undo this action (code depends on action type)
		virtual void Undo();
		//To redo this action (code depends on action type)
		virtual void Redo();
		// Sets the output pin to HIGH or LOW
};