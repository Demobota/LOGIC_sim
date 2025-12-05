#include "XNOR2.h"

XNOR2::XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XNOR2::Operate()
{
	STATUS A = m_InputPins[0].getStatus();
	STATUS B = m_InputPins[1].getStatus();
	if ((A == HIGH && B == LOW) || (A == LOW && B == HIGH))
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}

void XNOR2::Draw(Output* pOut,bool selected)
{
	pOut->DrawXNOR2(m_GfxInfo,selected);
}

int XNOR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int XNOR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();
}

void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
