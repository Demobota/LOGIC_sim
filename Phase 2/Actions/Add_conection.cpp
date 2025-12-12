#include "Actions\Add_conection.h"
#include "ApplicationManager.h"
#include "Components\Gate.h" // If you have a Gate class for dynamic_cast

Add_conection::Add_conection(ApplicationManager* pApp) :Action(pApp)
{
}

Add_conection::~Add_conection(void)
{
}

void Add_conection::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// 1. Get Source Component
	pOut->PrintMsg("Action: Add Connection. Click on the SOURCE component");
	pIn->GetPointClicked(x1, y1);

	// 2. Get Destination Component
	pOut->PrintMsg("Action: Add Connection. Click on the DESTINATION component");
	pIn->GetPointClicked(x2, y2);

	pOut->ClearStatusBar();
}

void Add_conection::Execute()
{
	ReadActionParameters();

	// 3. Find the components (Requires ApplicationManager::GetComponent)
	Component* SrcCmp = pManager->GetComponent(x1, y1);
	Component* DstCmp = pManager->GetComponent(x2, y2);

	// 4. Validation: Check if valid components were clicked
	if (SrcCmp != NULL && DstCmp != NULL)
	{
		// Try to get OutputPin from SrcCmp and InputPin from DstCmp
		OutputPin* pSrcPin = nullptr;
		InputPin* pDstPin = nullptr;

		// Try dynamic_cast to Gate (or your actual gate class) to access pins
		// If you have a base class for all gates, use it here
		// Otherwise, you may need to add virtual getters to Component

		// Example assuming Component has GetOutputPin() and GetInputPin()
		if (SrcCmp != nullptr)
		{
			pSrcPin = SrcCmp->GetOutputPin();
		}
		if (DstCmp != nullptr)
		{
			pDstPin = DstCmp->GetInputPin();
		}

		if (pSrcPin != nullptr && pDstPin != nullptr)
		{
			GraphicsInfo GInfo;
			GInfo.x1 = x1; GInfo.y1 = y1;
			GInfo.x2 = x2; GInfo.y2 = y2;

			Connection* pConn = new Connection(GInfo, pSrcPin, pDstPin);
			pManager->AddComponent(pConn);
		}
		else
		{
			pManager->GetOutput()->PrintMsg("Error: Could not get pins from selected components.");
		}
	}
	else
	{
		pManager->GetOutput()->PrintMsg("Error: Connection needs two valid components.");
	}
}

void Add_conection::Undo()
{
}

void Add_conection::Redo()
{
}