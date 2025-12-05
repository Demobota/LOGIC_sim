#include "AddORgate2.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

AddORgate2::AddORgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddORgate2::~AddORgate2(void)
{
}

void AddORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input OR Gate: Click to add the gate");
	double y1;
	double y2;
	int Len = UI.OR2_Width;
	int Wdth = UI.OR2_Height;
	bool validPosition = false;
	//Validation to not allow user to place gate at ToolBar or status bar
	do
	{
		pIn->GetPointClicked(Cx, Cy);

		// Calculate rectangle corners of the selected position
		GraphicsInfo temp;
		temp.x1 = Cx - Len / 2;
		temp.y1 = Cy - Wdth / 2;
		temp.x2 = Cx + Len / 2;
		temp.y2 = Cy + Wdth / 2;

		// Check screen boundaries (toolbar/status bar)
		if (temp.y1 < UI.ToolBarHeight || temp.y2 > UI.height - UI.StatusBarHeight)
		{
			pOut->PrintMsg("Invalid position! Cannot place on toolbar or status bar");
			continue;
		}

		// Check overlap with other existing components
		if (pManager->IsAreaOccupied(temp))
		{
			pOut->PrintMsg("Cannot place gate on top of another component");
			continue;
		}

		validPosition = true;

	} while (!validPosition);
	//Clear Status Bar
	pOut->ClearStatusBar();
}

void AddORgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	
	//Calculate the rectangle Corners
	int Len = UI.OR2_Width;
	int Wdth = UI.OR2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the OR2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	OR2 *pA=new OR2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddORgate2::Undo()
{}

void AddORgate2::Redo()
{}
