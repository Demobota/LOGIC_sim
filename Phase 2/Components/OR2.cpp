#include "OR2.h"

OR2::OR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void OR2::Operate()
{
	//calculate the output status as the ORing of the two input pins
	STATUS A = m_InputPins[0].getStatus();
	STATUS B = m_InputPins[1].getStatus();

	if (A == HIGH || B == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

// Function Draw
// Draws 2-input OR gate
void OR2::Draw(Output* pOut,bool selected)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawOR2(m_GfxInfo,selected);
}

//returns status of outputpin
int OR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

//returns status of Inputpin #n
int OR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void OR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void OR2::save(ofstream& file)
{
	string lbl = GetLabel();
	if (lbl == "")
		file << "OR2" << " " << -1 << " " << "$" << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
	else
		file << "OR2" << " " << -1 << " " << lbl << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

void OR2::load(ifstream& file)
{
	string tempLabel;
	int tempID;
	int x1, y1;
	file >> tempID >> tempLabel >> x1 >> y1;
	m_GfxInfo.x1 = x1;
	m_GfxInfo.y1 = y1;
	m_GfxInfo.x2 = x1 + UI.OR2_Width;
	m_GfxInfo.y2 = y1 + UI.OR2_Height;
}