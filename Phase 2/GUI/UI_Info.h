#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	// Window and toolbar layout
	static const int	width = 1500, height = 750,	// Window width and height
						wx = 15, wy = 15,				// Window starting coordinates
						StatusBarHeight = 50,			// Status Bar Height
						ToolBarHeight = 50,				// Tool Bar Height (distance from top of window to bottom line of toolbar)
						ToolItemWidth = width / ITM_DSN_CNT,				// Width of each item in toolbar menu
						ToolItemHeight = 50;			// Height of each item in toolbar menu (ADDED)

	// Colors
	color DrawColor;		// Drawing color
	color SelectColor;		// Highlighting color
	color ConnColor;		// Connector color
	color MsgColor;			// Messages color
	color BkGrndColor;		// Back ground color

	// Component sizes (width x height)
	// Gates
	static const int	G_Width = 50, G_Height = 50;
	static const int	AND2_Width   = 50, AND2_Height   = 50;
	static const int	OR2_Width    = 50, OR2_Height    = 50;
	//static const int	NOT_Width    = 50, NOT_Height    = 50;
	static const int	NAND2_Width  = 50, NAND2_Height  = 50;
	static const int	NOR2_Width   = 50, NOR2_Height   = 50;
	static const int	XOR2_Width   = 50, XOR2_Height   = 50;
	static const int	XOR3_Width = 50, XOR3_Height = 50;
	static const int	AND3_Width = 50, AND3_Height = 50;
	static const int	NOR3_Width = 50, NOR3_Height = 50;
	static const int	BUFF_Width = 50, BUFF_Height = 50;
	static const int	INV_Width = 50,   INV_Height = 50;
	static const int	Exit_Width = 50, Exit_Height = 50;
	static const int	SAVE_Width = 50, SAVE_Height = 50;
	// Other components
	static const int	LED_Width = 50, LED_Height = 50;
	static const int	CONNECTION_Width = 50, CONNECTION_Height = 50;
	static const int	LABEL_Width = 100, LABEL_Height = 30;
	static const int	EDIT_LABEL_Width = 100, EDIT_LABEL_Height = 30;
	static const int	Switch_Width  = 50, Switch_Height  = 50;
	static const int	UNDO_Width = 50, UNDO_Height = 50;
	static const int	REDO_Width = 50, REDO_Height = 50;
	static const int	Tunnel_Width  = 30, Tunnel_Height  = 10;

	// Add more item sizes here as needed
} UI;	// create a single global object UI

#endif