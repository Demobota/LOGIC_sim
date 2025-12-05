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
#include"Actions\Select.h"
#include"Actions\Delete.h"
#include"Actions\AddLabel.h"
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
		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;
		case SELECT:
			pAct = new Select(this,CompList, CompCount);
			break;
		case DEL:
			pAct = new Delete(this, CompList, &CompCount);
			break;
		case ADD_Label:
			pAct = new AddLabel(this);
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