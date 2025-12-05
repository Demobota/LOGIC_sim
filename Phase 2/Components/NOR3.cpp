#include "NOR3.h"

NOR3::NOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOR3::Operate()
{
	STATUS A = m_InputPins[0].getStatus();
	STATUS B = m_InputPins[1].getStatus();
	STATUS C = m_InputPins[2].getStatus();
	if (A == HIGH || B == HIGH || C == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}

void NOR3::Draw(Output* pOut,bool selected)
{
	pOut->DrawNOR3(m_GfxInfo,selected);
}

int NOR3::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int NOR3::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();
}

void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
