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

void Add_connection::Execute() {
	ReadActionParameters();
	Component* SrcCmp = pManager->GetComponent(x1, y1);
	Component* DstCmp = pManager->GetComponent(x2, y2);
	// Basic Validation
	if (SrcCmp == NULL || DstCmp == NULL || SrcCmp == DstCmp) {
		pManager->GetOutput()->PrintMsg("Error: Invalid Connection.");
		return;
	}
	OutputPin* pSrcPin = NULL;
	InputPin* pDstPin = NULL;
	GraphicsInfo GInfo;
	// 1. Source Logic (Standard)
	if (dynamic_cast<Switch*>(SrcCmp))
		pSrcPin = ((Switch*)SrcCmp)->GetOutputPin();
	else if (dynamic_cast<Gate*>(SrcCmp))
		pSrcPin = ((Gate*)SrcCmp)->GetOutputPin();

	if (pSrcPin != NULL) {
		GraphicsInfo SrcGfx = SrcCmp->GetGFXinfo();
		GInfo.x1 = SrcGfx.x2;
		GInfo.y1 = (SrcGfx.y1 + SrcGfx.y2) / 2;
	}

	// ====================================================
	// 2. Destination Logic (The Fix for 3-Inputs)
	// ====================================================
	if (dynamic_cast<LED*>(DstCmp))
	{
		pDstPin = ((LED*)DstCmp)->GetInputPin();
		GraphicsInfo DstGfx = DstCmp->GetGFXinfo();

		GInfo.x2 = DstGfx.x1;
		GInfo.y2 = (DstGfx.y1 + DstGfx.y2) / 2;
	}
	else if (dynamic_cast<Gate*>(DstCmp))
	{
		Gate* pGate = (Gate*)DstCmp;
		GraphicsInfo DstGfx = pGate->GetGFXinfo();
		int GateHeight = DstGfx.y2 - DstGfx.y1;
		int ClickOffsetY = y2 - DstGfx.y1;
		int PinIndex = 0;

		// Determine Pin Index based on Click Position
		int InputsCount = pGate->GetInputsCount();

		if (InputsCount == 3)
		{

			if (ClickOffsetY < GateHeight / 3) {
				PinIndex = 0; // Top
				GInfo.y2 = DstGfx.y1 + 13;
			}
			else if (ClickOffsetY > (GateHeight * 2) / 3) {
				PinIndex = 2; // Bottom
				GInfo.y2 = DstGfx.y2 - 13;
			}
			else {
				PinIndex = 1; // Middle
				GInfo.y2 = (DstGfx.y1 + DstGfx.y2) / 2;
			}
		}
		else // Default (2 Inputs)
		{

			if (ClickOffsetY < GateHeight / 2) {
				PinIndex = 0; // Top
				GInfo.y2 = DstGfx.y1 + 13;
			}
			else {
				PinIndex = 1; // Bottom
				GInfo.y2 = DstGfx.y2 - 13;
			}
		}

		// تحديد الـ Pin
		pDstPin = pGate->GetInputPin(PinIndex);
		GInfo.x2 = DstGfx.x1;
	}

	// 3. Create Connection
	if (pSrcPin != NULL && pDstPin != NULL)
	{
		if (pDstPin->getConnectionStatus())
		{
			pManager->GetOutput()->PrintMsg("Error: Pin is ALREADY Connected!");
		}
		else
		{
			Connection* pConn = new Connection(GInfo, pSrcPin, pDstPin);
			pDstPin->setConnection(true);
			pManager->AddComponent(pConn);
			pManager->GetOutput()->PrintMsg("Connection Created!");

			// Refresh Simulation immediately
			
		}
	}
}

void Add_connection::Undo() {}
void Add_connection::Redo() {}
