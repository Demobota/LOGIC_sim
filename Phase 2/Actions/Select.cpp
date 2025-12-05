#include "Select.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

Select::Select(ApplicationManager* pApp, Component* compList[],int length)
	: Action(pApp), Components(compList),countcomp(length)
{
	// Validate consistency between pointer and length
	if (compList == nullptr && length > 0) {
		countcomp = 0;
	}
}

Select::~Select(void)
{
}

void Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	pOut->PrintMsg("Click again on same component ");
	Input* pIn = pManager->GetInput();
	//Validation to not allow user to select non gates
	do {
		//Wait for User Input
		pIn->GetPointClicked(px, py);
	} while (py < UI.ToolBarHeight || py >= UI.height - UI.StatusBarHeight);
	pOut->ClearStatusBar();
}

void Select::Execute()
{	//Get clicked point
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	
	// Validate pointers before proceeding
	if (Components == nullptr || countcomp <= 0) {
		return;
	}
	
	
	
	
	
	// Then find and select the clicked component
	for (int i = 0; i < countcomp; i++) {
		if (Components[i] != nullptr) {
			GraphicsInfo ginfo = Components[i]->GetGFXinfo();
			if ((ginfo).x1 <= px && (ginfo).x2 >= px && (ginfo).y1 <= py && (ginfo).y2 >= py) {
				// Update component's internal selection state
				Components[i]->SetSelect();
				if (Components[i]->GetSelect()) {
					pOut->PrintMsg("Selected a component");
				}
				else {
					pOut->PrintMsg("Deselected a component");
				}
				break;  // Only select one component
			}
		}
	}
}

void Select::Undo()
{
}

void Select::Redo()
{
}