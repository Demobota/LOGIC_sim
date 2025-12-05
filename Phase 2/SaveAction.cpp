#include "SaveAction.h"
#include "..\Phase 2\ApplicationManager.h"

#include "..\Phase 2\GUI\Input.h"  // <--- ADD THIS
#include "..\Phase 2\GUI\Output.h" // <--- ADD THIS
#include <string> // Added this

using namespace std; // <--- ADD THIS

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp)
{
}

SaveAction::~SaveAction(void)
{
}

void SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Saving: Please type the file name (e.g. myCircuit)...");

	// FIXED TYPO HERE: It is GetString, not GetSrting
	FileName = pIn->GetString(pOut);

	pOut->ClearStatusBar();
}

void SaveAction::Execute()  
{
	ReadActionParameters();

	ofstream OutFile;
	OutFile.open(FileName + ".txt");

	if (OutFile.is_open())
	{
		// IMPORTANT: This line will give an error UNTIL you finish Step 4
		// because SaveAll() doesn't exist in ApplicationManager yet.
		pManager->SaveAll(OutFile);

		OutFile.close();
		pManager->GetOutput()->PrintMsg("Circuit Saved Successfully!");
	}
	else
	{
		pManager->GetOutput()->PrintMsg("Error: Could not create file!");
	}
}

void SaveAction::Undo() {}
void SaveAction::Redo() {}