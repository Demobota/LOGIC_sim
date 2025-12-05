#include "NOR2.h"

NOR2::NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOR2::Operate()
{
	STATUS A = m_InputPins[0].getStatus();
	STATUS B = m_InputPins[1].getStatus();
	if (A == HIGH || B == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}

void NOR2::Draw(Output* pOut,bool selected)
{
	pOut->DrawNOR2(m_GfxInfo,selected);
}

int NOR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int NOR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();
}

void NOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
