#include "AddBUFFgate.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddBUFFgate::AddBUFFgate(ApplicationManager *pApp):Action(pApp)
{
}

AddBUFFgate::~AddBUFFgate(void)
{
}

void AddBUFFgate::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Buffer Gate: Click to add the gate");
	int Len = UI.BUFF_Width;
	int Wdth = UI.BUFF_Height;
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

void AddBUFFgate::Execute()
{
	ReadActionParameters();
	int Len = UI.BUFF_Width;
	int Wdth = UI.BUFF_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	BUFF *pA=new BUFF(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddBUFFgate::Undo()
{}

void AddBUFFgate::Redo()
{}
