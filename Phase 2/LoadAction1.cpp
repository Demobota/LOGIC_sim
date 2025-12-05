#include "LoadAction1.h" // Include the new header name
#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

using namespace std;

// CHANGE 4: Scope Resolution (LoadAction1::)
LoadAction1::LoadAction1(ApplicationManager* pApp) : Action(pApp)
{
}

LoadAction1::~LoadAction1(void)
{
}

void LoadAction1::ReadActionParameters()
{
	// ... (Code remains the same) ...
}

void LoadAction1::Execute()
{
	// ... (Code remains the same) ...
}

void LoadAction1::Undo() {}
void LoadAction1::Redo() {}