#include "XOR2.h"

XOR2::XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR2::Operate()
{
	STATUS A = m_InputPins[0].getStatus();
	STATUS B = m_InputPins[1].getStatus();
	if ((A == HIGH && B == LOW) || (A == LOW && B == HIGH))
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void XOR2::Draw(Output* pOut,bool selected)
{
	pOut->DrawXOR2(m_GfxInfo,selected);
}

int XOR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int XOR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();
}

void XOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void XOR2::save(ofstream& file)
{
	string lbl = GetLabel();
	if (lbl == "")
		file << "XOR2" << " " << -1 << " " << "$" << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
	else
		file << "XOR2" << " " << -1 << " " << lbl << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

void XOR2::load(ifstream& file)
{
	string tempLabel;
	int tempID;
	int x1, y1;
	file >> tempID >> tempLabel >> x1 >> y1;
	m_GfxInfo.x1 = x1;
	m_GfxInfo.y1 = y1;
	m_GfxInfo.x2 = x1 + UI.XOR2_Width;
	m_GfxInfo.y2 = y1 + UI.XOR2_Height;
}