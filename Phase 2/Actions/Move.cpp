#include "Move.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include "..\Components\Label.h"

#include <iostream>
using namespace std;
Move::Move(ApplicationManager* pApp) : Action(pApp)
{
	selectedComp = NULL;
}

Move::~Move(void)
{
}

void Move::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Wait for user to double-click on a component to drag
	pOut->PrintMsg("Move: triple-click on a component to drag it");
	
	// Wait for user to double-click on a component
	bool isDoubleClick = false;
	do {
		isDoubleClick = pIn->WaitForDoubleClick(clickX, clickY);
		if (!isDoubleClick) {
			pOut->PrintMsg("Move: Please triple-click on a component");
			Sleep(500); // Brief pause before next attempt
		}
	} while ((!isDoubleClick) || (clickY < UI.ToolBarHeight || clickY >= UI.height - UI.StatusBarHeight));
	
	pOut->ClearStatusBar();
}

// Helper function to find component that owns an OutputPin
Component* FindComponentWithOutputPin(ApplicationManager* pManager, OutputPin* pPin)
{
	int compCount = pManager->GetComponentCount();
	for (int i = 0; i < compCount; i++) {
		Component* pComp = pManager->GetComponentByIndex(i);
		if (pComp == NULL) continue;
		
		Gate* pGate = dynamic_cast<Gate*>(pComp);
		if (pGate && pGate->GetOutputPin() == pPin) {
			return pComp;
		}
		
		Switch* pSwitch = dynamic_cast<Switch*>(pComp);
		if (pSwitch && pSwitch->GetOutputPin() == pPin) {
			return pComp;
		}
	}
	return NULL;
}

// Helper function to update connections for a moved component
void UpdateConnectionsForComponent(ApplicationManager* pManager, Component* pMovedComp)
{
	int compCount = pManager->GetComponentCount();
	for (int i = 0; i < compCount; i++) {
		Component* pComp = pManager->GetComponentByIndex(i);
		Connection* pConn = dynamic_cast<Connection*>(pComp);
		if (pConn == NULL) continue;
		
		// Check if connection's source pin belongs to moved component
		Component* pSrcComp = FindComponentWithOutputPin(pManager, pConn->getSourcePin());
		if (pSrcComp == pMovedComp) {
			pConn->UpdateSourceEndpoint(pMovedComp);
		}
		
		// Check if connection's destination pin belongs to moved component
		Component* pDstComp = pConn->getDestPin()->getComponent();
		if (pDstComp == pMovedComp) {
			pConn->UpdateDestEndpoint(pMovedComp);
		}
	}
}

// Helper function to check if position is valid
bool IsValidPosition(GraphicsInfo newGfxInfo, Component* selectedComp, ApplicationManager* pManager)
{
	// Check if new position is within drawing area
	if (newGfxInfo.x1 < 0 || newGfxInfo.y1 < UI.ToolBarHeight ||
		newGfxInfo.x2 > UI.width || newGfxInfo.y2 > (UI.height - UI.StatusBarHeight)) {
		return false;
	}

	// Check if new position overlaps with other components (excluding connections)
	int compCount = pManager->GetComponentCount();
	for (int i = 0; i < compCount; i++) {
		Component* pComp = pManager->GetComponentByIndex(i);
		if (pComp == NULL || pComp == selectedComp || dynamic_cast<Connection*>(pComp)) {
			continue;
		}
		GraphicsInfo otherGfx = pComp->GetGFXinfo();
		bool overlapX = !(newGfxInfo.x2 < otherGfx.x1 || newGfxInfo.x1 > otherGfx.x2);
		bool overlapY = !(newGfxInfo.y2 < otherGfx.y1 || newGfxInfo.y1 > otherGfx.y2);
		if (overlapX && overlapY) {
			return false;
		}
	}
	return true;
}

void Move::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Find the component at the clicked location
	selectedComp = pManager->GetComponent(clickX, clickY);

	if (selectedComp == NULL) {
		pOut->PrintMsg("Error: No component found at clicked location.");
		return;
	}

	// Don't allow moving connections directly
	if (dynamic_cast<Connection*>(selectedComp)) {
		pOut->PrintMsg("Error: Connections move automatically with their components.");
		return;
	}

	// Get old graphics info for undo
	oldGfxInfo = selectedComp->GetGFXinfo();
	GraphicsInfo currentGfx = oldGfxInfo;

	// Calculate offset from click point to component top-left
	int clickOffsetX = clickX - currentGfx.x1;
	int clickOffsetY = clickY - currentGfx.y1;

	// Store initial position for offset calculation
	int initialX = clickX;
	int initialY = clickY;

	// Drag loop: continue while mouse button is down
	int mouseX, mouseY;
	int buttonDown = pIn->GetButtonState(mouseX, mouseY);
	
	// Wait for button to be released first (in case it was already down)
	while (buttonDown) {
		buttonDown = pIn->GetButtonState(mouseX, mouseY);
	}
	
	// Now wait for button press to start dragging
	while (!buttonDown) {
		buttonDown = pIn->GetButtonState(mouseX, mouseY);
		if (buttonDown) {
			initialX = mouseX;
			initialY = mouseY;
			break;
		}
	}

	// Drag the component while button is held down
	bool wasValid = true;
	GraphicsInfo lastValidGfx = currentGfx;
	
	while (buttonDown) {
		pIn->GetMouseCoord(mouseX, mouseY);
		buttonDown = pIn->GetButtonState(mouseX, mouseY);

		// Calculate new position based on mouse position and offset
		GraphicsInfo newGfxInfo;
		newGfxInfo.x1 = mouseX - clickOffsetX;
		newGfxInfo.y1 = mouseY - clickOffsetY;
		newGfxInfo.x2 = newGfxInfo.x1 + (oldGfxInfo.x2 - oldGfxInfo.x1);
		newGfxInfo.y2 = newGfxInfo.y1 + (oldGfxInfo.y2 - oldGfxInfo.y1);

		// Only update if position is valid
		if (IsValidPosition(newGfxInfo, selectedComp, pManager)) {
			// Clear old position by redrawing background
			if (currentGfx.x1 != newGfxInfo.x1 || currentGfx.y1 != newGfxInfo.y1) {
				// Erase old component position
				pOut->whiteBox(currentGfx.x1 - 5, currentGfx.y1 - 5, 
				              currentGfx.x2 + 5, currentGfx.y2 + 5);
				
				// Also clear connections in old area
				int compCount = pManager->GetComponentCount();
				for (int i = 0; i < compCount; i++) {
					Component* pComp = pManager->GetComponentByIndex(i);
					Connection* pConn = dynamic_cast<Connection*>(pComp);
					if (pConn) {
						GraphicsInfo connGfx = pConn->GetGFXinfo();
						// Clear connection line area
						int minX = (connGfx.x1 < connGfx.x2) ? connGfx.x1 : connGfx.x2;
						int maxX = (connGfx.x1 > connGfx.x2) ? connGfx.x1 : connGfx.x2;
						int minY = (connGfx.y1 < connGfx.y2) ? connGfx.y1 : connGfx.y2;
						int maxY = (connGfx.y1 > connGfx.y2) ? connGfx.y1 : connGfx.y2;
						pOut->whiteBox(minX - 3, minY - 3, maxX + 3, maxY + 3);
					}
				}
			}
			
			// Update component position
			selectedComp->SetGFXinfo(newGfxInfo);
			currentGfx = newGfxInfo;
			lastValidGfx = newGfxInfo;
			wasValid = true;
			
			// Update connections in real-time
			UpdateConnectionsForComponent(pManager, selectedComp);
			
			// Redraw interface
			pManager->UpdateInterface();
		} else if (wasValid) {
			// If we were in a valid position but now we're not, keep the last valid position
			wasValid = false;
		}
	}
	
	// Ensure we end with valid position
	if (!wasValid && (currentGfx.x1 != lastValidGfx.x1 || currentGfx.y1 != lastValidGfx.y1)) {
		selectedComp->SetGFXinfo(lastValidGfx);
		currentGfx = lastValidGfx;
		UpdateConnectionsForComponent(pManager, selectedComp);
		pManager->UpdateInterface();
	}

	// Calculate final offset for undo/redo
	offsetX = currentGfx.x1 - oldGfxInfo.x1;
	offsetY = currentGfx.y1 - oldGfxInfo.y1;
	
	// Final cleanup - ensure everything is properly redrawn
	pManager->UpdateInterface();

	// Final update of connections
	UpdateConnectionsForComponent(pManager, selectedComp);
	
	
	// Try to get the label using the new position (15 pixels above the component)
	Component* pLabel = pManager->GetComponent(oldGfxInfo.x1, oldGfxInfo.y1 - 15);

	if (Label* label = dynamic_cast<Label*>(pLabel)) {
		if (label->GetAttachedComponent() == selectedComp) {
			// Get current label position
			GraphicsInfo labelGfx = label->GetGFXinfo();

			// Calculate the offset the component moved
			int moveOffsetX = currentGfx.x1 - oldGfxInfo.x1;
			int moveOffsetY = currentGfx.y1 - oldGfxInfo.y1;
			pOut->whiteBox(labelGfx.x1 - 2, labelGfx.y1 - 2,
				labelGfx.x2 + 2, labelGfx.y2 + 2);
			// Move label by the same offset
			labelGfx.x1 += moveOffsetX;
			labelGfx.x2 += moveOffsetX;
			labelGfx.y1 += moveOffsetY;
			labelGfx.y2 += moveOffsetY;

			// Update the label's graphics info
			label->SetGFXinfo(labelGfx);
		}
	}
	pManager->UpdateInterface();
	
	pOut->PrintMsg("Component moved successfully! Connections updated.");
}

void Move::Undo()
{
	if (selectedComp != NULL) {
		// Find and move label back
		GraphicsInfo currentGfx = selectedComp->GetGFXinfo();
		Component* pLabel = pManager->GetComponent(currentGfx.x1, currentGfx.y1 - 15);

		if (Label* label = dynamic_cast<Label*>(pLabel)) {
			if (label->GetAttachedComponent() == selectedComp) {
				GraphicsInfo labelGfx = label->GetGFXinfo();
				int moveOffsetX = oldGfxInfo.x1 - currentGfx.x1;
				int moveOffsetY = oldGfxInfo.y1 - currentGfx.y1;
				labelGfx.x1 += moveOffsetX;
				labelGfx.x2 += moveOffsetX;
				labelGfx.y1 += moveOffsetY;
				labelGfx.y2 += moveOffsetY;

				label->SetGFXinfo(labelGfx);
			}
		}

		// Restore old position
		selectedComp->SetGFXinfo(oldGfxInfo);

		// Update connections
		int compCount = pManager->GetComponentCount();
		for (int i = 0; i < compCount; i++) {
			Component* pComp = pManager->GetComponentByIndex(i);
			Connection* pConn = dynamic_cast<Connection*>(pComp);
			if (pConn == NULL) continue;

			Component* pSrcComp = FindComponentWithOutputPin(pManager, pConn->getSourcePin());
			if (pSrcComp == selectedComp) {
				pConn->UpdateSourceEndpoint(selectedComp);
			}

			Component* pDstComp = pConn->getDestPin()->getComponent();
			if (pDstComp == selectedComp) {
				pConn->UpdateDestEndpoint(selectedComp);
			}
		}
		pManager->UpdateInterface();
	}
}

void Move::Redo()
{
	if (selectedComp != NULL) {
		// Move again using stored offset
		GraphicsInfo currentGfx = selectedComp->GetGFXinfo();
		GraphicsInfo newGfxInfo;
		newGfxInfo.x1 = oldGfxInfo.x1 + offsetX;
		newGfxInfo.y1 = oldGfxInfo.y1 + offsetY;
		newGfxInfo.x2 = oldGfxInfo.x2 + offsetX;
		newGfxInfo.y2 = oldGfxInfo.y2 + offsetY;
		
		selectedComp->SetGFXinfo(newGfxInfo);
		
		// Update connections
		int compCount = pManager->GetComponentCount();
		for (int i = 0; i < compCount; i++) {
			Component* pComp = pManager->GetComponentByIndex(i);
			Connection* pConn = dynamic_cast<Connection*>(pComp);
			if (pConn == NULL) continue;
			
			Component* pSrcComp = FindComponentWithOutputPin(pManager, pConn->getSourcePin());
			if (pSrcComp == selectedComp) {
				pConn->UpdateSourceEndpoint(selectedComp);
			}
			
			Component* pDstComp = pConn->getDestPin()->getComponent();
			if (pDstComp == selectedComp) {
				pConn->UpdateDestEndpoint(selectedComp);
			}
		}
		pManager->UpdateInterface();
	}
}
