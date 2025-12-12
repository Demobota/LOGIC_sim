#include "AddNORgate3.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddNORgate3::AddNORgate3(ApplicationManager *pApp):Action(pApp)
{
}

AddNORgate3::~AddNORgate3(void)
{
}

void AddNORgate3::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("3-Input NOR Gate: Click to add the gate");
	int Len = UI.NOR3_Width;
	int Wdth = UI.NOR3_Height;
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

void AddNORgate3::Execute()
{
	ReadActionParameters();
	int Len = UI.NOR3_Width;
	int Wdth = UI.NOR3_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	NOR3 *pA=new NOR3(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddNORgate3::Undo()
{}

void AddNORgate3::Redo()
{}
