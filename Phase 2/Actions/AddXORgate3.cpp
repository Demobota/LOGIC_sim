#include "AddXORgate3.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddXORgate3::AddXORgate3(ApplicationManager *pApp):Action(pApp)
{
}

AddXORgate3::~AddXORgate3(void)
{
}

void AddXORgate3::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("3-Input XOR Gate: Click to add the gate");
	int Len = UI.XOR3_Width;
	int Wdth = UI.XOR3_Height;
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

void AddXORgate3::Execute()
{
	ReadActionParameters();
	int Len = UI.XOR3_Width;
	int Wdth = UI.XOR3_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	XOR3 *pA=new XOR3(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddXORgate3::Undo()
{}

void AddXORgate3::Redo()
{}
