#include "AddANDgate2.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;
AddANDgate2::AddANDgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message

	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");
	double y1;
	double y2;
	//Wait for User Input
	int Wdth = UI.AND2_Height;
	do {
		pIn->GetPointClicked(Cx, Cy);
		y1 = Cy - Wdth / 2;
		y2 = Cy + Wdth / 2;
		cout << y1 << " " << UI.height - UI.StatusBarHeight<<endl;
		cout << y2 << " " << UI.ToolBarHeight<<endl;
		cout << "goa"<<endl;
		cout << (y2 < UI.ToolBarHeight) << " " << (y1 >= UI.height - UI.StatusBarHeight) <<endl;
	} while (y1 < UI.ToolBarHeight || y2 >= UI.height - UI.StatusBarHeight);

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

