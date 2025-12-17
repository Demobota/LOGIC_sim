#include "EditLabel.h"
#include "..\ApplicationManager.h"

EditLabel::EditLabel(ApplicationManager* pApp) : Action(pApp)
{
    Cx = 0;
    Cy = 0;
    pLabel = nullptr;
    oldText = "";
    newText = "";
}

EditLabel::~EditLabel()
{
}

void EditLabel::ReadActionParameters()
{
    // Get a Pointer to the Input / Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Print Action Message
    pOut->PrintMsg("Edit Label: Click on the label you want to edit");

    bool validLabel = false;

    // Loop until user clicks on a valid label
    do
    {
        pIn->GetPointClicked(Cx, Cy);

        // Try to get component at clicked position
        Component* pComp = pManager->GetComponent(Cx, Cy);

        // Check if it's a label
        if (pComp)
        {
            pLabel = dynamic_cast<Label*>(pComp);

            if (pLabel)
            {
                validLabel = true;
                // Store old text for undo
                oldText = pLabel->GetText();
                pOut->PrintMsg("Enter new text for the label:");
            }
            else
            {
                pOut->PrintMsg("Not a label! Please click on a label to edit");
            }
        }
        else
        {
            pOut->PrintMsg("No component found! Please click on a label to edit");
        }

    } while (!validLabel);

    // Get new text from user
    newText = pIn->GetString(pOut);

    // Clear Status Bar
    pOut->ClearStatusBar();
}

void EditLabel::Execute()
{
    // Read parameters
    ReadActionParameters();

    if (pLabel && !newText.empty())
    {
        Output* pOut = pManager->GetOutput();

        // Update the label text
        pLabel->SetText(newText);

        // Recalculate box dimensions based on new text length
        const int fontSize = 18;
        int textWidth = 0, textHeight = 0;
        pOut->GetTextSize(textWidth, textHeight, newText, fontSize);

        const int horizontalPadding = 20;
        int newWidth = (textWidth > 0) ? (textWidth + horizontalPadding) : UI.LABEL_Width;
        int Wdth = UI.LABEL_Height;

        // Get current position
        GraphicsInfo currentGInfo = pLabel->GetGFXinfo();

        // Calculate center point
        int centerX = (currentGInfo.x1 + currentGInfo.x2) / 2;
        int centerY = (currentGInfo.y1 + currentGInfo.y2) / 2;

        // Update graphics info with new width, keeping the same center
        GraphicsInfo newGInfo;
        newGInfo.x1 = centerX - newWidth / 2;
        newGInfo.x2 = centerX + newWidth / 2;
        newGInfo.y1 = centerY - Wdth / 2;
        newGInfo.y2 = centerY + Wdth / 2;

        // If label is attached to a component, recalculate position relative to component
        Component* attachedComp = pLabel->GetAttachedComponent();
        if (attachedComp)
        {
            GraphicsInfo compG = attachedComp->GetGFXinfo();
            int compCenterX = (compG.x1 + compG.x2) / 2;

            newGInfo.x1 = compCenterX - newWidth / 2;
            newGInfo.x2 = compCenterX + newWidth / 2;
            newGInfo.y2 = compG.y1 - 5;
            newGInfo.y1 = newGInfo.y2 - Wdth;
        }

        // Update the graphics info
        pLabel->SetGFXinfo(newGInfo);

        pOut->PrintMsg("Label updated successfully");
    }
}

void EditLabel::Undo()
{
    if (pLabel)
    {
        Output* pOut = pManager->GetOutput();

        // Restore old text
        pLabel->SetText(oldText);

        // Recalculate box dimensions for old text
        const int fontSize = 18;
        int textWidth = 0, textHeight = 0;
        pOut->GetTextSize(textWidth, textHeight, oldText, fontSize);

        const int horizontalPadding = 20;
        int oldWidth = (textWidth > 0) ? (textWidth + horizontalPadding) : UI.LABEL_Width;
        int Wdth = UI.LABEL_Height;

        // Get current position
        GraphicsInfo currentGInfo = pLabel->GetGFXinfo();

        // Calculate center point
        int centerX = (currentGInfo.x1 + currentGInfo.x2) / 2;
        int centerY = (currentGInfo.y1 + currentGInfo.y2) / 2;

        // Update graphics info with old width
        GraphicsInfo oldGInfo;
        oldGInfo.x1 = centerX - oldWidth / 2;
        oldGInfo.x2 = centerX + oldWidth / 2;
        oldGInfo.y1 = centerY - Wdth / 2;
        oldGInfo.y2 = centerY + Wdth / 2;

        // If label is attached to a component, recalculate position
        Component* attachedComp = pLabel->GetAttachedComponent();
        if (attachedComp)
        {
            GraphicsInfo compG = attachedComp->GetGFXinfo();
            int compCenterX = (compG.x1 + compG.x2) / 2;

            oldGInfo.x1 = compCenterX - oldWidth / 2;
            oldGInfo.x2 = compCenterX + oldWidth / 2;
            oldGInfo.y2 = compG.y1 - 5;
            oldGInfo.y1 = oldGInfo.y2 - Wdth;
        }

        pLabel->SetGFXinfo(oldGInfo);
    }
}

void EditLabel::Redo()
{
    if (pLabel)
    {
        Output* pOut = pManager->GetOutput();

        // Restore new text
        pLabel->SetText(newText);

        // Recalculate box dimensions for new text
        const int fontSize = 18;
        int textWidth = 0, textHeight = 0;
        pOut->GetTextSize(textWidth, textHeight, newText, fontSize);

        const int horizontalPadding = 20;
        int redoWidth = (textWidth > 0) ? (textWidth + horizontalPadding) : UI.LABEL_Width;
        int Wdth = UI.LABEL_Height;

        // Get current position
        GraphicsInfo currentGInfo = pLabel->GetGFXinfo();

        // Calculate center point
        int centerX = (currentGInfo.x1 + currentGInfo.x2) / 2;
        int centerY = (currentGInfo.y1 + currentGInfo.y2) / 2;

        // Update graphics info with new width
        GraphicsInfo redoGInfo;
        redoGInfo.x1 = centerX - redoWidth / 2;
        redoGInfo.x2 = centerX + redoWidth / 2;
        redoGInfo.y1 = centerY - Wdth / 2;
        redoGInfo.y2 = centerY + Wdth / 2;

        // If label is attached to a component, recalculate position
        Component* attachedComp = pLabel->GetAttachedComponent();
        if (attachedComp)
        {
            GraphicsInfo compG = attachedComp->GetGFXinfo();
            int compCenterX = (compG.x1 + compG.x2) / 2;

            redoGInfo.x1 = compCenterX - redoWidth / 2;
            redoGInfo.x2 = compCenterX + redoWidth / 2;
            redoGInfo.y2 = compG.y1 - 5;
            redoGInfo.y1 = redoGInfo.y2 - Wdth;
        }

        pLabel->SetGFXinfo(redoGInfo);
    }
}