//#include "Input.h"
#include "Input.h"
#include "Output.h"
#include "..\CMUgraphicsLib\mousequeue.h"
#include <windows.h> // For Sleep function

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->FlushMouseQueue();// to not get wrong click by A
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output* pOut) // <--- FIXED
{	//// DONNNNEEEE
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	pOut->ClearStatusBar();
	pOut->PrintMsg("please Enter your text: ");
	string myst="";
	while (true) {
		char k;
		keytype ke;
		pWind->FlushKeyQueue();
		pWind->FlushMouseQueue();
		ke =pWind->WaitKeyPress(k);
		if (ke == ESCAPE) {
			pOut->ClearStatusBar();
			return "";
		}

		if (ke == ASCII) {
			if ((k == 127|| k == 8) && myst != "") {
				myst.pop_back();
			}
			else if(k == 13 || k == '\n' || k == '\r') {
				pOut->ClearStatusBar();
				break;
				
			}
			else {
				myst += k;
			}
			pOut->ClearStatusBar();
			pOut->PrintMsg(myst);
			
		}
	}
	return myst;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_INV:       return ADD_INV;
			case ITM_BUFF:      return ADD_Buff;
			case ITM_NAND2:     return ADD_NAND_GATE_2;
			case ITM_NOR2:      return ADD_NOR_GATE_2;
			case ITM_XOR2:      return ADD_XOR_GATE_2;
			case ITM_XNOR2:     return ADD_XNOR_GATE_2;
			case ITM_AND3:      return ADD_AND_GATE_3;
			case ITM_NOR3:      return ADD_NOR_GATE_3;
			case ITM_XOR3:      return ADD_XOR_GATE_3;
			case ITM_SWITCH:    return ADD_Switch;
			case ITM_LED:       return ADD_LED;
			case ITM_CONNECTION:return ADD_CONNECTION; 
			case ITM_LABEL:     return ADD_Label;
			case ITM_EDIT_LABEL:return EDIT_Label;
			case ITM_REDO:      return REDO;
			case ITM_DEL:	    return DEL;
			case ITM_MOVE:	    return MOVE;
			case ITM_UNDO:      return UNDO;
			case ITM_SAVE:      return SAVE; 
			case ITM_LOAD:      return LOAD;
			case ITM_EXIT:      return EXIT;
			case TO_SIM:	    return SIM_MODE;
				
				//testingtesting
			default: return DSN_TOOL;
//A click on empty place in desgin toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{	
			return SELECT;	//user want to select/unselect a component
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else if (UI.AppMode == SIMULATION)
	{
		// b ye check if el click gowa el vertical simulation toolbar
		if (x >= 0 && x < UI.ToolItemWidth &&
			y >= UI.ToolBarHeight &&
			y < UI.height - UI.StatusBarHeight)
		{
			// order bta3 el buttons fel simulation toolbar
			int ClickedItemOrderSim =
				(y - UI.ToolBarHeight) / UI.ToolItemHeight;

			switch (ClickedItemOrderSim)
			{
			case ITM_SIM:         return Simulate;
			case ITM_RUN:         return RUN_SIM;
			case ITM_STEP:        return Step;
			case ITM_RESET:       return Reset;
			case ITM_TRUTH:       return Create_TruthTable;
			case ITM_PROBE:       return PROBE;
			case ITM_EXIT_SIM:    return DSN_MODE;
			}

		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			// Try to toggle a switch at the clicked position
			return Change_Switch;//user want to select/unselect a component
		}
	}


	// Safe fallback to avoid undefined behaviour if none of the above returned
	return DSN_TOOL;
}

void Input::GetMouseCoord(int &x, int &y)
{
	pWind->GetMouseCoord(x, y);
}

int Input::GetButtonState(int &x, int &y)
{
	buttonstate bs = pWind->GetButtonState(LEFT_BUTTON, x, y);
	return (bs == BUTTON_DOWN) ? 1 : 0;
}

bool Input::WaitForDoubleClick(int &x, int &y)
{
	// Wait for first click
	int x1, y1, x2, y2;
	pWind->WaitMouseClick(x1, y1);
	
	// Try to get second click quickly (double-click detection)
	// Use a loop with small delays to check for second click
	DWORD startTime = GetTickCount();
	const DWORD doubleClickTime = 500; // 500ms double-click window
	
	while ((GetTickCount() - startTime) < doubleClickTime) {
		clicktype ct = pWind->GetMouseClick(x2, y2);
		if (ct == LEFT_CLICK) {
			// Check if second click is near first click (within 10 pixels)
			int dx = x2 - x1;
			int dy = y2 - y1;
			if (dx * dx + dy * dy < 500) { // Within 10 pixels
				x = x2;
				y = y2;
				return true; // Double-click detected
			}
		}
		Sleep(10); // Small delay to avoid busy waiting
	}
	
	// Single click only (timeout)
	x = x1;
	y = y1;
	return false;
}

Input::~Input()
{
}
