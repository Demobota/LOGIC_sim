#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include"Actions\Select.h"
#include "SaveAction.h"
#include "loadAction1.h"

////////////////////////////////////////////////////////////////////

ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);	
			break;

		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;
		case SELECT:
			pAct = new Select(this,CompList, CompCount);
			break;
		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(OutputInterface, CompList[i]->GetSelect());

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}

void ApplicationManager::SaveAll(ofstream& outputfile)
{
	// 1. Write how many components we have (so we know how many to load later)
	outputfile << CompCount << endl;

	// 2. Loop through the list and tell everyone to save themselves
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			CompList[i]->save(outputfile); // This calls the AND2::save you just wrote!
		}
	}
}

// ApplicationManager.cpp inside LoadAll loop
// In ApplicationManager.cpp

// Change "ofstream" to "ifstream" 
// In ApplicationManager.cpp

// 1. Change ofstream to ifstream (Input)
void ApplicationManager::LoadAll(ifstream& inputfile) 
{
	// --- A. CLEANUP: Delete old components before loading new ones ---
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i])
		{
			delete CompList[i];
			CompList[i] = NULL;
		}
	}
	CompCount = 0;

	// --- B. SETUP VARIABLES ---
	int Count = 0;
	inputfile >> Count; // Read the number of components from the top of the file

	string CompType;
	GraphicsInfo DummyGfx; // A temp variable needed to create objects
	DummyGfx.x1 = 0; DummyGfx.y1 = 0; DummyGfx.x2 = 0; DummyGfx.y2 = 0;

	// --- C. LOOP AND CREATE ---
	for (int i = 0; i < Count; i++)
	{
		inputfile >> CompType; // Read the type (e.g., "AND2")

		Component* pComp = NULL;

		// --- D. FACTORY LOGIC ---
		if (CompType == "AND2")
		{
			// Create the object (AND2_FANOUT is usually 5, defined in Defs.h or just use 5)
			pComp = new AND2(DummyGfx, 5);
		}
		else if (CompType == "OR2")
		{
			// pComp = new OR2(DummyGfx, 5);
		}
		// ... Add other gates here ...


		// --- E. LOADING ---
		// If we successfully created a component, tell it to load its own data
		if (pComp != NULL)
		{
			pComp->load(inputfile); // This reads x, y, label from the file
			AddComponent(pComp);    // Add it to the Application Manager's list
		}
	}
}

