#ifndef SIMULATION_MODE_ACTION_H
#define SIMULATION_MODE_ACTION_H
// osama tamer
#include "Action.h"

class SimulationModeAction : public Action
{
public:
    SimulationModeAction(ApplicationManager* pApp);
    virtual ~SimulationModeAction();

    virtual void ReadActionParameters(); 
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif





