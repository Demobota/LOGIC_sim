#include "INV.h"

INV::INV(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void INV::Operate()
{
	STATUS A = m_InputPins[0].getStatus();
	if (A == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}

void INV::Draw(Output* pOut,bool selected)
{
	pOut->DrawNOTGATE(m_GfxInfo,selected);
}

int INV::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int INV::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();
}

void INV::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
