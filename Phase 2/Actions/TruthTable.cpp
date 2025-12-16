#include "TruthTable.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

TruthTable::TruthTable(ApplicationManager* pApp) : Action(pApp)
{
}

TruthTable::~TruthTable(void)
{
}

void TruthTable::ReadActionParameters()
{
	// No clicks needed from user.
	// We just tell them what is happening.
	if (pManager->GetOutput()) {
		pManager->GetOutput()->PrintMsg("Generating Truth Table... Check the Console Window.");
	}
}

void TruthTable::Execute()
{
	// 1. Notify User
	if (pManager->GetOutput())
		pManager->GetOutput()->PrintMsg("Generating Truth Table... Click anywhere to close.");

	// 2. Collect Components
	vector<Switch*> InputSwitches;
	vector<LED*> OutputLEDs;
	int count = pManager->GetCompCount();

	for (int i = 0; i < count; i++)
	{
		Component* pComp = pManager->GetCompList()[i];
		if (dynamic_cast<Switch*>(pComp))
			InputSwitches.push_back(dynamic_cast<Switch*>(pComp));
		if (dynamic_cast<LED*>(pComp))
			OutputLEDs.push_back(dynamic_cast<LED*>(pComp));
	}

	// 3. Setup
	int numInputs = InputSwitches.size();
	int numOutputs = OutputLEDs.size();

	if (numInputs == 0) {
		pManager->GetOutput()->PrintMsg("Error: No Switches found!");
		return;
	}

	int numRows = pow(2, numInputs);
	int numCols = numInputs + numOutputs;

	// Create a dynamic array to hold all the 0s and 1s
	// Size = Rows * Columns
	int* tableData = new int[numRows * numCols];

	// 4. Simulation Loop
	for (int i = 0; i < numRows; i++)
	{
		// --- A. Set Inputs & Record Them ---
		for (int j = 0; j < numInputs; j++)
		{
			int bit = (i >> (numInputs - 1 - j)) & 1;

			// Set Component State
			if (bit == 1)
				InputSwitches[j]->setInputPinStatus(1, HIGH);
			else
				InputSwitches[j]->setInputPinStatus(1, LOW);

			// Save to Array: Row i, Column j
			tableData[(i * numCols) + j] = bit;
		}

		// --- B. Simulate ---
		for (int k = 0; k < count; k++) {
			for (int m = 0; m < count; m++) {
				if (pManager->GetCompList()[m])
					pManager->GetCompList()[m]->Operate();
			}
		}

		// --- C. Read Outputs & Record Them ---
		for (int j = 0; j < numOutputs; j++)
		{
			int result = (OutputLEDs[j]->GetInputPinStatus(1) == HIGH) ? 1 : 0;

			// Save to Array: Row i, Column (numInputs + j)
			tableData[(i * numCols) + (numInputs + j)] = result;
		}
	}

	// 5. Draw the Table
	pManager->GetOutput()->DrawTruthTable(numInputs, numOutputs, tableData);

	// 6. Wait for user to see it
	int x, y;
	pManager->GetInput()->GetPointClicked(x, y); // Wait for click

	// 7. Cleanup
	delete[] tableData; // Delete the array to prevent memory leak
	pManager->GetOutput()->ClearDrawingArea(); // Clear the table
	pManager->GetOutput()->PrintMsg("Truth Table Closed.");

	// Optional: Redraw circuit so it looks clean again
	// pManager->UpdateInterface(); 
}
void TruthTable::Undo()
{
}

void TruthTable::Redo()
{
}
