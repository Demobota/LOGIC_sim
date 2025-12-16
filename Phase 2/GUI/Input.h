#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window

public:
	Input(window*);
	void GetPointClicked(int &x, int &y);	//Get coordinate where user clicks
	string GetString(Output* pOut);		//Returns a string entered by the user (corrected name)

	ActionType GetUserAction() const; //Reads the user click and maps it to an action
	
	// Mouse drag support
	void GetMouseCoord(int &x, int &y); // Get current mouse coordinates
	int GetButtonState(int &x, int &y); // Get left button state (returns 1 if down, 0 if up)
	bool WaitForDoubleClick(int &x, int &y); // Wait for double-click (returns true if double-click detected)

	~Input();
};
