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

		if (SrcCmp == NULL || DstCmp == NULL) {
			pManager->GetOutput()->PrintMsg("Error: Please select valid components.");
			return;
		}


		if (SrcCmp == DstCmp) {
			pManager->GetOutput()->PrintMsg("Error: Cannot connect a component to itself.");
			return;
		}

		OutputPin* pSrcPin = NULL;
		InputPin* pDstPin = NULL;
		GraphicsInfo GInfo;

		// ===========================

		if (dynamic_cast<Switch*>(SrcCmp))
			pSrcPin = ((Switch*)SrcCmp)->GetOutputPin();
		else if (dynamic_cast<Gate*>(SrcCmp))
			pSrcPin = ((Gate*)SrcCmp)->GetOutputPin();

		if (pSrcPin != NULL) {
			GraphicsInfo SrcGfx = SrcCmp->GetGFXinfo();
			GInfo.x1 = SrcGfx.x2;
			GInfo.y1 = (SrcGfx.y1 + SrcGfx.y2) / 2;
		}

		// ===========================

		// ===========================
		if (dynamic_cast<LED*>(DstCmp))
		{

			pDstPin = ((LED*)DstCmp)->GetInputPin();
			GraphicsInfo DstGfx = DstCmp->GetGFXinfo();
			GInfo.x2 = DstGfx.x1 + (DstGfx.x2 - DstGfx.x1) / 2;
			GInfo.y2 = DstGfx.y2;
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


			if (ClickOffsetY < GateHeight / 2) {
				PinIndex = 0;
				GInfo.y2 = DstGfx.y1 + 13;
			}
			else {


				if (ClickOffsetY > GateHeight - 15) {
					PinIndex = 2;
					GInfo.y2 = DstGfx.y2 - 13;
				}
				else {
					PinIndex = 1;

					GInfo.y2 = DstGfx.y2 - 13;

				}
			}

			pDstPin = pGate->GetInputPin(PinIndex);


			if (PinIndex == 2 && GInfo.y2 > DstGfx.y2 - 13) {


			}

			GInfo.x2 = DstGfx.x1;
		}

		// ===========================

		// ===========================
		if (pSrcPin != NULL && pDstPin != NULL)
		{
			if (pDstPin->getConnectionStatus() == true)
			{
				pManager->GetOutput()->PrintMsg("Error: This Input Pin is ALREADY Connected!");
			}
			else
			{
				Connection* pConn = new Connection(GInfo, pSrcPin, pDstPin);
				pDstPin->setConnection(true); //
				pManager->AddComponent(pConn);
				pManager->GetOutput()->PrintMsg("Connection Created Successfully!");
			}
		}
		else
		{
			pManager->GetOutput()->PrintMsg("Error: Invalid Connection Points.");
		}
		
}

void Add_connection::Undo() {}
void Add_connection::Redo() {}
