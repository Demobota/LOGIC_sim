#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED,5);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	// Design Mode

	// Prepare list of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];

	// Common gates
	MenuItemImages[ITM_AND2]    = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]     = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_NAND2]   = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR2]    = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XOR2]    = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2]   = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_INV]     = "images\\Menu\\Menu_INV.jpg";
	MenuItemImages[ITM_BUFF]    = "images\\Menu\\Menu_BUFF.jpg";
	MenuItemImages[ITM_AND3]    = "images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_NOR3]    = "images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_XOR3]    = "images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_EXIT]    = "images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_SWITCH]  = "images\\Menu\\Menu_SWITCH.jpg";
	MenuItemImages[ITM_LABEL]   = "images\\Menu\\Menu_LABEL.jpg";
	MenuItemImages[ITM_CONNECTION] = "images\\Menu\\Menu_Connection.jpg";
	MenuItemImages[ITM_LED]       = "images\\Menu\\Menu_LED.jpg";
	MenuItemImages[ITM_EDIT_LABEL] = "images\\Menu\\Menu_Edit_LABEL.jpg";
	MenuItemImages[ITM_REDO] = "images\\Menu\\Menu_REDO.jpg";
	MenuItemImages[ITM_UNDO] = "images\\Menu\\Menu_UNDO.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\Menu_Move.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[TO_SIM] = "images\\Menu\\SIMMODE.jpg"; 
	MenuItemImages[ITM_DEL] = "images\\Menu\\Menu_del.jpg";
	//testingtesting
	// Continue for other menu items as needed
	// other items may be empty

	// compute slot width at runtime so all items fit the actual UI width
	int itemCount  = ITM_DSN_CNT;
	int itemWidth  = (itemCount > 0) ? (UI.width / itemCount) : UI.ToolItemWidth;
	if (itemWidth <= 0) itemWidth = 50; // safe fallback
	int itemHeight = UI.ToolBarHeight;

	// Draw menu item images
	for (int i = 0; i < itemCount; ++i) {
		const string &imgPath = MenuItemImages[i];
		if (imgPath.empty()) continue;
		int x = i * itemWidth;
		pWind->DrawImage(imgPath, x, 0, itemWidth, itemHeight);
	}

	// Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	ClearDrawingArea();

	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	pWind->DrawImage("images\\Simulation\\SIM.jpg", 0, 0, UI.ToolItemWidth, UI.ToolItemHeight);
	pWind->DrawImage("images\\Simulation\\RUN.jpg", UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolItemHeight);
	pWind->DrawImage("images\\Simulation\\STEP.jpg", 2 * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolItemHeight);
	pWind->DrawImage("images\\Simulation\\RESET.jpg", 3 * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolItemHeight);
	pWind->DrawImage("images\\Simulation\\TRUTH_TABLE.jpg", 4 * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolItemHeight);
	pWind->DrawImage("images\\Simulation\\PROBE.jpg", 5 * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolItemHeight);
	pWind->DrawImage("images\\Simulation\\EXIT.jpg", 6 * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolItemHeight);
	
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\Gate_AND2_Hi.jpg";
	else  
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

//TODO: Add similar functions to draw all components


void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}
void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR3.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NAND2_Width, UI.NAND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	// Fixed typo: UI.NOR22_Height -> UI.NOR2_Height
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOR2_Width, UI.NOR2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR2_Width, UI.XOR2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawBUFFER(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\BUFF_Hi.jpg";
	else
		GateImage = "Images\\Gates\\BUFF.jpg";

	// Fixed typo: UI.BUFEER_Width -> UI.BUFFER_Width
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawNOTGATE(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Inverter_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Inverter.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawLampGreen(GraphicsInfo r_GfxInfo, bool selected, bool On) const
{
	string GateImage;
	if (On)
		GateImage = "Images\\Gates\\Lamp_Green_ON.jpg";
	else
		GateImage = "Images\\Gates\\Lamp_Green_OFF.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawLampRed(GraphicsInfo r_GfxInfo, bool selected, bool On) const
{
	string GateImage;
	if (On)
		GateImage = "Images\\Gates\\Lamp_Red_ON.jpg"; // e.g., A lit-up red bulb
	else
		GateImage = "Images\\Gates\\Lamp_Red_OFF.jpg"; // e.g., A dark red bulb

	// You could also add a check for 'selected' to draw a blue box around it

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}

void Output::DrawLampBLUE(GraphicsInfo r_GfxInfo, bool selected, bool On) const
{
	string GateImage;
	if (On)
		GateImage = "Images\\Gates\\Lamp_BLUE_ON.jpg";
	else
		GateImage = "Images\\Gates\\Lamp_BLUE_OFF.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.G_Width, UI.G_Height);
}


	// You will need to define 'TunnelDir' in your header files (e.g., as an enum)
	// enum TunnelDir { DIR_IN, DIR_OUT };

void Output::DrawTunnel(GraphicsInfo r_GfxInfo, bool selected, TunnelDir direction) const
{
	string GateImage;

	if (direction == DIR_IN) // If it's an Input Tunnel
	{
		if (selected)
			GateImage = "Images\\Gates\\Tunnel_Input_Hi.jpg";
		else
			GateImage = "Images\\Gates\\Tunnel_Input.jpg";
	}
	else // If it's an Output Tunnel
	{
		if (selected)
			GateImage = "Images\\Gates\\Tunnel_Output_Hi.jpg";
		else
			GateImage = "Images\\Gates\\Tunnel_Output.jpg";
	}

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Tunnel_Width, UI.Tunnel_Height);
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo, bool selected, bool On) const
{
	string GateImage;

	if (selected) // First, check if the switch is highlighted
	{
		if (On) // Is it selected AND on?
			GateImage = "Images\\Gates\\SWITCH_1_HI.jpg";
		else // It's selected AND off
			GateImage = "Images\\Gates\\SWITCH_0_HI.jpg";
	}
	else // If it's not selected
	{
		if (On) // Is it not selected AND on?
			GateImage = "Images\\Gates\\SWITCH_1.jpg";
		else // It's not selected AND off
			GateImage = "Images\\Gates\\SWITCH_0.jpg";
	}

	//Draw the correct switch image
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Switch_Width, UI.Switch_Height);
}
void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected, bool On) const
{
	string GateImage;

	if (selected) // First, check if the switch is highlighted
	{
		if (On) // Is it selected AND on?
			GateImage = "Images\\Gates\\LED_ON_HI.jpg";
		else // It's selected AND off
			GateImage = "Images\\Gates\\LED_OFF_HI.jpg";
	}
	else // If it's not selected
	{
		if (On) // Is it not selected AND on?
			GateImage = "Images\\Gates\\LED_ON.jpg";
		else // It's not selected AND off
			GateImage = "Images\\Gates\\LED_OFF.jpg";
	}

	//Draw the correct switch image
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Switch_Width, UI.Switch_Height);
}


//TODO: Add similar functions to draw all components


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected, bool HighState) const
{
	if (selected == true)
		pWind->SetPen(UI.SelectColor, 3);
	else
		pWind->SetPen(UI.ConnColor, 3);
	int x1 = r_GfxInfo.x1;
	int y1 = r_GfxInfo.y1;
	int x2 = r_GfxInfo.x2;
	int y2 = r_GfxInfo.y2;
	pWind->DrawLine(x1, y1, x2, y1);
	pWind->DrawLine(x2, y1, x2, y2);
}

void Output::DrawJunctionDot(int x, int y, bool HighState) const
{  

	// This function draws a small, filled circle at coordinates (x, y)

	// 1. Determine Color
	color DotColor;
	if (HighState) {
		DotColor = color(0, 255, 0); // explicit green to replace undefined LIME
	}
	else {
		DotColor = BLACK;
	}

	// 2. Draw the Dot
	pWind->SetPen(DotColor);      // Set the outline color
	pWind->SetBrush(DotColor);    // Set the fill color

	// Draw a small filled circle (Dot)
	// The radius (5) determines the size of the junction dot.
	pWind->DrawCircle(x, y, 5, FILLED);
}


Output::~Output()
{
	delete pWind;
}
