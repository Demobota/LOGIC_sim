#include "AddNORgate2.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddNORgate2::AddNORgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("2-Input NOR Gate: Click to add the gate");
	int Len = UI.NOR2_Width;
	int Wdth = UI.NOR2_Height;
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

void AddNORgate2::Execute()
{
	ReadActionParameters();
	int Len = UI.NOR2_Width;
	int Wdth = UI.NOR2_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	NOR2 *pA=new NOR2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddNORgate2::Undo()
{}

void AddNORgate2::Redo()
{}
