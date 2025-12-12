#include "AddNANDgate2.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddNANDgate2::AddNANDgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddNANDgate2::~AddNANDgate2(void)
{
}

void AddNANDgate2::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("2-Input NAND Gate: Click to add the gate");
	int Len = UI.NAND2_Width;
	int Wdth = UI.NAND2_Height;
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

void AddNANDgate2::Execute()
{
	ReadActionParameters();
	int Len = UI.NAND2_Width;
	int Wdth = UI.NAND2_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	NAND2 *pA=new NAND2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddNANDgate2::Undo()
{}

void AddNANDgate2::Redo()
{}
