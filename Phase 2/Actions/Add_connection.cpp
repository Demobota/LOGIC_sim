#include "Add_connection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"
Add_connection::Add_connection(ApplicationManager* pApp) :Action(pApp)
{
}

Add_connection::~Add_connection(void)
{
}

void Add_connection::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Add Connection: Click on the SOURCE component (Output Pin)");
	pIn->GetPointClicked(x1, y1);
	pOut->ClearStatusBar();

	pOut->PrintMsg("Add Connection: Click on the DESTINATION Input Pin");
	pIn->GetPointClicked(x2, y2);
	pOut->ClearStatusBar();
}

void Add_connection::Execute()
{
	ReadActionParameters();

	Component* SrcCmp = pManager->GetComponent(x1, y1);
	Component* DstCmp = pManager->GetComponent(x2, y2);

	if (SrcCmp != NULL && DstCmp != NULL)
	{
		OutputPin* pSrcPin = NULL;
		InputPin* pDstPin = NULL;

		// 1. Get Source Pin
		if (dynamic_cast<Switch*>(SrcCmp))
			pSrcPin = ((Switch*)SrcCmp)->GetOutputPin();
		else if (dynamic_cast<Gate*>(SrcCmp))
			pSrcPin = ((Gate*)SrcCmp)->GetOutputPin();

		// 2. Get Destination Pin (Smart Logic)
		if (dynamic_cast<LED*>(DstCmp))
			pDstPin = ((LED*)DstCmp)->GetInputPin();
		else if (dynamic_cast<Gate*>(DstCmp))
		{
			Gate* pGate = (Gate*)DstCmp;
			GraphicsInfo GInfo = pGate->GetGFXinfo();
			int ClickOffsetY = y2 - GInfo.y1;
			int GateHeight = GInfo.y2 - GInfo.y1;

			// Decide Pin based on click height (Top half -> Pin 0, Bottom half -> Pin 1)
			int PinIndex = (ClickOffsetY > GateHeight / 2) ? 1 : 0;
			pDstPin = pGate->GetInputPin(PinIndex);
		}

		// 3. Create Connection
		if (pSrcPin != NULL && pDstPin != NULL)
		{
			GraphicsInfo GInfo;
			GInfo.x1 = x1; GInfo.y1 = y1;
			GInfo.x2 = x2; GInfo.y2 = y2;
			Connection* pConn = new Connection(GInfo, pSrcPin, pDstPin);
			pManager->AddComponent(pConn);
			pManager->GetOutput()->PrintMsg("Connection Created Successfully!");
		}
		else
		{
			pManager->GetOutput()->PrintMsg("Error: Invalid Connection Points.");
		}
	}
	else
	{
		pManager->GetOutput()->PrintMsg("Error: Select valid components.");
	}
}

void Add_connection::Undo() {}
void Add_connection::Redo() {}
