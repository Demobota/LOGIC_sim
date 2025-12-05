#include "AddANDgate2.h"
#include "..\ApplicationManager.h"
//delete after testing is done
#include <iostream>
using namespace std;
AddANDgate2::AddANDgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddANDgate2::~AddANDgate2(void)
{
}


void AddANDgate2::ReadActionParameters() // 5/12/2025 09:13 PM by Os
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message

	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");
	double y1;
	double y2;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
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

void AddANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	AND2 *pA=new AND2(GInfo, AND2_FANOUT); 
	pManager->AddComponent(pA);
}

void AddANDgate2::Undo()
{}

void AddANDgate2::Redo()
{}

