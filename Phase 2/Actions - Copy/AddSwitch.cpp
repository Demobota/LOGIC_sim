#include "AddSwitch.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddSwitch::AddSwitch(ApplicationManager *pApp) : Action(pApp)
{
}

AddSwitch::~AddSwitch(void)
{
}

void AddSwitch::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Switch: Click to add the switch");
	int Len = UI.Switch_Width;
	int Wdth = UI.Switch_Height;
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
			pOut->PrintMsg("Cannot place switch on top of another component");
			continue;
		}
		validPosition = true;
	} while (!validPosition);
	pOut->ClearStatusBar();
}

void AddSwitch::Execute()
{
	ReadActionParameters();
	int Len = UI.Switch_Width;
	int Wdth = UI.Switch_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	Switch *pA = new Switch(GInfo);
	pManager->AddComponent(pA);
}

void AddSwitch::Undo()
{}

void AddSwitch::Redo()
{}

