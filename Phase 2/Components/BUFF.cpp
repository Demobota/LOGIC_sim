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
