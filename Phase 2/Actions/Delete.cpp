#include "Delete.h"



Delete::Delete(ApplicationManager* pApp, Component* compList[], int *length)
	: Action(pApp), Components(compList), countcomp(length)
{
	// Validate consistency between pointer and length
	if (compList == nullptr && *length > 0) {
		*countcomp = 0;
	}
}
Delete::~Delete() {}
void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	if (Components == nullptr || *countcomp <= 0) {
		return;
	}
	
	for (int i = 0; i < *countcomp; i++) {
		if (Components[i]->GetSelect()) {
			
			GraphicsInfo ginfo = Components[i]->GetGFXinfo();
			x1 = ginfo.x1;
			y1 = ginfo.y1;
			y2 = ginfo.y2;
			x2 = ginfo.x2;
			if ((*countcomp - 1) != i) {
				
				delete Components[i];
				Components[i] = Components[*countcomp - 1];
				Components[*countcomp - 1] = nullptr;
				
			}else{ delete Components[i]; Components[*countcomp - 1] = nullptr;
			}
			break;  // Only select one component
		}
	}
	//Validation to not allow user to select non gates
	
}
void Delete::Execute() {	//Get clicked point
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	(*countcomp)--;
	// Validate pointers before proceeding
	
	pOut->whiteBox(x1, y1,x2,y2);
	pOut->PrintMsg("component deleted");


}
void Delete::Undo()
{
}

void Delete::Redo()
{
}

