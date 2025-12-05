#include "XOR3.h"

XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR3::Operate()
{
	STATUS A = m_InputPins[0].getStatus();
	STATUS B = m_InputPins[1].getStatus();
	STATUS C = m_InputPins[2].getStatus();
	int highCount = 0;
	if (A == HIGH) highCount++;
	if (B == HIGH) highCount++;
	if (C == HIGH) highCount++;
	if (highCount % 2 == 1)// checks if number of 1 inputs are odd xnor high
		//// explanation: if A  A(.)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void XOR3::Draw(Output* pOut,bool selected)
{
	pOut->DrawXOR3(m_GfxInfo,selected);
}

int XOR3::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int XOR3::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();
}

void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
