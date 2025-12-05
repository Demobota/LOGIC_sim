#include "AddLabel.h"
#include "..\ApplicationManager.h"
//delete after testing is done
#include <iostream>
using namespace std;
AddLabel::AddLabel(ApplicationManager* pApp) :Action(pApp)
{
}

AddLabel::~AddLabel()
{
}

void AddLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message

	pOut->PrintMsg("Label: Click to add the AddLabel");
	double y1;
	double y2;

	int Len = UI.LABEL_Width;
	int Wdth = UI.LABEL_Height;
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
	label = pIn->GetString(pOut);
	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddLabel::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners based on text length
	Output* pOut = pManager->GetOutput();
	
	// Get the text size using the same font size as drawing
	const int fontSize = 18;
	int textWidth = 0, textHeight = 0;
	if (!label.empty()) {
		pOut->GetTextSize(textWidth, textHeight, label, fontSize);
	}
	
	// Calculate box dimensions: text width + padding on both sides
	const int horizontalPadding = 20;  // 10 pixels padding on each side
	int Len = (textWidth > 0) ? (textWidth + horizontalPadding) : UI.LABEL_Width;
	int Wdth = UI.LABEL_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the label

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	Label *pA = new Label(GInfo, label);
	pManager->AddComponent(pA);
}

void AddLabel::Undo()
{
}

void AddLabel::Redo()
{
}

