#include "AddLED.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddLED::AddLED(ApplicationManager *pApp) : Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("LED: Click to add the LED");
	int Len = UI.LED_Width;
	int Wdth = UI.LED_Height;
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
			pOut->PrintMsg("Cannot place LED on top of another component");
			continue;
		}
		validPosition = true;
	} while (!validPosition);
	pOut->ClearStatusBar();
}

void AddLED::Execute()
{
	ReadActionParameters();
	int Len = UI.LED_Width;
	int Wdth = UI.LED_Height;
	GraphicsInfo GInfo;
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	LED *pA = new LED(GInfo);
	pManager->AddComponent(pA);
}

void AddLED::Undo()
{}

void AddLED::Redo()
{}

