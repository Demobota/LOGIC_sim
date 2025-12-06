#include "Switch.h"

Switch::Switch(const GraphicsInfo &r_GfxInfo) : Component(r_GfxInfo)
{
	m_Status = LOW;	// Default to OFF
	m_OutputPin = new OutputPin(5);	// FanOut of 5
	m_OutputPin->setStatus(LOW);
}

void Switch::Operate()
{
	// Switch doesn't need to operate - it just maintains its state
	// The output pin status is set when the switch status changes
}

void Switch::Draw(Output* pOut, bool selected)
{
	pOut->DrawSwitch(m_GfxInfo, selected, (m_Status == HIGH));
}

int Switch::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}

int Switch::GetInputPinStatus(int n)
{
	return -1;	// Switch has no input pins
}

void Switch::setInputPinStatus(int n, STATUS s)
{
	// This is used to change the switch status
	m_Status = s;
	m_OutputPin->setStatus(s);
}

void Switch::Toggle()
{
	if (m_Status == HIGH)
		m_Status = LOW;
	else
		m_Status = HIGH;
	m_OutputPin->setStatus(m_Status);
}

void Switch::save(ofstream& file)
{
	string lbl = GetLabel();
	int status = (m_Status == HIGH) ? 1 : 0;
	if (lbl == "")
		file << "SWITCH" << " " << -1 << " " << "$" << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << status << endl;
	else
		file << "SWITCH" << " " << -1 << " " << lbl << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << status << endl;
}

void Switch::load(ifstream& file)
{
	string tempLabel;
	int tempID;
	int x1, y1;
	int status;
	file >> tempID >> tempLabel >> x1 >> y1 >> status;
	m_GfxInfo.x1 = x1;
	m_GfxInfo.y1 = y1;
	m_GfxInfo.x2 = x1 + UI.Switch_Width;
	m_GfxInfo.y2 = y1 + UI.Switch_Height;
	m_Status = (status == 1) ? HIGH : LOW;
	if (!m_OutputPin)
		m_OutputPin = new OutputPin(5);
	m_OutputPin->setStatus(m_Status);
}

Switch::~Switch()
{
	if (m_OutputPin)
		delete m_OutputPin;
}
