#pragma once
#ifndef _EDITLABEL_H
#define _EDITLABEL_H

#include "Action.h"
#include "..\Components\Label.h"

class EditLabel : public Action
{
private:
    int Cx, Cy;  // Click coordinates
    Label* pLabel;  // Pointer to the label being edited
    string oldText;  // Store old text for undo
    string newText;  // Store new text for redo

public:
    EditLabel(ApplicationManager* pApp);
    virtual ~EditLabel();

    // Reads parameters required for action execution
    virtual void ReadActionParameters();

    // Executes action (edit the label)
    virtual void Execute();

    // Undo action
    virtual void Undo();

    // Redo action
    virtual void Redo();
};

#endif