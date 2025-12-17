#include "Delete.h"

Delete::Delete(ApplicationManager* pApp, Component* compList[], int* length)
	: Action(pApp), Components(compList), countcomp(length)
{
	// Validate consistency between pointer and length
	if (compList == nullptr || length == nullptr)
	{
		Components = nullptr;
		countcomp = nullptr;
	}

	deletedCount = 0;
}

Delete::~Delete() {}

void Delete::ReadActionParameters()
{
	if (Components == nullptr || countcomp == nullptr || *countcomp <= 0)
		return;

	Output* pOut = pManager->GetOutput();

	for (int i = *countcomp - 1; i >= 0; i--)
	{
		if (Components[i] && Components[i]->GetSelect())
		{
			GraphicsInfo ginfo = Components[i]->GetGFXinfo();
			pOut->whiteBox(ginfo.x1 - 5, ginfo.y1 - 5,
				ginfo.x2 + 5, ginfo.y2 + 5);
			pManager->RemoveComponent(Components[i]);

			deletedCount++;
		}
	}
}


void Delete::Execute() {
	//Get clicked point
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	// Validate pointers before proceeding
	if (deletedCount > 0) {
		 // Redraw everything
		pOut->PrintMsg("Deleted " + to_string(deletedCount) + " component(s)");
	}
	else {
		pOut->PrintMsg("No components selected to delete");
	}
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}