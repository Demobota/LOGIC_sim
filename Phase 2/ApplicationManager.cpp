#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddINVgate.h"
#include "Actions\AddBUFFgate.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddLED.h"
#include"Actions\Select.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction1.h"
#include "Actions\SimulationModeAction.h"
#include"Actions\Add_connection.h"
#include "Actions\TruthTable.h"

// Component includes for LoadAll
#include "Components\AND2.h"
#include "Components\AND3.h"
#include "Components\OR2.h"
#include "Components\NAND2.h"
#include "Components\NOR2.h"
#include "Components\NOR3.h"
#include "Components\XOR2.h"
#include "Components\XOR3.h"
#include "Components\XNOR2.h"
#include "Components\INV.h"
#include "Components\BUFF.h"
#include "Components\Label.h"
#include "Components\Switch.h"
#include "Components\LED.h"

////////////////////////////////////////////////////////////////////

#include"Actions\Delete.h"
#include"Actions\AddLabel.h"
#include"Actions\EditLabel.h"
#include"Actions\Move.h"
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

Component* ApplicationManager::GetComponent(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		GraphicsInfo GInfo = CompList[i]->GetGFXinfo();
		if (x >= GInfo.x1 && x <= GInfo.x2 && y >= GInfo.y1 && y <= GInfo.y2)
		{
			return CompList[i];
		}
	}
	return NULL;
}

Component* ApplicationManager::GetComponentByIndex(int index) const
{
	if (index >= 0 && index < CompCount)
		return CompList[index];
	return NULL;
}
///////////////////////////////////////////////////////////////////


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
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(this);
			break;
		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(this);
			break;
		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;
		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(this);
			break;
		case ADD_INV:
			pAct = new AddINVgate(this);
			break;
		case ADD_Buff:
			pAct = new AddBUFFgate(this);
			break;
		case ADD_Switch:
			pAct = new AddSwitch(this);
			break;
		case ADD_LED:
			pAct = new AddLED(this);
			break;
		case ADD_CONNECTION:
			pAct = new Add_connection(this);
			//TODO: Create AddConection Action here
			break;
		case SELECT:
			pAct = new Select(this,CompList, CompCount);
			break;
		case SIM_MODE: // osama tamer
			pAct = new SimulationModeAction(this);
			break;

		case DEL:
			pAct = new Delete(this, CompList, &CompCount);
			break;
		case MOVE:
			pAct = new Move(this);
			break;
		case ADD_Label:
			pAct = new AddLabel(this);
			break;
		case EDIT_Label:
			pAct = new EditLabel(this);
			break;
		case EXIT:
			///TODO: create ExitAction here
			break;
		case SAVE:
			pAct = new SaveAction(this);
			break;
		case UNDO:
			pAct = new LoadAction1(this);
			break;
		// osama tamer, note: lesa ha3mel el classes btoo3 el sim mode ba3den
		case RUN_SIM:
			UpdateSimulation();
			break;
	    case Step:
            OutputInterface->PrintMsg("step button clicked");
			break;
		case Reset:
			OutputInterface->PrintMsg("reset button clicked");
			break;
		case Create_TruthTable:
			pAct = new TruthTable(this);
			break;
		case PROBE:
			OutputInterface->PrintMsg("probe button clicked");
			break;
		case Change_Switch:
		{
			// Get the click position
			int x, y;
			InputInterface->GetPointClicked(x, y);
			// Try to toggle a switch at the clicked position
			if (!ToggleSwitch(x, y))
			{
				// If no switch was toggled, show a message
				OutputInterface->PrintMsg("Click on a switch to toggle it");
			}
			break;
		}
		case Simulate:
			OutputInterface->PrintMsg("simulation button clicked");
            break;
		case DSN_MODE:
			OutputInterface->PrintMsg("exiting simulation mode...");
			OutputInterface->ClearDrawingArea(); // b yesheel el simulation toolbar
			UI.AppMode = DESIGN;
			break;
		

	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
bool ApplicationManager::IsAreaOccupied(GraphicsInfo newGate)
{
	for (int i = 0; i < CompCount; i++)
	{
		GraphicsInfo oldGate = CompList[i]->GetGFXinfo();

		bool overlapX = !(newGate.x2 < oldGate.x1 || newGate.x1 > oldGate.x2);
		bool overlapY = !(newGate.y2 < oldGate.y1 || newGate.y1 > oldGate.y2);

		if (overlapX && overlapY)
			return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{	
	for (int i = 0; i < CompCount; i++) 
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
			CompList[i]->save(outputfile);
		}
	}
}

// ApplicationManager.cpp inside LoadAll loop
// In ApplicationManager.cpp

// --- Add this at the very end of ApplicationManager.cpp ---

int ApplicationManager::GetCompCount() const
{
	return CompCount;
}

Component* const* ApplicationManager::GetCompList() const
{
	return CompList;
}

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
			pComp = new AND2(DummyGfx, 5);
		}
		else if (CompType == "AND3")
		{
			pComp = new AND3(DummyGfx, 5);
		}
		else if (CompType == "OR2")
		{
			pComp = new OR2(DummyGfx, 5);
		}
		else if (CompType == "NAND2")
		{
			pComp = new NAND2(DummyGfx, 5);
		}
		else if (CompType == "NOR2")
		{
			pComp = new NOR2(DummyGfx, 5);
		}
		else if (CompType == "NOR3")
		{
			pComp = new NOR3(DummyGfx, 5);
		}
		else if (CompType == "XOR2")
		{
			pComp = new XOR2(DummyGfx, 5);
		}
		else if (CompType == "XOR3")
		{
			pComp = new XOR3(DummyGfx, 5);
		}
		else if (CompType == "XNOR2")
		{
			pComp = new XNOR2(DummyGfx, 5);
		}
		else if (CompType == "INV")
		{
			pComp = new INV(DummyGfx, 5);
		}
		else if (CompType == "BUFF")
		{
			pComp = new BUFF(DummyGfx, 5);
		}
		else if (CompType == "LABEL")
		{
			pComp = new Label(DummyGfx, "");
		}
		else if (CompType == "SWITCH")
		{
			pComp = new Switch(DummyGfx);
		}
		else if (CompType == "LED")
		{
			pComp = new LED(DummyGfx);
		}

		// --- E. LOADING ---
		// If we successfully created a component, tell it to load its own data
		if (pComp != NULL)
		{
			pComp->load(inputfile); // This reads x, y, label from the file (component-specific)
			AddComponent(pComp);    // Add it to the Application Manager's list
		}
		else
		{
			// Unknown component type: try to recover by skipping its data line(s).
			// This helps avoid getting stuck if file contains unsupported types.
		}
	}
}



bool ApplicationManager::ToggleSwitch(int x, int y)
{
	// Get the component at the clicked position
	Component* pComp = GetComponent(x, y);
	if (pComp != nullptr)
	{
		// Try to cast to Switch
		Switch* pSwitch = dynamic_cast<Switch*>(pComp);
		if (pSwitch != nullptr)
		{
			// Toggle the switch
			pSwitch->Toggle();
			
			// Update the simulation to reflect the change
			UpdateSimulation();
			UpdateInterface();
			
			// Log the action
			OutputInterface->PrintMsg("Switch toggled: " + string(pSwitch->GetOutPinStatus() == HIGH ? "ON" : "OFF"));
			return true;
		}
	}
	return false;
}

void ApplicationManager::UpdateSimulation()
{
	// Loop multiple times to ensure signal propagation across cascaded gates
	for (int repeat = 0; repeat < 5; repeat++)
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] != NULL)
			{
				CompList[i]->Operate();
			}
		}
	}
}
void ApplicationManager::RemoveComponent(Component* pComp)
{
	if (!pComp) return;

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == pComp)
		{
			delete CompList[i];

			CompList[i] = CompList[CompCount - 1];
			CompList[CompCount - 1] = nullptr;
			CompCount--;

			return;
		}
	}
}
