#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo) : Component(r_GfxInfo)
{
	m_Status = LOW;
	m_InputPin.setStatus(LOW);
	m_InputPin.setComponent(this);
}

void LED::Operate()
{
	// Update status based on input pin
	m_Status = (STATUS)m_InputPin.getStatus();
}

void LED::Draw(Output* pOut, bool selected)
{
	// Call the Output class to draw the LED
	pOut->DrawLED(m_GfxInfo, selected, (m_Status == HIGH));
}

int LED::GetOutPinStatus()
{
	return -1; // LED has no output
}

int LED::GetInputPinStatus(int n)
{
	// Return the status of the single input pin
	return m_InputPin.getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
	Operate(); // Update the LED immediately
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