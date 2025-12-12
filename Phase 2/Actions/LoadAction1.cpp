#include "LoadAction1.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <fstream>

LoadAction1::LoadAction1(ApplicationManager* pApp) : Action(pApp)
{
}

LoadAction1::~LoadAction1(void)
{
}

void LoadAction1::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Loading: Please type the file name (without extension) or press ESC to cancel...");
    FileName = pIn->GetString(pOut);

    pOut->ClearStatusBar();
}

void LoadAction1::Execute()
{
    // Ask for filename
    ReadActionParameters();

    if (FileName.empty()) // user cancelled or empty input
    {
        pManager->GetOutput()->PrintMsg("Load cancelled.");
        return;
    }

    // Try with .txt extension first
    std::ifstream inFile(FileName + ".txt");
    if (!inFile.is_open())
    {
        // Try using the exact name user provided (in case they included ext)
        inFile.open(FileName);
    }

    if (!inFile.is_open())
    {
        pManager->GetOutput()->PrintMsg("Error: Could not open file for loading.");
        return;
    }

    // Delegate loading to ApplicationManager
    pManager->LoadAll(inFile);
    inFile.close();

    // Refresh UI
    pManager->UpdateInterface();
    pManager->GetOutput()->PrintMsg("Circuit loaded successfully.");
}

void LoadAction1::Undo() {}
void LoadAction1::Redo() {}