#pragma once
#include "..\Defs.h"
#include "Input.h"
enum TunnelDir { DIR_IN, DIR_OUT };
class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;
	void whiteBox( int dimx, int dimy,int x2, int y2)const;//for delete class by A
	void DrawLabel(GraphicsInfo r_GfxInfo, bool selected, string str) const;//for label class by A
	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window

	
	// Draws 2-input AND gate
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawBUFFER(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOTGATE(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// I/O and Tunnels (5 functions)
	void DrawSwitch(GraphicsInfo r_GfxInfo, bool selected, bool On) const;
	void DrawLED(GraphicsInfo r_GfxInfo, bool selected, bool On) const;
	void DrawLampGreen(GraphicsInfo r_GfxInfo, bool selected, bool On) const;
	void DrawLampRed(GraphicsInfo r_GfxInfo, bool selected, bool On) const;
	void DrawLampBLUE(GraphicsInfo r_GfxInfo, bool selected, bool On) const;
	
	void DrawTunnel(GraphicsInfo r_GfxInfo, bool selected, TunnelDir direction) const;

	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc

	// Draws Connection
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false , bool HighState = false) const;
	void DrawJunctionDot(int x, int y, bool HighState) const;
	void PrintMsg(string msg) const;	//Print a message on Status bar
	void GetTextSize(int& width, int& height, string text, int fontSize = 18) const; //Get text dimensions
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const;
	
	// Draws the Truth Table (Inputs + Outputs) on the screen
	void DrawTruthTable(int numInputs, int numOutputs, int* tableData) const;

	~Output();
};
