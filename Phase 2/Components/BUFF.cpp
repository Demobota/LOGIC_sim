#include "BUFF.h"

BUFF::BUFF(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void BUFF::Operate()
{
	STATUS A = m_InputPins[0].getStatus();
	m_OutputPin.setStatus(A);
}

void BUFF::Draw(Output* pOut,bool selected)
{
	pOut->DrawBUFFER(m_GfxInfo,selected);
}

int BUFF::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int BUFF::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();
}

void BUFF::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void BUFF::save(ofstream& file)
{
	string lbl = GetLabel();
	if (lbl == "")
		file << "BUFF" << " " << -1 << " " << "$" << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
	else
		file << "BUFF" << " " << -1 << " " << lbl << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

void BUFF::load(ifstream& file)
{
	string tempLabel;
	int tempID;
	int x1, y1;
	file >> tempID >> tempLabel >> x1 >> y1;
	m_GfxInfo.x1 = x1;
	m_GfxInfo.y1 = y1;
	m_GfxInfo.x2 = x1 + UI.BUFF_Width;
	m_GfxInfo.y2 = y1 + UI.BUFF_Height;
}