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

	int Wdth = UI.LABEL_Height;
	//Validation to not allow user to place gate at ToolBar or status bar
	do {
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);
		y1 = Cy - Wdth / 2;
		y2 = Cy + Wdth / 2;
	} while (y1 < UI.ToolBarHeight || y2 >= UI.height - UI.StatusBarHeight);
	label = pIn->GetSrting(pOut);
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

