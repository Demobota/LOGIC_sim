#include "Connection.h"
#include "Gate.h"
#include "../ApplicationManager.h"
#include "LED.h"
Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{
	SrcPin = pSrcPin;
}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}
void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	// Transmit the status from the Source Pin to the Destination Pin
	STATUS s = SrcPin->getStatus();
	DstPin->setStatus(s);
}

void Connection::Draw(Output* pOut,bool selected)
{	
	pOut->DrawConnection(m_GfxInfo, selected, false);
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}
 void Connection::save(ofstream& file){}
 void Connection::load(ifstream& file){}

void Connection::UpdateSourceEndpoint(Component* pSrcComp)
{
	if (pSrcComp == NULL) return;
	
	GraphicsInfo SrcGfx = pSrcComp->GetGFXinfo();
	m_GfxInfo.x1 = SrcGfx.x2;
	m_GfxInfo.y1 = (SrcGfx.y1 + SrcGfx.y2) / 2;
}

void Connection::UpdateDestEndpoint(Component* pDstComp)
{
	if (pDstComp == NULL) return;
	
	GraphicsInfo DstGfx = pDstComp->GetGFXinfo();
	
	// For gates, find which input pin this connection is connected to
	Gate* pGate = dynamic_cast<Gate*>(pDstComp);
	if (pGate) {
		// Find which input pin index this connection uses
		// Check each input pin to find the one that matches DstPin
		int pinIndex = -1;
		// We need to check up to 3 pins (typical max for gates)
		for (int i = 0; i < 3; i++) {
			InputPin* pPin = pGate->GetInputPin(i);
			if (pPin == DstPin) {
				pinIndex = i;
				break;
			}
		}
		
		// Calculate y position based on pin index
		int GateHeight = DstGfx.y2 - DstGfx.y1;
		if (pinIndex == 0) {
			m_GfxInfo.y2 = DstGfx.y1 + 13;
		} else if (pinIndex == 1) {
			m_GfxInfo.y2 = DstGfx.y2 - 13;
		} else if (pinIndex == 2) {
			m_GfxInfo.y2 = DstGfx.y2 - 13;
		} else {
			// Fallback: use middle
			m_GfxInfo.y2 = (DstGfx.y1 + DstGfx.y2) / 2;
		}
		m_GfxInfo.x2 = DstGfx.x1;
	} else if (dynamic_cast<LED*>(pDstComp)) {
		// LED has one input pin at the left center
		m_GfxInfo.x2 = DstGfx.x1;
		m_GfxInfo.y2 = (DstGfx.y1 + DstGfx.y2) / 2;
	}
}

