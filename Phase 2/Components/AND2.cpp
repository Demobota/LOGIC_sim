#include "AND2.h"

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void AND2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut,bool selected)
{
	//Call output class and pass gate drawing info to it.
	
	pOut->DrawAND2(m_GfxInfo,selected);
}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void AND2::save(ofstream& file)
{
	string lbl = GetLabel();

	// Logic: If empty, write $, otherwise write the label
	if (lbl == "")
		file << "AND2" << " " << -1 << " " << "$" << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
	else
		file << "AND2" << " " << -1 << " " << lbl << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

void AND2::load(ifstream& file)
{
	string tempLabel;
	int tempID;
	int x1, y1;

	// Read values in the same order
	file >> tempID >> tempLabel >> x1 >> y1;

	// We ignore ID and Label because the Component class doesn't support them right now.

	// Update Graphics Info
	m_GfxInfo.x1 = x1;
	m_GfxInfo.y1 = y1;
	// Calculate the other corner
	m_GfxInfo.x2 = x1 + UI.AND2_Width;
	m_GfxInfo.y2 = y1 + UI.AND2_Height;
}