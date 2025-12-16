#pragma once
#include "Action.h"
#include "..\Defs.h"

// Forward declarations
class ApplicationManager;
class Component;

class Move : public Action
{
private:
	int clickX, clickY;		// Point clicked to select component
	int destX, destY;		// Destination point for moving
	Component* selectedComp; // Component to be moved
	GraphicsInfo oldGfxInfo;  // Store old position for undo
	int offsetX, offsetY;   // Store offset for redo
public:
	Move(ApplicationManager* pApp);
	virtual ~Move(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

