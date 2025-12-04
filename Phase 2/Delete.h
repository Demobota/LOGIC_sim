#pragma once
#include "Actions\\Action.h"

class Delete : public Action
{
    int P1, P2; //point clicked 
public:
    Delete(ApplicationManager* pApp) : Action(pApp) {}

    // Action interface
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};

