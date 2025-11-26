#include "GUI\Input.h"
#include "GUI\Output.h"

//This is a test code to test the Input and Output classes

int main()
{
	int x,y;

	//Create Input and Output objects to test
	Output *pOut = new Output();
	Input *pIn = pOut->CreateInput();

	
	//Starting the test
	pOut->PrintMsg("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x,y);	//Wait for any click


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 1:	Create The FULL Tool bar, the drawing area and the status bar	
	//			This has already been done through the constrcutor of class Output
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMsg("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:	Drawing all the Components with all possible states: Normal, highlighted
	//			
	///////////////////////////////////////////////////////////////////////////////////
	
	pOut->PrintMsg("TEST2: Now we will show that Output class can draw any Component in any state, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	GraphicsInfo GfxInfo;  //to be used with draw function of the class Ouput

	/// 2.1- AND2 Gate test
	pOut->PrintMsg("Drawing 2-input AND gate, Normal and Highlighted,  Click to continue");
	
	//Drawing Normal AND2 gate
	GfxInfo.x1 = 100;	GfxInfo.y1 = 100;
	pOut->DrawAND2(GfxInfo);

	//Drawing Highlighted AND2 gate
	GfxInfo.x1 = 100;	GfxInfo.y1 = 300;
	pOut->DrawAND2(GfxInfo, true);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	/// 2.2- NAND2 Gate test
	pOut->PrintMsg("Drawing 2-input NAND gate, Normal and Highlighted,  Click to continue");

	///TODO: Add code to draw 2-input NAND gate, Normal and Highlighted -done
	GfxInfo.x1 = 100;	GfxInfo.y1 = 100;
	pOut->DrawNAND2(GfxInfo);

	//Drawing Highlighted NAND2 gate
	GfxInfo.x1 = 100;	GfxInfo.y1 = 300;
	pOut->DrawNAND2(GfxInfo, true);
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	/// 2.3- OR2 and NOR2 Gates test
	pOut->PrintMsg("Drawing 2-input OR and NOR gates, Normal and Highlighted,  Click to continue");
	
	// Draw OR2 normal and highlighted
	GfxInfo.x1 = 100; GfxInfo.y1 = 100;
	pOut->DrawOR2(GfxInfo);
	GfxInfo.x1 = 350; GfxInfo.y1 = 100;
	pOut->DrawOR2(GfxInfo, true);

	// Draw NOR2 normal and highlighted
	GfxInfo.x1 = 100;	GfxInfo.y1 = 220;
	pOut->DrawNOR2(GfxInfo);
	GfxInfo.x1 = 350;	GfxInfo.y1 = 220;
	pOut->DrawNOR2(GfxInfo, true);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	/// 2.4- XOR2 and XNOR2 Gates test
	pOut->PrintMsg("Drawing 2-input XOR and XNOR gates, Normal and Highlighted,  Click to continue");
	
	// XOR2
	GfxInfo.x1 = 120; GfxInfo.y1 = 100;
	pOut->DrawXOR2(GfxInfo);
	GfxInfo.x1 = 420; GfxInfo.y1 = 100;
	pOut->DrawXOR2(GfxInfo, true);

	// XNOR2
	GfxInfo.x1 = 120; GfxInfo.y1 = 260;
	pOut->DrawXNOR2(GfxInfo);
	GfxInfo.x1 = 420; GfxInfo.y1 = 260;
	pOut->DrawXNOR2(GfxInfo, true);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	/// 2.5- Buffer and Inverter Gates test
	pOut->PrintMsg("Drawing Buffer and Inverter Gates, Normal and Highlighted,  Click to continue");
	
	// Buffer (normal + highlighted)
	GfxInfo.x1 = 150; GfxInfo.y1 = 120;
	pOut->DrawBUFFER(GfxInfo);
	GfxInfo.x1 = 400; GfxInfo.y1 = 120;
	pOut->DrawBUFFER(GfxInfo, true);

	// Inverter (normal + highlighted)
	GfxInfo.x1 = 150; GfxInfo.y1 = 260;
	pOut->DrawNOTGATE(GfxInfo);
	GfxInfo.x1 = 400; GfxInfo.y1 = 260;
	pOut->DrawNOTGATE(GfxInfo, true);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.6- AND3, NOR3, and XOR3 Gates test
	pOut->PrintMsg("Drawing 3-input AND, NOR, XOR Gates, Normal and Highlighted,  Click to continue");
	
	// NOR3 (normal + highlighted)
	GfxInfo.x1 = 60;	GfxInfo.y1 = 90;
	pOut->DrawNOR3(GfxInfo);
	GfxInfo.x1 = 360;	GfxInfo.y1 = 90;
	pOut->DrawNOR3(GfxInfo, true);

	// AND3 (normal + highlighted)
	GfxInfo.x1 = 60;	GfxInfo.y1 = 220;
	pOut->DrawAND3(GfxInfo);
	GfxInfo.x1 = 360;	GfxInfo.y1 = 220;
	pOut->DrawAND3(GfxInfo, true);

	// XOR3 (normal + highlighted)
	GfxInfo.x1 = 60;	GfxInfo.y1 = 350;
	pOut->DrawXOR3(GfxInfo);
	GfxInfo.x1 = 360;	GfxInfo.y1 = 350;
	pOut->DrawXOR3(GfxInfo, true);

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();
	/// 2.7- Switch and LED test
	pOut->PrintMsg("Drawing Switch and LED, Normal and Highlighted,  Click to continue");
	
	// Switch: off normal, on highlighted
	//GfxInfo.x1 = 120; GfxInfo.y1 = 100;
	//pOut->DrawSwitch(GfxInfo, false, false); // not selected, off
	//GfxInfo.x1 = 320; GfxInfo.y1 = 100;
	//pOut->DrawSwitch(GfxInfo, true, true); // selected, on

	// Lamps: Green, Red, Blue - each off and on (normal/highlighted where applicable)
	//GfxInfo.x1 = 120; GfxInfo.y1 = 240;
	//pOut->DrawLampGreen(GfxInfo, false, false); // off
	//GfxInfo.x1 = 220; GfxInfo.y1 = 240;
	//pOut->DrawLampGreen(GfxInfo, true, true);  // selected + on

	//GfxInfo.x1 = 320; GfxInfo.y1 = 240;
	//pOut->DrawLampRed(GfxInfo, false, false); // off
	//GfxInfo.x1 = 420; GfxInfo.y1 = 240;
	//pOut->DrawLampRed(GfxInfo, true, true);  // selected + on

	//GfxInfo.x1 = 120; GfxInfo.y1 = 360;
	//pOut->DrawLampBLUE(GfxInfo, false, false); // off
	//GfxInfo.x1 = 220; GfxInfo.y1 = 360;
	//pOut->DrawLampBLUE(GfxInfo, true, true);  // selected + on

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.8- Connections
	pOut->PrintMsg("Drawing connections, Normal, Highlighted, straight, and broken,  Click to continue");

	// Let user click two points to draw an L-shaped selected connection
	//pIn->GetPointClicked(GfxInfo.x1, GfxInfo.y1);
	//pIn->GetPointClicked(GfxInfo.x2, GfxInfo.y2);
	//pOut->DrawConnection(GfxInfo, true);

	//// Let user click two points to draw an L-shaped non-selected connection
	//pIn->GetPointClicked(GfxInfo.x1, GfxInfo.y1);
	//pIn->GetPointClicked(GfxInfo.x2, GfxInfo.y2);
	//pOut->DrawConnection(GfxInfo, false);

	
	GfxInfo.x1 = 80; GfxInfo.y1 = 120;
	GfxInfo.x2 = 500; GfxInfo.y2 = 120;
	pOut->DrawConnection(GfxInfo, false);

	
	GfxInfo.x1 = 300; GfxInfo.y1 = 150;
	GfxInfo.x2 = 300; GfxInfo.y2 = 450;
	pOut->DrawConnection(GfxInfo, true);

	//Draw junction dots (high and low)
	pOut->DrawJunctionDot(300, 120, true);
	pOut->DrawJunctionDot(300, 240, false);

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	pOut->PrintMsg("Testing Input ability to read strings");

	///TODO: Add code here to 
	// 1- Read a string from the user on the status bar and print it inside the drawing area
	string textin = pIn->GetSrting(pOut);
	
	pOut->PrintMsg("Your text is ");
	pIn->GetPointClicked(x, y);
	pOut->PrintMsg(textin);
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;
	
	///TODO:  You must add a case for each action
	//Add cases for the missing actions below
	do
	{
		ActType = pIn->GetUserAction();

		switch (ActType)
		{
		case ADD_Buff:
				pOut->PrintMsg("Action: add a buffer gate , Click anywhere");
				break;

		case ADD_INV:
				pOut->PrintMsg("Action: add an inverter gate , Click anywhere");
				break;

		case ADD_AND_GATE_2:
				pOut->PrintMsg("Action: add 2-input AND gate , Click anywhere");
				break;

		case ADD_NAND_GATE_2:
				pOut->PrintMsg("Action: add 2-input NAND gate , Click anywhere");
				break;

		case ADD_OR_GATE_2:
				pOut->PrintMsg("Action: add 2-input OR gate , Click anywhere");
				break;

		case ADD_NOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input NOR gate , Click anywhere");
				break;

		case ADD_XOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input XOR gate , Click anywhere");
				break;

		case ADD_XNOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input XNOR gate , Click anywhere");
				break;

		case SELECT:
				pOut->PrintMsg("Action: a click on the Drawing area, Click anywhere");
				break;
			
		case STATUS_BAR:
				pOut->PrintMsg("Action: a click on the Status Bar, Click anywhere");
				break;
 
		case DSN_TOOL:
				pOut->PrintMsg("Action: a click on empty area in the Design Tool Bar, Click anywhere");
				break;

		case SIM_MODE:
				pOut->PrintMsg("Action: Switch to Simulation Mode, creating simualtion tool bar");
				pOut->CreateSimulationToolBar();
				break;

		case PROBE:
			pOut->PrintMsg("Action: You clicked on the Probe icon");
			break;

		case RUN_SIM:
			pOut->PrintMsg("Action: You clicked on Run Simulation");
			break;

		case Reset:
			pOut->PrintMsg("Action: You clicked on Reset");
			break;

		case Simulate:
			pOut->PrintMsg("Action: You clicked on Simulation");
			break;

		case Step:
			pOut->PrintMsg("Action: You clicked on the Step icon");
			break;
		case Create_TruthTable:
			pOut->PrintMsg("Action: You clicked on Create Truth Table");
			break;

		case DSN_MODE:
				pOut->PrintMsg("Action: Switch to Design Mode, creating Design tool bar");
				pOut->CreateDesignToolBar();
				break;
		case ADD_AND_GATE_3:
				pOut->PrintMsg("Action: add 3-input AND gate , Click anywhere");
				break;//Add 3-input AND gate
		case ADD_NOR_GATE_3:
				pOut->PrintMsg("Action: add 3-input NOR gate , Click anywhere");
				break;//Add 3-input NOR gate
		case ADD_XOR_GATE_3:
				pOut->PrintMsg("Action: add 3-input XOR gate , Click anywhere");
				break;
		case ADD_Switch:
			pOut->PrintMsg("Action: add Switch , Click anywhere");
			break;
		case ADD_LED:
			pOut->PrintMsg("Action: add LED , Click anywhere");
			break;
		case ADD_CONNECTION:
			pOut->PrintMsg("Action: add Connection , Click anywhere");
			break;
		case ADD_Label:
			pOut->PrintMsg("Action: add label , Click anywhere");
			break;
		case EDIT_Label:
			pOut->PrintMsg("Action: add EDIT label , Click anywhere");
			break;
		case UNDO:
			pOut->PrintMsg("Action: add UNDO, Click anywhere");
			break;
		case REDO:
			pOut->PrintMsg("Action: add REDO , Click anywhere");
			break;
		case SAVE:
			pOut->PrintMsg("Action:   SAVE, Click anywhere");
			break;
		case DEL:
			pOut->PrintMsg("Action:   DELETE, Click anywhere");
			break;
		case MOVE:
			pOut->PrintMsg("Action:   MOVE, Click anywhere");
			break;
		case EXIT:				
				pOut->PrintMsg("EXIT is Pressed");
				break;
		}
	}while(ActType != EXIT);


	/// Exiting
	pOut->PrintMsg("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x,y);

	
	delete pIn;
	delete pOut;	
	return 0;
}


