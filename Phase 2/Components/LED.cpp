#include "LED.h"

LED::LED(const GraphicsInfo &r_GfxInfo) : Component(r_GfxInfo)
{
	m_Status = LOW;	// Default to OFF
	m_InputPin.setStatus(LOW);
	m_InputPin.setComponent(this);	// Set the component for the input pin
}

void LED::Operate()
{
	// LED updates its status based on the input pin
	m_Status = (STATUS)m_InputPin.getStatus();
}

void LED::Draw(Output* pOut, bool selected)
{
	pOut->DrawLED(m_GfxInfo, selected, (m_Status == HIGH));
}

int LED::GetOutPinStatus()
{
	return -1;	// LED has no output pin
}

int LED::GetInputPinStatus(int n)
{
	return m_InputPin.getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
	// This sets the input pin status
	m_InputPin.setStatus(s);
	Operate();	// Update LED status based on input
}

void LED::save(ofstream& file)
{
	string lbl = GetLabel();
	int status = (m_Status == HIGH) ? 1 : 0;
	if (lbl == "")
		file << "LED" << " " << -1 << " " << "$" << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << status << endl;
	else
		file << "LED" << " " << -1 << " " << lbl << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << status << endl;
}

void LED::load(ifstream& file)
{
	string tempLabel;
	int tempID;
	int x1, y1;
	int status;
	file >> tempID >> tempLabel >> x1 >> y1 >> status;
	m_GfxInfo.x1 = x1;
	m_GfxInfo.y1 = y1;
	m_GfxInfo.x2 = x1 + UI.LED_Width;
	m_GfxInfo.y2 = y1 + UI.LED_Height;
	m_Status = (status == 1) ? HIGH : LOW;
	m_InputPin.setStatus(m_Status);
}

