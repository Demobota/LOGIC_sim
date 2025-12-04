#include "Delete.h"
#include "ApplicationManager.h"

// Read parameters required for delete (e.g., which component/connection to delete)
void Delete::ReadActionParameters()
{
    // TODO: implement parameter reading (use pManager->GetInput() etc.)
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Delete: Click to delete the gate");

	//Wait for User Input
	pIn->GetPointClicked(P1, P2);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

// Execute the delete action
void Delete::Execute()
{
    
   
}

// Undo the delete action
void Delete::Undo()
{
    // TODO: restore deleted component/connection
}

// Redo the delete action
void Delete::Redo()
{
    // TODO: re-apply the delete if needed
}
