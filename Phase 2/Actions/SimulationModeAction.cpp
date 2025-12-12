#include "SimulationModeAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
//osama tamer
SimulationModeAction::SimulationModeAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

SimulationModeAction::~SimulationModeAction()
{
}

void SimulationModeAction::ReadActionParameters()
{
    // No user input needed
}

void SimulationModeAction::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();

    // Switch internal application state (if required)
    UI.AppMode = SIMULATION;

    // Clear status bar and redraw interface
    pOut->ClearStatusBar();
    pOut->PrintMsg("Simulation Mode Activated");

    // Draw simulation toolbar under design toolbar
    pOut->CreateSimulationToolBar();
}

void SimulationModeAction::Undo() {}
void SimulationModeAction::Redo() {}





