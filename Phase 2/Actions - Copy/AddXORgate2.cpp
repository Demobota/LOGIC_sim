#include "AddXORgate2.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddXORgate2::AddXORgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddXORgate2::~AddXORgate2(void)
{
}

void AddXORgate2::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("2-Input XOR Gate: Click to add the gate");
	int Len = UI.XOR2_Width;
	int Wdth = UI.XOR2_Height;
	bool validPosition = false;
	do
	{
		pIn->GetPointClicked(Cx, Cy);
		GraphicsInfo temp;
		temp.x1 = Cx - Len / 2;
		temp.y1 = Cy - Wdth / 2;
		temp.x2 = Cx + Len / 2;
		temp.y2 = Cy + Wdth / 2;
		if (temp.y1 < UI.ToolBarHeight || temp.y2 > UI.height - UI.StatusBarHeight)
		{
			pOut->PrintMsg("Invalid position! Cannot place on toolbar or status bar");
			continue;
		}
		if (pManager->IsAreaOccupied(temp))
		{
			pOut->PrintMsg("Cannot place gate on top of another component");
			continue;
		}
		validPosition = true;
	} while (!validPosition);
	pOut->ClearStatusBar();
}

void AddXORgate2::Execute()
{
	ReadActionParameters();
	int Len = UI.XOR2_Width;
	int Wdth = UI.XOR2_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	XOR2 *pA=new XOR2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddXORgate2::Undo()
{}

void AddXORgate2::Redo()
{}
